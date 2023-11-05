#pragma once

#include <memory>

#include "runtime/function/render/render_camera.h"

namespace Gp {

  class RenderCameraController {
  public:
    typedef std::shared_ptr<RenderCameraController> ptr;

    // 16:9(1.7778) or 4:3(1.3333)
    RenderCameraController(float radio, float zoom);

    void tick(const float delta_time);

    void onEvent();

    RenderCamera &getCamera() { return m_camera; }

    const RenderCamera &getCamera() const { return m_camera; }

  private:
    void onZoomCamera(float scroll_offset);

  private:
    float m_zoomLevel = 0.0f;
    float m_zoomSpeed = 120.0f;
    // aspectRatio = width / height
    float m_aspectRadio = 1.26667f;
    float m_rotateSpeed = 20.0f;
    bool m_rotatable = true;

    glm::vec2 m_lastMousePos = {-1, -1};
    glm::vec2 m_deltaPos = {0, 0}; // perspective camera

    RenderCamera m_camera;
  };

}
