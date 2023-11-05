#pragma once

#include <memory>

#include "runtime/function/render/render_buffer.h"

namespace Gp {

  class VertexBuffer {
  public:
    typedef std::shared_ptr<VertexBuffer> ptr;
    typedef std::unique_ptr<VertexBuffer> u_ptr;

    virtual ~VertexBuffer() {};

    virtual void Bind() const = 0;

    virtual void UnBind() const = 0;

    virtual BufferLayout &GetBufferLayout() = 0;

    virtual void SetBufferLayout(const BufferLayout &layout) = 0;

    virtual void SetData(uint32_t pos, void *data, uint32_t len) = 0;

    // static buffer
    static VertexBuffer *Create(const float *vertices, uint32_t size);

    // dynamic buffer
    static VertexBuffer *Create(uint32_t size);

  private:
    uint32_t m_vertexBuffer;
  };

}

