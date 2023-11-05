#include "render_command.h"

#include "runtime/function/render/interface/opengles/opengl_es_render_api.h"

namespace Gp {
  RendererAPI *RenderCommand::s_renderApi = new OpenglESRenderApi();

  void RenderCommand::Clear() {
    s_renderApi->Clear();
  }

  void RenderCommand::SetClearColor(const glm::vec4 &color) {
    s_renderApi->SetClearColor(color);
  }

  void RenderCommand::DrawIndexed(const VertexArray::ptr &vertexArray) {
    s_renderApi->DrawIndexed(vertexArray);
  }

  void RenderCommand::DrawIndexedLine(const VertexArray::ptr &vertexArray) {
    s_renderApi->DrawIndexedLine(vertexArray);
  }

  void RenderCommand::DrawIndexedPoint(const VertexArray::ptr &vertexArray) {
    s_renderApi->DrawIndexedPoint(vertexArray);
  }

  void
  RenderCommand::DrawIndexedBatch(
      const VertexArray::ptr &vertexArray,
      const uint32_t instanceCount) {
    s_renderApi->DrawIndexedBatch(vertexArray, instanceCount);
  }
}