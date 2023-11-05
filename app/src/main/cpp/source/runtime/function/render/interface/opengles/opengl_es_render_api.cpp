#include "opengl_es_render_api.h"

namespace Gp {

  void OpenglESRenderApi::Init() const {
    glEnable(GL_BLEND);
    glBlendFuncSeparate(
        GL_SRC_ALPHA,
        GL_ONE_MINUS_SRC_ALPHA,
        GL_ONE,
        GL_ZERO
    );
    glEnable(GL_DEPTH_TEST);
  }

  void OpenglESRenderApi::Clear() const {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }

  void OpenglESRenderApi::SetClearColor(const glm::vec4 &color) const {
    glClearColor(color.x, color.y, color.z, color.w);
  }

  void
  OpenglESRenderApi::DrawIndexed(const VertexArray::ptr &vertexArray) const {
    vertexArray->Bind();
    glDrawElements(
        GL_TRIANGLES,
        static_cast<int>(vertexArray->GetIndexBuffer()->GetCount()),
        GL_UNSIGNED_INT, nullptr);
    vertexArray->UnBind();
  }

  void
  OpenglESRenderApi::DrawIndexedBatch(const VertexArray::ptr &vertexArray,
                                      const uint32_t instance_count) const {
    vertexArray->Bind();
    glDrawElementsInstanced(
        GL_TRIANGLES,
        static_cast<int>(vertexArray->GetIndexBuffer()->GetCount()),
        GL_UNSIGNED_INT, nullptr, static_cast<int>(instance_count));
    vertexArray->UnBind();
  }

  void OpenglESRenderApi::DrawIndexedLine(const VertexArray::ptr &vertexArray) const {
    vertexArray->Bind();
    glDrawElements(
        GL_LINES,
        static_cast<int>(vertexArray->GetIndexBuffer()->GetCount()),
        GL_UNSIGNED_INT, nullptr);
    vertexArray->UnBind();
  }

  void OpenglESRenderApi::DrawIndexedPoint(const VertexArray::ptr &vertexArray) const {
    vertexArray->Bind();
    glDrawElements(
        GL_POINTS,
        static_cast<int>(vertexArray->GetIndexBuffer()->GetCount()),
        GL_UNSIGNED_INT, nullptr);
    vertexArray->UnBind();
  }
}
