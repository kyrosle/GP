#include "render_control.h"

namespace Gp {
  void RenderControl::Submit(
    const Shader::ptr &shader,
    const VertexArray::ptr &vertexArray,
    const glm::mat4 &transform
  ) {
    shader->Bind();

    // shader uniform transfer `u_ViewProjection`
    // shader uniform transfer `u_Transform`

    vertexArray->Bind();
    RenderCommand::DrawIndexed(vertexArray);
    vertexArray->UnBind();

    shader->UnBind();
  }

  void RenderControl::BeginScene() {

  }

  void RenderControl::EndScene() {

  }
}