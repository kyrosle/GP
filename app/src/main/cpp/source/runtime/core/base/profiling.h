/*
 * Profiling :
 * https://blog.csdn.net/alexhu2010q/article/details/122871987
 */
#pragma once

#include <chrono>
#include <string>
#include <sstream>

namespace Gp {
  struct ProfileResult {
    const char *Name;
    size_t ThreadId;
    long long Start;
    long long End;
  };

//  class Instrumentor {
//  public:
//    static Instrumentor &Get() {
//      static Instrumentor instance;
//      return instance;
//    }
//
//
//  private:
//    std::string m_currentSessionName;
//    std::stringstream m_outputStream;
//  };

  template<typename Fn>
  class Timer {
  public:
    Timer(const char *name, Fn &&func)
      : m_name(name), m_func(func), m_stopped(false) {
      m_startTimePoint = std::chrono::high_resolution_clock::now();
    }

    ~Timer() {
      if (!m_stopped) {
        Stop();
      }
    }

  private:
    void Stop() {
      auto endTimePoint = std::chrono::high_resolution_clock::now();

      uint64_t start =
        std::chrono::time_point_cast<std::chrono::microseconds>(
          m_startTimePoint).time_since_epoch().count();
      uint64_t end =
        std::chrono::time_point_cast<std::chrono::microseconds>(
          endTimePoint).time_since_epoch().count();

      float duration = (end - start) * 0.001f;

      m_stopped = true;

      m_func(m_name, duration);
    }

  private:
    const char *m_name;
    Fn m_func;
    std::chrono::time_point<std::chrono::steady_clock> m_startTimePoint;
    bool m_stopped;
  };

}
