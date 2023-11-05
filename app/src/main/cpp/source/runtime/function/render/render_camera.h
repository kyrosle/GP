#pragma once

#include <memory>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "runtime/core/math/math_header.h"

namespace Gp {

  class RenderCamera {
  public:
    enum class ProjectionType { Perspective = 0, Orthographic = 1 };
  public:
    typedef std::shared_ptr<RenderCamera> ptr;

    RenderCamera(ProjectionType type, float left, float right, float bottom, float top);

    void OnResize(uint32_t width, uint32_t height);

    // read or modify camera position and direction, used in setting view matrix
    const glm::vec3 &getPosition() const { return m_position; }

    void setPosition(const glm::vec3 &position);

    glm::quat getRotation() const { return m_rotation; }

    void setRotation(glm::quat rotation);

    // return 3 matrix interface, used in setting projection matrix
    const glm::mat4 &getProjectMatrix() const { return m_projectionMatrix; }

    const glm::mat4 &getViewMatrix() const { return m_viewMatrix; }

    const glm::mat4 &
    getViewProjectionMatrix() const { return m_viewProjectionMatrix; }

    void setProjectMatrix(float left, float right, float bottom, float top);

    bool isProjectiveCamera() { return m_type == ProjectionType::Perspective; }

    bool isOrthographicCamera() { return m_type == ProjectionType::Orthographic; }

    glm::vec3 getLocalForward() { return m_rotation * glm::vec3{0, 0, 1}; }

    glm::vec3 getLocalRight() { return m_rotation * glm::vec3{1, 0, 0}; }

    glm::vec3 getLocalUp() { return m_rotation * glm::vec3{0, 1, 0}; }

  private:
    void recalculateViewMatrix();

  private:
    glm::mat4 m_projectionMatrix;
    glm::mat4 m_viewMatrix;
    // calculate cache
    glm::mat4 m_viewProjectionMatrix;

    float m_aspectRatio;
    float m_zoomLevel = 1.f;

    // projection camera position
    glm::vec3 m_position = glm::vec3(0);
    // w,x,y,z initial direction: -z
    glm::quat m_rotation = {0, 0, 1, 0};

    ProjectionType m_type = ProjectionType::Orthographic;
  };

}

