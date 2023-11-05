#include "render_pipeline_base.h"

#include <glm/glm.hpp>

#include "runtime/function/render/render_command.h"

namespace Gp {

  void RenderPipelineBase::preparePassData(
      std::shared_ptr<RenderResourceBase> render_resource) {
    m_main_camera_pass->preparePassData(render_resource);
    RenderCommand::SetClearColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    RenderCommand::Clear();
  }

  void RenderPipelineBase::forwardRender(
      std::shared_ptr<RenderResourceBase> render_resource) {
  }

  void RenderPipelineBase::deferredRender(
      std::shared_ptr<RenderResourceBase> render_resource) {}
}