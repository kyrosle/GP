#pragma once

#include <memory>
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <array>
#include <game-activity/native_app_glue/android_native_app_glue.h>

#include "runtime/core/base/ring_buffer.h"
#include "runtime/function/event/event.h"
#include "runtime/function/render/layer/render_layer_stack.h"

namespace Gp {
  class WindowSystem {
  public:
    typedef std::shared_ptr<WindowSystem> ptr;

    WindowSystem() = default;

    ~WindowSystem();

    /*!
     * Performs necessary OpenGL initialization. Customize this if you want to change your EGL
     * context or application-wide settings.
     */
    void initialize(struct android_app *app);

    /*!
     * @brief we have to check every frame to see if the framebuffer has changed in size. If it has,
     * update the viewport accordingly
     */
    void updateRenderArea();

    /*!
     * Handles input from the android_app.
     *
     * Note: this will clear the input queue
     */
    void handleInput();


    /*!
     * Swap egl buffer, after all opengl es/ imgui step finished.
     */
    bool swapBuffers() {
      auto swapResult = eglSwapBuffers(m_display, m_surface);
      return swapResult;
    }

    /*!
     * Push a Event to buffer.
     * if the buffer is full, this will overlap the Event before.
     */
    void pushEvent(Event::ptr event) {
      m_ring_buffer.push(std::move(event));
    }

    /*!
     * Fetch a Event from buffer.
     * if the buffer is empty, return a nullptr.
     */
    Event::ptr popEvent() {
      return m_ring_buffer.pop().value_or(nullptr);
    }

    /*!
     * dispatcher the motion to imgui layer, layerStack
     */
    void inputDispatcher(RenderLayerStack &layerStack);

    void inputDispatcher();

  private:
    /*!
     * handle a motion event
     * currently only for MousePressed, MouseReleased, MouseMoved
     */
    void handleMotionEvent(GameActivityMotionEvent &motionEvent);

  private:

    RingBuffer<Event::ptr> m_ring_buffer;

    struct android_app *m_app;

    EGLDisplay m_display = EGL_NO_DISPLAY;
    EGLSurface m_surface = EGL_NO_SURFACE;
    EGLContext m_context = EGL_NO_CONTEXT;
    EGLint m_width = 0;
    EGLint m_height = 0;
  };
}
