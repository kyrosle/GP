#pragma once

#include <string>
#include <memory>
#include <game-activity/native_app_glue/android_native_app_glue.h>
#include "runtime/function/global/global_context.h"

namespace Gp {

  class GameEngine {
    static const float s_fps_alpha;
  public:
    typedef std::shared_ptr<GameEngine> ptr;

    void startEngine(const std::string &config_file_path);

    void shutdownEngine();

    void initialize(struct android_app *app);

    void clear();

    bool isQuit() { return m_is_quit; }

    void run();

    bool tickOneFrame(float delta_time);

    int getFps() const { return s_fps_alpha; }

    static float getRunningTimeMs() {
      using namespace std::chrono;
      auto now_time = steady_clock::now();
      auto time_span = duration_cast<duration<float>>(
          now_time - m_startup_time);

      return time_span.count();
    }

  private:
    void logicalTick(float delta_time);

    void rendererTick(float delta_time);

    void calculateFPS(float delta_time);

    float calculateDeltaTime();

  private:
    struct android_app *m_app;
    bool m_is_quit{false};

    static std::chrono::steady_clock::time_point m_startup_time;

    std::chrono::steady_clock::time_point
        m_last_tick_time_point{std::chrono::steady_clock::now()};

    float m_average_duration{0.f};
    int m_frame_count{0};
    int m_fps{0};
  };

}
