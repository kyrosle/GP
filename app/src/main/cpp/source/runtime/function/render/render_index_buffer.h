#pragma once

#include <memory>
#include <GLES3/gl3.h>

namespace Gp {

  class IndexBuffer {
  public:
    typedef std::shared_ptr<IndexBuffer> ptr;
    typedef std::unique_ptr<IndexBuffer> u_ptr;

    virtual ~IndexBuffer() {}

    virtual void Bind() const = 0;

    virtual void UnBind() const = 0;

    virtual uint32_t GetCount() const = 0;

    static IndexBuffer *Create(uint32_t *indices, uint32_t size);

  private:
    uint32_t m_indexBuffer;
  };

}

