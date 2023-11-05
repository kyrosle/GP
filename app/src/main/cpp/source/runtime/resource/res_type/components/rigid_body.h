#pragma once

#include "runtime/core/math/math_header.h"

#include <vector>

namespace Gp {
  enum class RigidBodyShapeType : unsigned char {
    quad,
    circle,
    cylinder,
    invalid
  };

  class RigidBodyShape {
  public:
    Transform2D m_global_transform;
    RigidBodyShapeType m_type{RigidBodyShapeType::invalid};

    Transform2D m_local_transform;

    RigidBodyShape() = default;

    RigidBodyShape(const RigidBodyShape &res);

    ~RigidBodyShape();
  };

  class RigidBodyComponentRes {
  public:
    std::vector<RigidBodyShape> m_shapes;
    float m_inverse_mass;
    int m_actor_type;
  };
}
