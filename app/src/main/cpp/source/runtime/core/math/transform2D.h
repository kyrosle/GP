#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Gp {
  class Transform2D {
  public:
    glm::vec3 m_position{glm::vec3(0.f, 0.f, 0.f)};
    glm::vec3 m_scale{glm::vec3(1.f, 1.f, 0.f)};
    float m_rotation = 0.f;

    Transform2D() = default;

    Transform2D(const glm::vec3 &position, float rotation,
                const glm::vec3 &scale)
        : m_position{position}, m_scale{scale}, m_rotation{rotation} {}

    glm::mat4 getMatrix() const {
      glm::mat4 model = glm::mat4(1.0f);
      // (1). translate
      // (2). rotate
      // (3). zoom

      // translate
      model = glm::translate(model, m_position);

      // rotate
      model = glm::rotate(model, glm::radians(m_rotation), glm::vec3(0.f, 0.f, 1.f));
//      model = glm::translate(model, glm::vec3(-0.5f * m_scale.x, -0.5f * m_scale.y, 0.f));

      // zoom
      model = glm::scale(model, m_scale);

      return model;
    }
  };
}