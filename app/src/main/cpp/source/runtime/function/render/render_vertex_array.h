#pragma once

#include <memory>

#include "runtime/function/render/render_vertex_buffer.h"
#include "runtime/function/render/render_index_buffer.h"

namespace Gp {

  class VertexArray {
  public:
    typedef std::shared_ptr<VertexArray> ptr;
    typedef std::unique_ptr<VertexArray> u_ptr;

    virtual ~VertexArray() {};

    virtual void Bind() const = 0;

    virtual void UnBind() const = 0;

    static VertexArray *Create();

    virtual void AddVertexBuffer(VertexBuffer::ptr &) = 0;

    virtual void SetIndexBuffer(IndexBuffer::ptr &) = 0;

    virtual const std::vector<VertexBuffer::ptr> &GetVertexBuffers() const
    = 0;

    virtual const IndexBuffer::ptr &GetIndexBuffer() const = 0;
  };

}
