#pragma once

#include <memory>

namespace Gp {
  class RenderResourceBase;

  struct RenderPassInitInfo {};

  struct RenderPassCommonInfo {
    std::shared_ptr<RenderResourceBase> render_resource;
  };

  class RenderPassBase {
  public:
    virtual void initialize(const RenderPassInitInfo *init_info) = 0;

    virtual void postInitialize();

    virtual void setCommonInfo(RenderPassCommonInfo common_info);

    virtual void preparePassData(std::shared_ptr<RenderResourceBase> render_resource);

  protected:
    std::shared_ptr<RenderResourceBase> m_render_resource;
  };

}

