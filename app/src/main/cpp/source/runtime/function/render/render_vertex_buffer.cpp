#include "render_vertex_buffer.h"

#include "runtime/function/render/interface/opengles/opengl_es_vertex_buffer.h"

namespace Gp {
  VertexBuffer *VertexBuffer::Create(const float *vertices, uint32_t size) {
    // opengl es
    return reinterpret_cast<VertexBuffer *>(
        new OpenglESVertexBuffer(vertices, size));
  }

  VertexBuffer *VertexBuffer::Create(uint32_t size) {
    // opengl es
    return reinterpret_cast<VertexBuffer *> (
        new OpenglESVertexBuffer(size));
  }
}