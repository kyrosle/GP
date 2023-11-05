#pragma once

#include <memory>

#include "runtime/function/framework/component/component.h"
#include "runtime/resource/res_type/components/motor.h"
#include "runtime/function/controller/character_controller.h"

namespace Gp {
  enum class MotorState : unsigned char {
    moving,
    jumping
  };

  enum class JumpState : unsigned char {
    idle,
    rising,
    falling,
  };

  class MotorComponent : public ComponentBase {
  public:
    typedef std::shared_ptr<MotorComponent> ptr;

    MotorComponent() : ComponentBase("MotorComponent") {}

    ~MotorComponent() override;

    void postLoadResource(std::weak_ptr<GObject> parent_object) override;

    void tick(float deltaTime) override;

    void tickPlayerMotor(float deltaTime);

    const glm::vec3 &getTargetPosition() const { return m_target_position; }

    float getSpeedRatio() const { return m_move_speed_ratio; }

    bool getIsMoving() const { return m_is_moving; }

    void getOffStuckDead();

  private:
    void calculatedDesiredHorizontalMoveSpeed(unsigned int command, float delta_time);

    void calculatedDesiredVerticalMoveSpeed(unsigned int command, float delta_time);

    void calculatedDesiredMoveDirection(unsigned int command, const float &object_rotation);

    void calculatedDesiredDisplacement(float delta_time);

    void calculatedTargetPosition(const glm::vec3 &&current_position);

  private:

    MotorComponentRes m_motor_res;

    float m_move_speed_ratio{0.f};
    float m_vertical_speed{0.f};
    float m_jump_horizontal_speed_ratio{0.f};

    glm::vec3 m_desired_displacement;
    glm::vec3 m_desired_horizontal_move_destination;
    glm::vec3 m_jump_initial_velocity;
    glm::vec3 m_target_position;

    MotorState m_motor_state{MotorState::moving};
    JumpState m_jump_state{JumpState::idle};

    ControllerType m_controller_type{ControllerType::none};
    Controller *m_controller{nullptr};

    bool m_is_moving{false};
  };

}

