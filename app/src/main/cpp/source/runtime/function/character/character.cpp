#include "character.h"

#include "runtime/function/framework/component/transform/transform_component.h"
#include "runtime/function/framework/component/motor/motor_component.h"

namespace Gp {
  Character::Character(GObject::ptr character_object) {
    setObject(std::move(character_object));
  }

  void Character::setObject(GObject::ptr gObject) {
    m_character_object = std::move(gObject);
    // fetch meta information from component
    // m_position
    // m_rotation
  }

  GObjectID Character::getObjectID() const {
    if (m_character_object) {
      return m_character_object->getID();
    }
    return k_invalid_gobject_id;
  }

  void Character::tick(float deltaTime) {
    if (m_character_object == nullptr) {
      return;
    }

    TransformComponent::ptr transformComponent =
        m_character_object->tryGetComponent(TransformComponent);

    MotorComponent::ptr motorComponent =
        m_character_object->tryGetComponent(MotorComponent);

  }

}