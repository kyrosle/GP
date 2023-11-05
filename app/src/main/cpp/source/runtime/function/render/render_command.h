#pragma once

#include "runtime/function/render/render_api.h"

namespace Gp {

  class RenderCommand {
  public:
    static void Clear();

    static void SetClearColor(const glm::vec4 &color);

    static void DrawIndexed(const VertexArray::ptr &vertexArray);

    // the relevant shader should
    // have set the layout:
    // layout (location = ?) in vec2 aOffset;
    static void DrawIndexedBatch(
        const VertexArray::ptr &vertexArray,
        const uint32_t instanceCount);

    static void DrawIndexedLine(const VertexArray::ptr &vertexArray);

    static void DrawIndexedPoint(const VertexArray::ptr &vertexArray);

  private:
    static RendererAPI *s_renderApi;
  };

}

