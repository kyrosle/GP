#pragma once

#include <glm/glm.hpp>
#include <memory>

#include "runtime/function/render/render_vertex_array.h"

namespace Gp {
  class RendererAPI {
  public:
    typedef std::shared_ptr<RendererAPI> ptr;
    typedef std::unique_ptr<RendererAPI> u_ptr;

    enum class ApiType {
      None, OpenglES
    };

    inline static ApiType GetApiType() { return s_apiType; }

  public:
    virtual void Init() const = 0;

    virtual void Clear() const = 0;

    virtual void SetClearColor(const glm::vec4 &) const = 0;

    virtual void DrawIndexed(const VertexArray::ptr &) const = 0;

    virtual void DrawIndexedBatch(const VertexArray::ptr &, const uint32_t) const = 0;

    virtual void DrawIndexedLine(const VertexArray::ptr &) const = 0;

    virtual void DrawIndexedPoint(const VertexArray::ptr &) const = 0;

  private:
    static ApiType s_apiType;
  };

}

