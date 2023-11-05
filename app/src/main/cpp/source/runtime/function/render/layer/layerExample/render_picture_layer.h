#pragma once

#include <memory>

#include "runtime/function/render/render_render2D.h"
#include "runtime/function/render/render_command.h"
#include "runtime/function/render/render_camera_controller.h"
#include "runtime/function/render/render_texture.h"
#include "runtime/function/render/layer/render_layer.h"

namespace Gp {

  class RenderPictureLayer : public RenderLayer {
  public:
    typedef std::shared_ptr<RenderPictureLayer> ptr;

    RenderPictureLayer(const std::string &name = "layer");

    ~RenderPictureLayer();

    // Init()
    void OnAttach() override;

    // Shutdown()
    void OnDetach() override;

    void OnEvent(Event::ptr event) override;

    void OnUpdate(const float deltaTime) override;

    void OnImGuiRender() override;

  private:
    RenderCameraController::ptr m_camera;
    Texture2D::ptr m_texture;
    glm::vec4 m_flatColor = glm::vec4(0.2, 0.3, 0.8, 1.0);
  };

}