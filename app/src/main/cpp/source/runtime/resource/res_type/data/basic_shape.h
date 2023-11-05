#pragma once

#include "runtime/core/math/math_header.h"

namespace Gp {

  class Geometry {
  public:
    virtual ~Geometry() {}
  };

  class Quad : public Geometry {
  public:
    ~Quad() override {}

    glm::vec3 m_half_extents{0.5f, 0.5f, 0.5f};
  };

  class Circle : public Geometry {
  public:
    ~Circle() override {}

    float m_radius{0.5f};
  };

  class Cylinder : public Geometry {
  public:
    ~Cylinder() override {}

    float m_radius{0.3f};
    float m_half_height{0.7f};
  };
}