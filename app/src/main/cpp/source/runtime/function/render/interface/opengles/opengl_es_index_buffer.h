#pragma once

#include <memory>

#include "runtime/function/render/render_index_buffer.h"
#include "runtime/function/render/render_buffer.h"

namespace Gp {

  class OpenglESIndexBuffer : public IndexBuffer {
  public:
    typedef std::shared_ptr<OpenglESIndexBuffer> ptr;
    typedef std::unique_ptr<OpenglESIndexBuffer> u_ptr;

    OpenglESIndexBuffer(uint32_t *indices, uint32_t size); // static

    virtual ~OpenglESIndexBuffer() override;

    uint32_t GetCount() const override;

    void Bind() const override;

    void UnBind() const override;

  private:
    uint32_t m_count;
    uint32_t m_indexBuffer;
  };

}

