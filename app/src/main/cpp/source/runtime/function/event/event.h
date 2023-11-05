#pragma once

#include <memory>
#include <string>

#define EVENT_CLASS_TYPE(type) \
static EventType GetStaticType() { return EventType::type; }\
const EventType GetEventType() const override { return GetStaticType(); }\
const char* GetName() const override { return #type; }

#define EVENT_CLASS_GET_CATEGORY(category) int GetCategoryFlag() const override { return category;}

namespace Gp {
  enum class EventType {
    None = 0,
    WindowClose, WindowResized, WindowFocus, WindowLostFocus, WindowMoved,
    AppTick, AppUpdate, AppRender,
    KeyPressed, KeyReleased, KeyTyped,
    MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
  };

  enum EventCategory {
    None = 0,
    EventCategoryApplication = 0,
    EventCategoryInput = 1 << 1,
    EventCategoryKeyboard = 1 << 2,
    EventCategoryMouse = 1 << 3,
    EventCategoryMouseButton = 1 << 4,
  };

  class Event {
  public:
    friend class EventDispatcher;

    typedef std::shared_ptr<Event> ptr;
    typedef std::unique_ptr<Event> u_ptr;

    virtual ~Event() {};

    virtual const char *GetName() const = 0;

    virtual const EventType GetEventType() const = 0;

    virtual int GetCategoryFlag() const = 0;

    virtual std::string ToString() const { return GetName(); }

    inline bool IsInCategory(EventCategory type) {
      return GetCategoryFlag() & (int) type;
    }

    bool IsHandled() { return m_handled; }

    void MarkHandled() { m_handled = true; }

  protected:
    bool m_handled = false;
  };

  class EventDispatcher {
    template<typename T>
    using EventHandler = std::function<bool(T &)>;
  public:
    EventDispatcher(Event &e) : m_event(e) {}

    template<typename T>
    void Dispatch(EventHandler<T> handler) {
      if (m_event.m_handled) {
        return;
      }

      if (m_event.GetEventType() == T::GetStaticType()) {
        m_event.m_handled = handler(*(T *) &m_event);
        m_event.m_handled = true;
      }
    }

  private:
    Event &m_event;
  };

}

