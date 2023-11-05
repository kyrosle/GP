#pragma once

#include <memory>

#include "runtime/core/math/math_header.h"
#include "runtime/resource/res_type/components/rigid_body.h"
#include "runtime/function/framework/component/component.h"

namespace Gp {
  //TODO: use after add `JoltPhysics`
  class RigidBodyComponent : public ComponentBase {
  public:
    typedef std::shared_ptr<RigidBodyComponent> ptr;

    RigidBodyComponent() : ComponentBase("RigidBodyComponent") {}

    ~RigidBodyComponent() override;

    void postLoadResource(std::weak_ptr<GObject> parent_object) override;

    void tick(float deltaTime) override {}

    void updateGlobalTransform(const Transform2D &transform, bool is_scale_dirty);

  protected:
    void createRigidBody(const Transform2D &global_transform);

    void removeRigidBody();

    RigidBodyComponentRes m_rigidbody_res;

    uint32_t m_rigidbody_id{0xffffffff};
  };
}