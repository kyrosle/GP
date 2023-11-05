#pragma once

#include <memory>

#include "runtime/core/math/math_header.h"
#include "runtime/function/render/render_vertex_buffer.h"
#include "runtime/function/render/render_index_buffer.h"
#include "runtime/function/render/render_vertex_array.h"

namespace Gp {
  class TextureData;

  // mesh
  struct MeshNodeData {
    VertexBuffer::ptr m_vertex_buffer;
    IndexBuffer::ptr m_index_buffer;
    BufferLayout m_buffer_layout;
    VertexArray::ptr m_vertex_array;
  };

  // texture
  struct TextureNodeData {
    std::shared_ptr<TextureData> m_texture;
  };

  // nodes
  struct RenderMeshNode {
    const glm::mat4 *model_matrix{nullptr};
    MeshNodeData *ref_mesh{nullptr};
    TextureNodeData *ref_texture{nullptr};
    uint32_t node_id;
  };

  struct StaticMeshNodeData {
  };
  struct RenderStaticMeshNode {
  };

}