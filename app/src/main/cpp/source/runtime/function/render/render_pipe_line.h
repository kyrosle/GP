#pragma once

#include "runtime/function/render/render_pipeline_base.h"

namespace Gp {

  class RenderPipeline : public RenderPipelineBase {
  public:
    virtual void initialize(RenderPipelineInitInfo init_info) override final;

    virtual void forwardRender(
        std::shared_ptr<RenderResourceBase> render_resource) override final;

    virtual void deferredRender(
        std::shared_ptr<RenderResourceBase> render_resource) override final;

    void passUpdateAfterRecreateSwapChain();
  };

}
