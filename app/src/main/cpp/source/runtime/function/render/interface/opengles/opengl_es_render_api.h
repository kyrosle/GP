#pragma once

#include <memory>

#include "runtime/function/render/render_api.h"

namespace Gp {

  class OpenglESRenderApi : public RendererAPI {
  public:
    typedef std::shared_ptr<OpenglESRenderApi> ptr;

    virtual void Init() const override;

    virtual void Clear() const override;

    virtual void SetClearColor(const glm::vec4 &) const override;

    virtual void DrawIndexed(const VertexArray::ptr &) const override;

    virtual void DrawIndexedBatch(const VertexArray::ptr &, const uint32_t) const override;

    virtual void DrawIndexedLine(const VertexArray::ptr &) const override;

    virtual void DrawIndexedPoint(const VertexArray::ptr &) const override;
  };

}