#include "opengl_es_index_buffer.h"

namespace Gp {
  OpenglESIndexBuffer::OpenglESIndexBuffer(uint32_t *indices, uint32_t size) {
    m_count = size / sizeof(uint32_t);
    glGenBuffers(1, &m_indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<long>(size), indices,
                 GL_STATIC_DRAW);
  }

  OpenglESIndexBuffer::~OpenglESIndexBuffer() {
    glDeleteBuffers(1, &m_indexBuffer);
  }

  uint32_t OpenglESIndexBuffer::GetCount() const {
    return m_count;
  }

  void OpenglESIndexBuffer::Bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
  }

  void OpenglESIndexBuffer::UnBind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }
}