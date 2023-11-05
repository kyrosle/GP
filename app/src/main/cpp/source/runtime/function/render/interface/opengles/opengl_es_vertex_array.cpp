#include "opengl_es_vertex_array.h"

#include <cassert>

#include "runtime/core/log/android_out.h"

namespace Gp {
  OpenglESVertexArray::OpenglESVertexArray() {
    glGenVertexArrays(1, &m_index);
  }

  OpenglESVertexArray::~OpenglESVertexArray() {
    glDeleteVertexArrays(1, &m_index);
  }


  void OpenglESVertexArray::Bind() const {
    glBindVertexArray(m_index);
  }

  void OpenglESVertexArray::UnBind() const {
    glBindVertexArray(0);
  }

  void OpenglESVertexArray::AddVertexBuffer(VertexBuffer::ptr &vertexBuffer) {
    assert(vertexBuffer->GetBufferLayout().GetCount() > 0);
    glBindVertexArray(m_index);
    vertexBuffer->Bind();

    BufferLayout layout = vertexBuffer->GetBufferLayout();

    int index = 0;

    for (const BufferElement &element: layout) {
      glEnableVertexAttribArray(index);
      if (element.HasInstancing()) {
        glBindBuffer(GL_ARRAY_BUFFER, element.GetInstancing());
        if (element.IsIntegerType()) {
          glVertexAttribPointer(
              index,
              GetShaderTypeDataCount(element.GetType()),
              ShaderDataTypeToOpenGLBaseType(element.GetType()),
              GL_FALSE,
              sizeof(float) * 2, //TODO: should parse a size from BufferElement
              (const void *) 0
          );
        } else {
          glVertexAttribPointer(
              index,
              GetShaderTypeDataCount(element.GetType()),
              ShaderDataTypeToOpenGLBaseType(element.GetType()),
              element.IsNormalized() ? GL_TRUE : GL_FALSE,
              sizeof(float) * 2,
              (const void *) 0
          );
        }
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glVertexAttribDivisor(index, 1);
        index++;
        continue;
      }
      if (element.IsIntegerType()) {
        glVertexAttribPointer(
            index,
            GetShaderTypeDataCount(element.GetType()),
            ShaderDataTypeToOpenGLBaseType(element.GetType()),
            GL_FALSE,
            layout.GetStride(),
            (const void *) (element.GetOffset())
        );
      } else {
        glVertexAttribPointer(
            index,
            GetShaderTypeDataCount(element.GetType()),
            ShaderDataTypeToOpenGLBaseType(element.GetType()),
            element.IsNormalized() ? GL_TRUE : GL_FALSE,
            layout.GetStride(),
            (const void *) (element.GetOffset())
        );
      }
      index++;
    }

    m_vertexBuffers.push_back(vertexBuffer);
  }

  void OpenglESVertexArray::SetIndexBuffer(IndexBuffer::ptr &indexBuffer) {
    glBindVertexArray(m_index);
    indexBuffer->Bind();
    m_indexBuffer = indexBuffer;
  }

  const std::vector<VertexBuffer::ptr> &
  OpenglESVertexArray::GetVertexBuffers() const {
    return m_vertexBuffers;
  }

  const IndexBuffer::ptr &OpenglESVertexArray::GetIndexBuffer() const {
    return m_indexBuffer;
  }
}