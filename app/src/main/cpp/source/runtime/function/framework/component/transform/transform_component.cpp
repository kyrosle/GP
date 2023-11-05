#include "transform_component.h"

#include "runtime/core/log/android_out.h"
#include "runtime/function/framework/object/object.h"
#include "runtime/function/framework/component/rigidbody/rigidbody_component.h"

namespace Gp {
  void TransformComponent::postLoadResource(std::weak_ptr<GObject> parent_object) {
    m_parent_object = parent_object;
    m_transform_buffer[0] = m_transform;
    m_transform_buffer[1] = m_transform;
    m_is_dirty = true;
  }

  void TransformComponent::setPosition(const glm::vec3 &new_transform) {
    m_transform_buffer[m_next_index].m_position = new_transform;
    m_transform.m_position = new_transform;
    m_is_dirty = true;
  }

  void TransformComponent::setScale(const glm::vec3 &new_scale) {
    m_transform_buffer[m_next_index].m_scale = new_scale;
    m_transform.m_scale = new_scale;
    m_is_dirty = true;
    m_is_scale_dirty = true;
  }

  void TransformComponent::setRotation(const float &new_rotation) {
    m_transform_buffer[m_next_index].m_rotation = new_rotation;
    m_transform.m_rotation = new_rotation;
    m_is_dirty = true;
  }

  void TransformComponent::tick(float deltaTime) {
//    cout("Transform Component tick");
    std::swap(m_current_index, m_next_index);

    if (m_is_dirty) {
      // update transform component, dirty flag will be reset in mesh component
//      tryUpdateRigidBodyComponent();
    }
  }

  void TransformComponent::tryUpdateRigidBodyComponent() {
    if (!m_parent_object.lock()) {
      return;
    }

    RigidBodyComponent::ptr rigid_body_component =
        m_parent_object.lock()->tryGetComponent(RigidBodyComponent);

    if (rigid_body_component) {
      rigid_body_component->updateGlobalTransform(
          m_transform_buffer[m_current_index],
          m_is_scale_dirty
      );
      m_is_scale_dirty = false;
    }
  }
}