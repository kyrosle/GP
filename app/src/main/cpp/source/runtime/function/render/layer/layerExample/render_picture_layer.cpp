#include "render_picture_layer.h"

#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

#include "runtime/function/global/global_context.h"
#include "runtime/engine.h"

namespace Gp {

  RenderPictureLayer::RenderPictureLayer(const std::string &name)
    : RenderLayer(name),
      m_camera(std::make_shared<RenderCameraController>(1.6667f, 1.0f)) {
    Renderer2D::init();
    m_texture = Texture2D::Create("Resources/HeadIcon.jpg");
  }

  RenderPictureLayer::~RenderPictureLayer() {
    Renderer2D::shutdown();
  }

  void RenderPictureLayer::OnAttach() {
    acout << "RenderPictureLayer attach" << std::endl;
  }

  void RenderPictureLayer::OnDetach() {
    acout << "RenderPictureLayer detach" << std::endl;
  }

  void RenderPictureLayer::OnEvent(Event::ptr event) {
  }

  void RenderPictureLayer::OnUpdate(const float deltaTime) {
    RenderCommand::Clear();
    RenderCommand::SetClearColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

    Renderer2D::beginScene(m_camera->getCamera());
    auto time = GameEngine::getRunningTimeMs();
    auto x_offset = std::sin(time);
    auto y_offset = std::cos(time);
    acout << "running time=" << time << std::endl;
//    acout << "x=" << x_offset << " y=" << y_offset << std::endl;
    // red
    Renderer2D::drawQuad(
      {x_offset, y_offset, 0},
      time * 100,
      {0.5, 0.5},
      {1.0f, 0.0f, 0.0f, 1.0f}
    );
    // green
    Renderer2D::drawQuad(
      {1 + y_offset, 1 + x_offset, 0},
      30 + time * 50,
      {0.5, 0.5},
      {0.0f, 1.0f, 0.0f, 1.0f}
    );
    // blue
    Renderer2D::drawQuad(
      {-1 + x_offset, -1 + y_offset, 0},
      60 + time * 10,
      {0.5, 0.5},
      {0.0f, 0.0f, 1.0f, 1.0f}
    );

//    Renderer2D::drawQuad(
//      {0, 0, 0},
//      {1.0, 1.0},
//      m_texture
//    );
    Renderer2D::endScene();
  }


  void RenderPictureLayer::OnImGuiRender() {
    ImGuiIO &io = ImGui::GetIO();
    ImGui::SetWindowSize("Dear ImGui Demo", {2000, 1000});
    io.FontGlobalScale = 3.0f;
    ImGui::Begin("Render Picture Layer");
    {
      ImGui::ColorEdit4("Color editor", (float *) (&m_flatColor));
    }
    ImGui::End();
  }
}