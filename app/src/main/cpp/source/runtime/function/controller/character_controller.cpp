#include "character_controller.h"

namespace Gp {
  CharacterController::CharacterController(const Cylinder &cylinder) {

  }

  glm::vec3
  CharacterController::move(const glm::vec3 &current_position, const glm::vec3 &displacement) {
    return glm::vec3(1.f);
  }
}
