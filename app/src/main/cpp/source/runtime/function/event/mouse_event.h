#pragma once

#include <sstream>

#include "runtime/function/event/event.h"

namespace Gp {

  class MouseMovedEvent : public Event {
  public:
    typedef std::shared_ptr<MouseMovedEvent> ptr;

    MouseMovedEvent(float x_pos, float y_pos)
      : m_xPos(x_pos), m_yPos(y_pos) {}

    EVENT_CLASS_TYPE(MouseMoved)

    EVENT_CLASS_GET_CATEGORY(EventCategoryInput | EventCategoryMouse)

    std::string ToString() const override {
      std::stringstream ss;
      ss << "MouseMovedEvent: xPos=" << GetXPos() << " yPos=" << GetYPos();
      return ss.str();
    }

    inline float GetXPos() const { return m_xPos; }

    inline float GetYPos() const { return m_yPos; }

  private:
    float m_xPos;
    float m_yPos;
  };

  class MouseButtonEvent : public Event {
  public:
    typedef std::shared_ptr<MouseButtonEvent> ptr;

    MouseButtonEvent(int button) : m_button(button) {}

    EVENT_CLASS_GET_CATEGORY(EventCategoryInput | EventCategoryMouseButton)

    virtual ~MouseButtonEvent() {}

    inline int GetMouseButton() const { return m_button; }

  protected:
    int m_button;
  };

  class MouseButtonPressedEvent : public MouseButtonEvent {
  public:
    typedef std::shared_ptr<MouseButtonPressedEvent> ptr;

    MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {}

    EVENT_CLASS_TYPE(MouseButtonPressed)

    std::string ToString() const override {
      std::stringstream ss;
      ss << "MouseButtonPressed: button=" << m_button;
      return ss.str();
    }
  };

  class MouseButtonReleasedEvent : public MouseButtonEvent {
  public:
    typedef std::shared_ptr<MouseButtonReleasedEvent> ptr;

    MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}

    EVENT_CLASS_TYPE(MouseButtonReleased)

    std::string ToString() const override {
      std::stringstream ss;
      ss << "MouseButtonRelease: button=" << m_button;
      return ss.str();
    }

  };

}
