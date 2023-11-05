#pragma once

#include <memory>
#include <string>

namespace Gp {
  class GObject;

  class ComponentBase {
  public:
    typedef std::shared_ptr<ComponentBase> ptr;

    ComponentBase(const std::string &component_name) : m_component_name(component_name) {}

    virtual ~ComponentBase() {}

    virtual void postLoadResource(std::weak_ptr<GObject> parent_object) {
      m_parent_object = parent_object;
    }

    virtual void tick(float deltaTime) {};

    const std::string &getTypeName() const { return m_component_name; }

    bool isDirty() const { return m_is_dirty; }

    void setDirtyFlag(bool is_dirty) { m_is_dirty = is_dirty; }

  protected:
    std::string m_component_name;
    std::weak_ptr<GObject> m_parent_object;
    bool m_is_dirty{false};
    bool m_is_scale_dirty{false};
  };

}

