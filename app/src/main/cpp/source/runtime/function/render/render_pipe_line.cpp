#include "render_pipe_line.h"

#include "runtime/function/render/passes/main_camera_pass.h"

namespace Gp {
  void RenderPipeline::initialize(RenderPipelineInitInfo init_info) {
    m_main_camera_pass = std::make_shared<MainCameraPass>();
    m_main_camera_pass->initialize(nullptr);
  }

  void RenderPipeline::forwardRender(std::shared_ptr<RenderResourceBase> render_resource) {
    dynamic_cast<MainCameraPass *>(m_main_camera_pass.get())->draw();
  }

  void RenderPipeline::deferredRender(std::shared_ptr<RenderResourceBase> render_resource) {
    RenderPipelineBase::deferredRender(render_resource);
  }

  void RenderPipeline::passUpdateAfterRecreateSwapChain() {}
}