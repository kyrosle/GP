#include "motor_component.h"

#include "runtime/core/log/android_out.h"
#include "runtime/function/global/global_context.h"
#include "runtime/function/framework/component/transform/transform_component.h"

namespace Gp {

  MotorComponent::~MotorComponent() {
    if (m_controller_type == ControllerType::physical) {
      delete m_controller;
      m_controller = nullptr;
    }
  }

  void MotorComponent::postLoadResource(std::weak_ptr<GObject> parent_object) {
    m_parent_object = parent_object;

    m_controller_type = ControllerType::physical;
    auto controller_config =
        reinterpret_cast<PhysicalControllerConfig *> (m_motor_res.m_controller_config);
    m_controller = new CharacterController(controller_config->m_cylinder_shape);

    const TransformComponent::ptr transform_component =
        parent_object.lock()->tryGetComponentConst(TransformComponent);
    m_target_position = transform_component->getPosition();
  }

  void MotorComponent::getOffStuckDead() {
    acout << "Some get off stuck dead logic" << std::endl;
  }

  void MotorComponent::tick(float deltaTime) { tickPlayerMotor(deltaTime); }

  void MotorComponent::tickPlayerMotor(float deltaTime) {
    if (!m_parent_object.lock()) {
      return;
    }

    auto current_level = g_runtime_global_context.m_world_manager->getCurrentActiveLevel().lock();
    auto current_character = current_level->getCurrentActiveCharacter().lock();
    if (current_character == nullptr ||
        current_character->getObjectID() != m_parent_object.lock()->getID()) {
      return;
    }

    auto transform_component = m_parent_object.lock()->tryGetComponent(TransformComponent);
  }

  void
  MotorComponent::calculatedDesiredHorizontalMoveSpeed(unsigned int command, float delta_time) {

  }

  void MotorComponent::calculatedDesiredVerticalMoveSpeed(unsigned int command, float delta_time) {

  }

  void MotorComponent::calculatedDesiredMoveDirection(unsigned int command,
                                                      const float &object_rotation) {

  }

  void MotorComponent::calculatedDesiredDisplacement(float delta_time) {

  }

  void MotorComponent::calculatedTargetPosition(const glm::vec3 &&current_position) {

  }

}