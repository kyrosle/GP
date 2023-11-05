#include "render_vertex_array.h"

#include "runtime/function/render/interface/opengles/opengl_es_vertex_array.h"

namespace Gp {
  VertexArray *VertexArray::Create() {
    // opengl es
    return reinterpret_cast<VertexArray *>(new OpenglESVertexArray());
  }
}
