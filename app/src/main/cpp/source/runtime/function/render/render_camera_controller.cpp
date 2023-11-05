#include "render_camera_controller.h"

namespace Gp {
  RenderCameraController::RenderCameraController(float radio, float zoom)
      : m_camera(RenderCamera::ProjectionType::Orthographic,
                 -radio * zoom, radio * zoom, -zoom, zoom) {}

  void RenderCameraController::tick(const float delta_time) {}

  void RenderCameraController::onEvent() {}

  void RenderCameraController::onZoomCamera(float scroll_offset) {}
}