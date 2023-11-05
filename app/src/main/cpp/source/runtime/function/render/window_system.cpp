#include "window_system.h"

#include <cassert>
#include <string>
#include <vector>
#include <imgui.h>
#include <imgui/backends/imgui_impl_android.h>
#include <game-activity/GameActivityEvents.h>

#include "runtime/core/log/android_out.h"
#include "runtime/function/global/global_context.h"

#include "runtime/function/event/mouse_event.h"


//! executes glGetString and outputs the result to logcat
#define PRINT_GL_STRING(s) {acout << #s": "<< glGetString(s) << std::endl;}

/*!
 * @brief if glGetString returns a space separated list of elements, prints each one on a new line
 *
 * This works by creating an istringstream of the input c-style string. Then that is used to create
 * a vector -- each element of the vector is a new element in the input string. Finally a foreach
 * loop consumes this and outputs it to logcat using @a acout
 */
#define PRINT_GL_STRING_AS_LIST(s) { \
std::istringstream extensionStream((const char *) glGetString(s));\
std::vector<std::string> extensionList(\
        std::istream_iterator<std::string>{extensionStream},\
        std::istream_iterator<std::string>());\
acout << #s":\n";\
for (auto& extension: extensionList) {\
    acout << extension << "\n";\
}\
acout << std::endl;\
}

//! Color for cornflower blue. Can be sent directly to glClearColor
#define CORNFLOWER_BLUE 100 / 255.f, 149 / 255.f, 237 / 255.f, 1

namespace Gp {
  void WindowSystem::initialize(struct android_app *app) {
    // record struct android_app
    m_app = app;
    // initialize the ring buffer for input buffer
    m_ring_buffer.initialize(1024);
    // Choose your render attributes
    constexpr EGLint attribs[] = {
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT, // render type - opengl es 3
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT, // surface type - use window
        EGL_BLUE_SIZE, 8, // blue color render_buffer size - 8
        EGL_GREEN_SIZE, 8, // green color render_buffer size - 8
        EGL_RED_SIZE, 8, // red color render_buffer size - 8
        EGL_DEPTH_SIZE, 24, // depth size - 24
        EGL_NONE // end mark
    };

    // The default display is probably what you want on Android
    auto display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    eglInitialize(display, nullptr, nullptr);

    // figure out how many configs there are
    EGLint numConfigs;
    eglChooseConfig(display, attribs, nullptr, 0,
                    &numConfigs);

    // get the list of configurations
    std::unique_ptr<EGLConfig[]> supportedConfigs(
        new EGLConfig[numConfigs]);
    eglChooseConfig(display, attribs, supportedConfigs.get(),
                    numConfigs, &numConfigs);

    // Find a config we like.
    // Could likely just grab the first if we don't care about anything else in the config.
    // Otherwise hook in your own heuristic
    auto config = *std::find_if(
        supportedConfigs.get(),
        supportedConfigs.get() + numConfigs,
        [&display](const EGLConfig &config) {
          EGLint red, green, blue, depth;
          if (eglGetConfigAttrib(display, config, EGL_RED_SIZE, &red)
              && eglGetConfigAttrib(display, config, EGL_GREEN_SIZE, &green)
              && eglGetConfigAttrib(display, config, EGL_BLUE_SIZE, &blue)
              && eglGetConfigAttrib(display, config, EGL_DEPTH_SIZE, &depth)) {

            acout << "Found config with " << red << ", " << green
                  << ", " << blue << ", "
                  << depth << std::endl;
            return red == 8 && green == 8 && blue == 8 &&
                   depth == 24;
          }
          return false;
        });

    acout << "Found " << numConfigs << " configs" << std::endl;
    acout << "Chose " << config << std::endl;

    // create the proper window surface
    EGLint format;
    eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID,
                       &format);
    EGLSurface surface = eglCreateWindowSurface(display,
                                                config,
                                                app->window,
                                                nullptr);

    // Create a GLES 3 context
    EGLint contextAttribs[] = {EGL_CONTEXT_CLIENT_VERSION, 3,
                               EGL_NONE};
    EGLContext context = eglCreateContext(display, config,
                                          nullptr,
                                          contextAttribs);

    // get some window metrics
    auto madeCurrent = eglMakeCurrent(display, surface,
                                      surface, context);
    assert(madeCurrent);

    m_display = display;
    m_surface = surface;
    m_context = context;

    // make width and height invalid so it gets updated the first frame in @a updateRenderArea()
    m_width = -1;
    m_height = -1;

    PRINT_GL_STRING(GL_VENDOR);
    PRINT_GL_STRING(GL_RENDERER);
    PRINT_GL_STRING(GL_VERSION);
    PRINT_GL_STRING_AS_LIST(GL_EXTENSIONS);

    // setup any other gl related global states
    glClearColor(CORNFLOWER_BLUE);

    // enable alpha globally for now, you probably don't want to do this in a game
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // call at first time to set width and height
    updateRenderArea();

    // set vsync on
    eglSwapInterval(m_display, 1);
  }

  void WindowSystem::updateRenderArea() {
    EGLint width;
    eglQuerySurface(m_display, m_surface, EGL_WIDTH, &width);

    EGLint height;
    eglQuerySurface(m_display, m_surface, EGL_HEIGHT, &height);

    if (width != m_width || height != m_height) {
      m_width = width;
      m_height = height;

      //  Window Size: x=2159 y=1080
      // x_of = 1000 y_of = 500
//      acout << "Window Size: x=" << m_width << " y=" << m_height << std::endl;
      glViewport(0, 0, width, height);
      if (g_runtime_global_context.m_render_system != nullptr) {
        g_runtime_global_context.m_render_system->m_render_camera->getCamera().
            OnResize(width, height);
      }

      // make sure that we lazily recreate the projection matrix before we render
//      m_shaderNeedsNewProjectionMatrix = true;
    }
  }

  WindowSystem::~WindowSystem() {
    if (m_display != EGL_NO_DISPLAY) {
      eglMakeCurrent(m_display, EGL_NO_SURFACE, EGL_NO_SURFACE,
                     EGL_NO_CONTEXT);
      if (m_context != EGL_NO_CONTEXT) {
        eglDestroyContext(m_display, m_context);
        m_context = EGL_NO_CONTEXT;
      }
      if (m_surface != EGL_NO_SURFACE) {
        eglDestroySurface(m_display, m_surface);
        m_surface = EGL_NO_SURFACE;
      }
      eglTerminate(m_display);
      m_display = EGL_NO_DISPLAY;
    }
  }

  void WindowSystem::handleInput() {
    // handle all queued inputs
    auto *inputBuffer = android_app_swap_input_buffers(m_app);
    if (!inputBuffer) {
      // no inputs yet.
      return;
    }

    // handle motion events (motionEventsCounts can be 0).
    for (auto i = 0; i < inputBuffer->motionEventsCount; i++) {
      auto &motionEvent = inputBuffer->motionEvents[i];
      handleMotionEvent(motionEvent);
    }
    // clear the motion input count in this render_buffer for main thread to re-use.
    android_app_clear_motion_events(inputBuffer);

    // handle input key events.
    for (auto i = 0; i < inputBuffer->keyEventsCount; i++) {
      auto &keyEvent = inputBuffer->keyEvents[i];
      acout << "Key: " << keyEvent.keyCode << " ";
      switch (keyEvent.action) {
        case AKEY_EVENT_ACTION_DOWN:
          acout << "Key Down";
          break;
        case AKEY_EVENT_ACTION_UP:
          acout << "Key Up";
          break;
        case AKEY_EVENT_ACTION_MULTIPLE:
          // Deprecated since Android API level 29.
          acout << "Multiple Key Actions";
          break;
        default:
          acout << "Unknown KeyEvent Action: "
                << keyEvent.action;
      }
      acout << std::endl;
    }
    // clear the key input count too.
    android_app_clear_key_events(inputBuffer);
  }

  void WindowSystem::handleMotionEvent(GameActivityMotionEvent &motionEvent) {
    ImGuiIO &io = ImGui::GetIO();
    auto action = motionEvent.action;

    // Find the pointer index, mask and bitshift to turn it into a readable value.
    auto pointerIndex =
        (action & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK)
            >> AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT;

    // get the x and y position of this event if it is not ACTION_MOVE.
    auto &pointer = motionEvent.pointers[pointerIndex];
    auto x = GameActivityPointerAxes_getX(&pointer);
    auto y = GameActivityPointerAxes_getY(&pointer);
//    io.AddMouseSourceEvent(ImGuiMouseSource_TouchScreen);

    // determine the action type and process the event accordingly.
    switch (action & AMOTION_EVENT_ACTION_MASK) {
      case AMOTION_EVENT_ACTION_DOWN:
      case AMOTION_EVENT_ACTION_POINTER_DOWN:
        pushEvent(std::move(std::make_unique<MouseMovedEvent>(x, y)));
        pushEvent(std::move(std::make_unique<MouseButtonPressedEvent>(0)));
//        io.AddMousePosEvent(x, y);
//        io.AddMouseButtonEvent(0, true);
        break;

      case AMOTION_EVENT_ACTION_CANCEL:
        // treat the CANCEL as an UP event: doing nothing in the app, except
        // removing the pointer from the cache if pointers are locally saved.
        // code pass through on purpose.
      case AMOTION_EVENT_ACTION_UP:
      case AMOTION_EVENT_ACTION_POINTER_UP:
        pushEvent(std::move(std::make_unique<MouseMovedEvent>(x, y)));
        pushEvent(std::move(std::make_unique<MouseButtonReleasedEvent>(0)));
//        io.AddMousePosEvent(x, y);
//        io.AddMouseButtonEvent(0, false);
        break;

      case AMOTION_EVENT_ACTION_MOVE:
        // There is no pointer index for ACTION_MOVE, only a snapshot of
        // all active pointers; app needs to cache previous active pointers
        // to figure out which ones are actually moved.
        for (auto index = 0; index < motionEvent.pointerCount; index++) {
          pointer = motionEvent.pointers[index];
          x = GameActivityPointerAxes_getX(&pointer);
          y = GameActivityPointerAxes_getY(&pointer);
          pushEvent(std::move(std::make_unique<MouseMovedEvent>(x, y)));
//          io.AddMousePosEvent(x, y);
        }
        break;
      default:
        break;
    }
  }

  /*
   * at fist ImguiLayer handle the event
   *  -> not handle
   *   -> pass to the tail(as queue)/head(as queue) of layerStack
   *    -> not handle
   *     -> next layer of layerStack ...
   *
   * this function handle by `WindowSystem` or `RenderSystem`?
   * - `WindowSystem` -> ring_buffer -> `RenderSystem`
   *     caller by engine after handleInput()
   * - `RenderSystem` -> layer_stack, imgui_layer -> `WindowSystem` (for now)
   *     caller by engine after handleInput()
   *
   * - `Engine` ~ this may mess
   *
   * each layer register a EventListener -> here dispatch the event,
   * loop the layer to handle its event (X), seem it has lots of problems.
   */
  void WindowSystem::inputDispatcher(RenderLayerStack &layerStack) {
    while (!m_ring_buffer.isEmpty()) {
      auto event = popEvent();
      assert(event);


      // first handle by imgui layer
      auto imgui_layer = g_runtime_global_context
          .m_render_system->getImguiLayer();
      imgui_layer->OnEvent(event);

      // if the event is not mark handled by imgui layer,
      // continue down passing
      if (!event->IsHandled()) {
        for (auto &layer: layerStack) {
          layer->OnEvent(event);
        }
      }
    }
  }

  void WindowSystem::inputDispatcher() {
    while (!m_ring_buffer.isEmpty()) {
      auto event = popEvent();
      assert(event);

      // first handle by imgui layer
      auto imgui_layer = g_runtime_global_context
          .m_render_system->getImguiLayer();
      imgui_layer->OnEvent(event);
    }
  }
}