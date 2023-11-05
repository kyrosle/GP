#include "runtime/engine.h"
#include "runtime/core/math/math_header.h"
#include "runtime/core/base/macro.h"
#include "runtime/function/framework/world/world_manager.h"

namespace Gp {
  std::chrono::steady_clock::time_point GameEngine::m_startup_time =
      std::chrono::steady_clock::now();

  void GameEngine::startEngine(const std::string &config_file_path) {
    g_runtime_global_context.startSystems(m_app, config_file_path);

    acout << "start engine" << std::endl;
  }

  void GameEngine::shutdownEngine() {
    LOG_INFO("engine shutdown");

    g_runtime_global_context.shutdownSystems();
  }

  void GameEngine::initialize(struct android_app *app) {
    m_app = app;
  }

  void GameEngine::clear() {}

  bool GameEngine::tickOneFrame(float delta_time) {
    logicalTick(delta_time);

    g_runtime_global_context.m_render_system->swapLogicRenderData();
    // Check to see if the surface has changed size. This is _necessary_ to do every frame when
    // using immersive mode as you'll get no other notification that your
    // render-able area has changed.
    g_runtime_global_context.m_window_system->updateRenderArea();

    rendererTick(delta_time);

    // physic manager tick
    // window system poll event
    // update fps show

    // return window whether should close
    return true;
  }

  void GameEngine::run() {
    const float delta_time = calculateDeltaTime();
    tickOneFrame(delta_time);
  }

  void GameEngine::logicalTick(float delta_time) {
//    cout("logical tick");
//    LOG_INFO("logical tick");
    // world manager tick
    g_runtime_global_context.m_world_manager->tick(delta_time);
    // input system tick
    g_runtime_global_context.m_window_system->handleInput();

    //[Thinking]: use render layer stack?
//    g_runtime_global_context.m_window_system->inputDispatcher
//        (g_runtime_global_context.m_render_system->getRenderLayerStack());
    g_runtime_global_context.m_window_system->inputDispatcher();
  }

  void GameEngine::rendererTick(float delta_time) {
//    cout("renderer tick");
//    LOG_INFO("render tick");
    // render system tick
//    g_runtime_global_context.m_render_system->tick(delta_time);
    g_runtime_global_context.m_render_system->tick(delta_time);

    assert(g_runtime_global_context.m_window_system->swapBuffers());
  }

  const float GameEngine::s_fps_alpha = 1.f / 100;

  void GameEngine::calculateFPS(float delta_time) {
    ++m_frame_count;

    if (m_frame_count == 1) {
      m_average_duration += delta_time;
    } else {
      m_average_duration +=
          m_average_duration * (1 - s_fps_alpha) + delta_time * s_fps_alpha;
    }

    m_fps = static_cast<int>(1.f / m_average_duration);
  }

  float GameEngine::calculateDeltaTime() {
    using namespace std::chrono;
    float delta_time;

    {
      steady_clock::time_point tick_time_point = steady_clock::now();
      duration<float> time_span =
          duration_cast<duration<float>>
              (tick_time_point - m_last_tick_time_point);

      delta_time = time_span.count();

      m_last_tick_time_point = tick_time_point;
    }
    return delta_time;
  }
}