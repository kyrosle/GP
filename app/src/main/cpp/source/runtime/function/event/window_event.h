#pragma once

#include <sstream>

#include "runtime/function/event/event.h"

namespace Gp {

  class WindowCloseEvent : public Event {
  public:
    WindowCloseEvent() {}

    EVENT_CLASS_TYPE(WindowClose)

    EVENT_CLASS_GET_CATEGORY(EventCategoryApplication)

    std::string ToString() const override {
      std::stringstream ss;
      ss << "Window Close";
      return ss.str();
    }
  };

  class WindowResizedEvent : public Event {
  public:
    WindowResizedEvent(int width, int height)
      : m_height(height), m_width(width) {}

    EVENT_CLASS_TYPE(WindowResized)

    EVENT_CLASS_GET_CATEGORY(EventCategoryApplication)

    inline int GetWindowHeight() const { return m_height; }

    inline int GetWindowWidth() const { return m_width; }

    std::string ToString() const override {
      std::stringstream ss;
      ss << "Window resize: width=" << m_width << " height=" << m_height;
      return ss.str();
    }

  private:
    int m_width;
    int m_height;
  };
}

