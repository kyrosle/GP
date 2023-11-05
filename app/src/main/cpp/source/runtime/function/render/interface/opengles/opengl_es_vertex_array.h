#pragma once

#include <memory>

#include "runtime/function/render/render_vertex_array.h"
#include "runtime/function/render/render_buffer.h"

namespace Gp {

  class OpenglESVertexArray : public VertexArray {
  public:
    typedef std::shared_ptr<OpenglESVertexArray> ptr;
    typedef std::shared_ptr<OpenglESVertexArray> u_ptr;

    OpenglESVertexArray();

    ~OpenglESVertexArray() override;

    void Bind() const override;

    void UnBind() const override;

    void AddVertexBuffer(VertexBuffer::ptr &vertexBuffer) override;

    void SetIndexBuffer(IndexBuffer::ptr &indexBuffer) override;

    const std::vector<VertexBuffer::ptr> &GetVertexBuffers() const override;

    const IndexBuffer::ptr &GetIndexBuffer() const override;

  private:
    unsigned int m_index;
    std::vector<VertexBuffer::ptr> m_vertexBuffers;
    IndexBuffer::ptr m_indexBuffer;
  };

}