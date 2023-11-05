#pragma once

#include <memory>

#include "runtime/function/render/render_pass_base.h"

namespace Gp {
  class RenderResourceBase;

  struct RenderPipelineInitInfo {
    std::shared_ptr<RenderResourceBase> render_resource;
  };

  class RenderPipelineBase {
    friend class RenderSystem;

  public:
    typedef std::shared_ptr<RenderPipelineBase> ptr;

    virtual ~RenderPipelineBase() {}

    virtual void clear() {};

    virtual void initialize(RenderPipelineInitInfo init_info) = 0;

    virtual void preparePassData(std::shared_ptr<RenderResourceBase> render_resource);

    virtual void forwardRender(std::shared_ptr<RenderResourceBase> render_resource);

    virtual void deferredRender(std::shared_ptr<RenderResourceBase> render_resource);

  protected:
    std::shared_ptr<RenderPassBase> m_main_camera_pass;
  };

}

