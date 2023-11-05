#pragma once

#include <unordered_map>

#include "runtime/function/render/render_pass.h"
#include "runtime/function/render/render_shader.h"

namespace Gp {
  class RenderResourceBase;

  struct MainCameraPassInitInfo : RenderPassInitInfo {};

  class MainCameraPass : public RenderPass {
  public:
    typedef std::shared_ptr<MainCameraPass> ptr;

    void initialize(const RenderPassInitInfo *init_info) override final;

    void preparePassData(std::shared_ptr<RenderResourceBase> render_resource) override final;

    void draw() override;

  private:
    std::unordered_map<std::string, Shader::ptr> m_shader;
    glm::mat4 ViewProjectionMatrix;
  };

}

