#include "opengl_es_vertex_buffer.h"

namespace Gp {
#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-pro-type-member-init"

  OpenglESVertexBuffer::OpenglESVertexBuffer(const float *vertexes,
                                             uint32_t size) {
    glGenBuffers(1, &m_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, static_cast<int>(size), vertexes,
                 GL_STATIC_DRAW);
  }


  OpenglESVertexBuffer::OpenglESVertexBuffer(uint32_t size) {
    glGenBuffers(1, &m_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, static_cast<int>(size), nullptr,
                 GL_DYNAMIC_DRAW);
  }

#pragma clang diagnostic pop

  OpenglESVertexBuffer::~OpenglESVertexBuffer() {
    glDeleteBuffers(1, &m_vertexBuffer);
  }

  void OpenglESVertexBuffer::Bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
  }

  void OpenglESVertexBuffer::UnBind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  void OpenglESVertexBuffer::SetData(uint32_t pos, void *data, uint32_t len) {
    glBufferSubData(GL_ARRAY_BUFFER, static_cast<long>(pos),
                    static_cast<long>(len), data);
  }

}