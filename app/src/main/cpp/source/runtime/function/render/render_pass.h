#pragma once

#include <vector>
#include <GLES3/gl3.h>

#include "runtime/function/render/render_pass_base.h"
#include "runtime/function/render/render_common.h"

namespace Gp {
  struct VisibleNodes {
    std::vector<RenderMeshNode> *p_main_camera_visible_mesh_nodes{nullptr};
  };

  class RenderPass : public RenderPassBase {
  public:
    std::vector<GLuint> m_texture_unints;
    std::vector<GLuint> m_shader_programs;
    std::vector<GLboolean> m_state_flags;

    void initialize(const Gp::RenderPassInitInfo *init_info) override;

    void postInitialize() override;

    virtual void draw();

    static VisibleNodes m_visible_nodes;

  private:
  };

}

