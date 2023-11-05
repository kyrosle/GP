
#include "rigidbody_component.h"

#include "runtime/function/framework/object/object.h"
#include "runtime/function/framework/component/transform/transform_component.h"
#include "runtime/core/log/android_out.h"

namespace Gp {
  RigidBodyComponent::~RigidBodyComponent() {
    // remove rigid body form physics scene
  }

  void RigidBodyComponent::postLoadResource(std::weak_ptr<GObject> parent_object) {
    m_parent_object = parent_object;

    const TransformComponent::ptr parent_transform =
        m_parent_object.lock()->tryGetComponentConst(TransformComponent);
    if (parent_transform == nullptr) {
      acout << "No transform component in the object" << std::endl;
      return;
    }

    // create rigid body in physics scene
  }

  void RigidBodyComponent::createRigidBody(const Transform2D &global_transform) {
    // create rigid body in physics and get the rigid body id;
  }

  void RigidBodyComponent::removeRigidBody() {
    // remove the rigid body
  }

  void
  RigidBodyComponent::updateGlobalTransform(const Transform2D &transform, bool is_scale_dirty) {
    if (is_scale_dirty) {
      removeRigidBody();
      createRigidBody(transform);
    } else {
      // update rigid body global transform in physics scene
    }
  }
}