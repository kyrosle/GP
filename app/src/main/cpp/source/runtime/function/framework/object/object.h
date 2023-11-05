#pragma once

#include <memory>
#include <vector>

#include "runtime/function/framework/object/object_id_allocator.h"
#include "runtime/function/framework/component/component.h"
#include "runtime/resource/res_type/common/object.h"

namespace Gp {
  class ObjectInstanceRes;

  class ComponentBase;

  /*
   * Current now only for 2d game,
   * game object in unity is offered these components:
   * 1. Sprite Render
   * 2. Collider 2D
   * 3. Rigidbody 2D
   * 4. Animator
   * 5. AudioSource
   *
   * And others:
   * 1. Tilemap
   * 2. TextMesh
   */
  class GObject : public std::enable_shared_from_this<GObject> {
  public:
    typedef std::shared_ptr<GObject> ptr;
    typedef std::weak_ptr<GObject> w_ptr;

    GObject(GObjectID id) : m_id(id) {}

    virtual ~GObject();

    virtual void tick(float delta_time);

    bool load(const ObjectInstanceRes &object_instance_res);

    void defaultLoad(int idx = 0);

//    void save(ObjectInstanceRes& object_instance_res);

    GObjectID getID() const { return m_id; }

    void setName(const std::string &name) { m_name = name; }

    const std::string &getName() { return m_name; }

    bool hasComponent(const std::string &component_type_name) const;

    std::vector<std::shared_ptr<ComponentBase>> &getComponents() { return m_components; }

    template<typename TComponent>
    std::shared_ptr<TComponent> tryGetComponent_(const std::string &component_type_name) const {
      for (const auto &component: m_components) {
        if (component->getTypeName() == component_type_name) {
//          return static_cast<TComponent>(component.operator->());
          return std::dynamic_pointer_cast<TComponent>(component);
        }
      }
      return nullptr;
    }

    template<typename TComponent>
    std::shared_ptr<TComponent>
    tryGetComponentConst_(const std::string &component_type_name) const {
      for (const auto &component: m_components) {
        if (component->getTypeName() == component_type_name) {
          return std::const_pointer_cast<TComponent>(
              std::dynamic_pointer_cast<TComponent>(component));
        }
      }
      return nullptr;
    }

    #define tryGetComponent(COMPONENT_TYPE) tryGetComponent_<COMPONENT_TYPE>(#COMPONENT_TYPE)
    #define tryGetComponentConst(COMPONENT_TYPE) tryGetComponentConst_<COMPONENT_TYPE>(#COMPONENT_TYPE)

  protected:
    GObjectID m_id{k_invalid_gobject_id};
    std::string m_name;
    std::string m_definition_url;

    std::vector<std::shared_ptr<ComponentBase>> m_components;
  };

}

