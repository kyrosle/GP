#pragma once

#include "runtime/resource/res_type/data/basic_shape.h"
#include "runtime/resource/res_type/components/motor.h"

namespace Gp {
  enum class ControllerType : unsigned char {
    none,
    physical,
    invalid,
  };

  class ControllerConfig {
  public:
    virtual ~ControllerConfig() {}
  };

  class PhysicalControllerConfig : public ControllerConfig {
  public:
    PhysicalControllerConfig() {}

    ~PhysicalControllerConfig() {}

    Cylinder m_cylinder_shape;
  };

  class MotorComponentRes {
  public:
    MotorComponentRes() = default;

    ~MotorComponentRes();

    float m_move_speed{0.f};
    float m_jump_height{0.f};
    float m_max_move_speed_ratio{0.f};
    float m_max_sprint_speed_ratio{0.f};
    float m_move_acceleration{0.f};
    float m_sprint_acceleration{0.f};

    PhysicalControllerConfig *m_controller_config;
  };

}