#include "render_index_buffer.h"

#include "runtime/function/render/interface/opengles/opengl_es_index_buffer.h"

namespace Gp {
  IndexBuffer *IndexBuffer::Create(uint32_t *indices, uint32_t size) {
    // opengl es
    return
      reinterpret_cast<IndexBuffer *>(new OpenglESIndexBuffer(indices, size));
  }
}