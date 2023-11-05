#include "render_camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Gp {
  RenderCamera::RenderCamera(
      ProjectionType type,
      float leftOrFov,
      float rightOrAspect,
      float bottomOrZNear,
      float topOrZFar) {
    m_zoomLevel = topOrZFar;
    m_aspectRatio = rightOrAspect / m_zoomLevel;

    if (type == ProjectionType::Orthographic) {
      m_projectionMatrix =
          glm::ortho(leftOrFov, rightOrAspect, bottomOrZNear, topOrZFar, -1.0f, 1.0f);
      m_viewMatrix = glm::mat4(1.f);
    } else if (type == ProjectionType::Perspective) {
      //TODO: 2d not support
    }

    m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
  }

  void RenderCamera::OnResize(uint32_t width, uint32_t height) {
    m_aspectRatio =
        static_cast<float>(width) / static_cast<float>(height);
    if (m_type == ProjectionType::Orthographic) {
      setProjectMatrix(
          -m_aspectRatio * m_zoomLevel,
          m_aspectRatio * m_zoomLevel,
          -m_zoomLevel, m_zoomLevel);
    }
  }

  void RenderCamera::setPosition(const glm::vec3 &position) {
    if (m_position != position) {
      m_position = position;
      recalculateViewMatrix();
    }
  }

  void RenderCamera::setRotation(glm::quat rotation) {
    if (m_rotation != rotation) {
      m_rotation = rotation;
      recalculateViewMatrix();
    }
  }

  void RenderCamera::setProjectMatrix(
      float leftOrFov,
      float rightOrAspect,
      float bottomOrZNear,
      float topOrZFar) {
    if (m_type == ProjectionType::Orthographic) {
      m_projectionMatrix =
          glm::ortho(leftOrFov, rightOrAspect, bottomOrZNear, topOrZFar, -1.f, 1.f);
    } else if (m_type == ProjectionType::Perspective) {
      //TODO: 2d no support
    }
    // update vp mat4
    m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
  }

  void RenderCamera::recalculateViewMatrix() {
    m_viewMatrix = glm::lookAt(m_position, m_position + getLocalForward(), getLocalUp());
    m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
  }
}