#pragma once

#include "runtime/core/math/math_header.h"
#include "runtime/resource/res_type/data/basic_shape.h"

namespace Gp {

  enum class SweepPass {
    SWEEP_PASS_UP,
    SWEEP_PASS_SIDE,
    SWEEP_PASS_DOWN,
    SWEEP_PASS_SENSOR
  };

  class Controller {
  public:
    virtual ~Controller() = default;

    virtual glm::vec3 move(const glm::vec3 &current_position, const glm::vec3 &displacement) = 0;
  };

  class CharacterController : public Controller {
  public:
    CharacterController(const Cylinder &cylinder);

    ~CharacterController() = default;

    glm::vec3 move(const glm::vec3 &current_position, const glm::vec3 &displacement) override;

  private:
    Cylinder m_cylinder;
//    RigidBodyShape m_rigidbody_shape;
  };
}
