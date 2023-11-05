#include "object.h"

#include "runtime/core/log/android_out.h"

namespace Gp {
  /* -------------------------------------------------------------------------------------------- */
  /* default object resource definition */
  MeshComponentRes default_mesh_component_res_left = {
      {
          {
              "Resources/mesh.json", // not existed, texture file should hard core now
              Transform2D(glm::vec3(-1.f, 0.f, 0.f), 0.f, glm::vec3(1.f, 1.f, 0.f))
          }
      }
  };
  MeshComponentRes default_mesh_component_res_right = {
      {
          {
              "Resources/mesh.json", // not existed, texture file should hard core now
              Transform2D(glm::vec3(1.f, 0.f, 0.f), 0.f, glm::vec3(1.f, 1.f, 0.f))
          }
      }
  };
  TextureComponentRes default_texture_component_res1 = {
      "Resources/pic.png"
  };
  TextureComponentRes default_texture_component_res2 = {
      "Resources/HeadIcon.jpg"
  };
  ObjectInstanceRes
      default_object_instance_res[] = {
      {
          "default_object_instance1",
          "null",
          {
              TransformComponent::ptr(new TransformComponent()),
              MeshComponent::ptr(new MeshComponent(default_mesh_component_res_left)),
              TextureComponent::ptr(new TextureComponent(default_texture_component_res1))
          },
      },
      {
          "default_object_instance2",
          "null",
          {
              TransformComponent::ptr(new TransformComponent()),
              MeshComponent::ptr(new MeshComponent(default_mesh_component_res_right)),
              TextureComponent::ptr(new TextureComponent(default_texture_component_res2))
          }
      }
  };

  /* -------------------------------------------------------------------------------------------- */

  GObject::~GObject() {
    m_components.clear();
  }

  void GObject::tick(float delta_time) {
    for (auto &component: m_components) {
      component->tick(delta_time);
    }
  }

  void GObject::defaultLoad(int idx) {
    m_components.clear();

    setName(default_object_instance_res[idx].m_name);

    m_components = default_object_instance_res[idx].m_instanced_components;

    for (const auto &component: m_components) {
      if (component) {
        acout << "component load: " << component->getTypeName() << std::endl;
        component->postLoadResource(weak_from_this());
      }
    }
  }

  bool GObject::load(const ObjectInstanceRes &object_instance_res) {
    // clear old components
    m_components.clear();

    setName(object_instance_res.m_name);

    // load object instanced components
    m_components = object_instance_res.m_instanced_components;

    for (const auto &component: m_components) {
      if (component) {
        component->postLoadResource(weak_from_this());
      }
    }

    // load object definition components
    m_definition_url = object_instance_res.m_definition;

    // load definition form `m_definition_url` path file
    ObjectDefinitionRes definition_res;

    // load definition resources file by asset manager

    for (const auto &loaded_component: definition_res.m_components) {
      const std::string type_name = loaded_component->getTypeName();
      if (hasComponent(type_name)) {
        continue;
      }
      loaded_component->postLoadResource(weak_from_this());

      m_components.push_back(loaded_component);
    }

    return true;
  }

  bool GObject::hasComponent(const std::string &component_type_name) const {
    return std::any_of(
        m_components.begin(), m_components.end(),
        [component_type_name](const ComponentBase::ptr &component) {
          return component->getTypeName() == component_type_name;
        });
  }


}