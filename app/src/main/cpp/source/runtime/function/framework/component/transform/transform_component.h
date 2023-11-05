#pragma once

#include <memory>

#include "runtime/core/math/math_header.h"
#include "runtime/function/framework/component/component.h"
#include "runtime/resource/res_type/common/object.h"

namespace Gp {

  class TransformComponent : public ComponentBase {
  public:
    typedef std::shared_ptr<TransformComponent> ptr;

    TransformComponent() : ComponentBase("TransformComponent") {}

    void postLoadResource(std::weak_ptr<GObject> parent_object) override;

    glm::vec3 getPosition() const { return m_transform_buffer[m_current_index].m_position; }

    glm::vec3 getScale() const { return m_transform_buffer[m_current_index].m_scale; }

    float getRotation() const { return m_transform_buffer[m_current_index].m_rotation; }

    void setPosition(const glm::vec3 &new_transform);

    void setScale(const glm::vec3 &new_scale);

    void setRotation(const float &new_rotation);

    const Transform2D &getTransform() const { return m_transform_buffer[m_current_index]; }

    Transform2D &getTransform() { return m_transform_buffer[m_current_index]; }

    glm::mat4 getMatrix() const { return m_transform_buffer[m_current_index].getMatrix(); }

    void tick(float deltaTime) override;

    void tryUpdateRigidBodyComponent();

  protected:
    Transform2D m_transform;
    Transform2D m_transform_buffer[2];
    size_t m_current_index{0};
    size_t m_next_index{1};
  };
}
