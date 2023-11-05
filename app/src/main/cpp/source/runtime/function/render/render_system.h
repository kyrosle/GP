#pragma once

#include <memory>
#include <string>

#include "runtime/function/render/window_system.h"
#include "runtime/function/render/render_render2D.h"
#include "runtime/function/render/render_render2D_batch.h"
#include "runtime/function/render/layer/render_layer.h"
#include "runtime/function/render/layer/render_layer_stack.h"
#include "runtime/function/render/layer/layerExample/imgui_layer.h"
#include "runtime/function/render/render_swap_context.h"
#include "runtime/function/render/render_scene.h"
#include "runtime/function/render/render_camera_controller.h"
#include "runtime/function/render/render_resource.h"
#include "runtime/function/render/render_pipeline_base.h"


namespace Gp {
  struct RenderSystemInitInfo {
    // window system ptr
    WindowSystem::ptr window_system;
    struct android_app *app;
    // debug draw manager ptr
  };

  class RenderSystem {
  public:
    friend class WindowSystem;

    typedef std::shared_ptr<RenderSystem> ptr;

    RenderSystem() = default;

    ~RenderSystem();

    void initialize(const RenderSystemInitInfo &init_info);

    void tick(float delta_time);

    void clear();

//    void pushLayer(RenderLayer::ptr layer) { m_layer_stack.pushLayer(layer); }
//
//    RenderLayer::ptr popLayer() { return m_layer_stack.popLayer(); }
//
    ImguiLayer::ptr getImguiLayer() const { return m_imgui_layer; }
//
//    RenderLayerStack &getRenderLayerStack() { return m_layer_stack; }

    RenderSwapContext &getSwapContext() { return m_swap_context; }

    glm::mat4
    getViewProjectionMatrix() { return m_render_camera->getCamera().getViewProjectionMatrix(); }

    void swapLogicRenderData() { m_swap_context.swapLogicRenderData(); }

  private:
    RenderSwapContext m_swap_context;

    RenderCameraController::ptr m_render_camera;
    RenderScene::ptr m_render_scene;
    RenderResourceBase::ptr m_render_resource;
    RenderPipelineBase::ptr m_render_pipeline;

//    RenderLayerStack m_layer_stack;
    ImguiLayer::ptr m_imgui_layer;

    void processSwapData();
  };
}
