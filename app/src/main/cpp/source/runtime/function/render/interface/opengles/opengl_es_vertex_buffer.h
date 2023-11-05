#pragma once

#include <memory>

#include "runtime/function/render/render_vertex_buffer.h"
#include "runtime/function/render/render_buffer.h"

namespace Gp {

  class OpenglESVertexBuffer : public VertexBuffer {
  public:
    typedef std::shared_ptr<OpenglESVertexBuffer> ptr;
    typedef std::unique_ptr<OpenglESVertexBuffer> u_ptr;

    // static vertex
    OpenglESVertexBuffer(const float *vertexes, uint32_t size);

    // dynamic vertex
    OpenglESVertexBuffer(uint32_t size);

    virtual ~OpenglESVertexBuffer();

    void Bind() const override;

    void UnBind() const override;

    void SetData(uint32_t pos, void *data, uint32_t len) override;

    BufferLayout &GetBufferLayout() override { return m_layout; }

    void SetBufferLayout(const BufferLayout &layout) override {
      m_layout = layout;
    }

  private:
    uint32_t m_vertexBuffer;
    BufferLayout m_layout;
  };

}