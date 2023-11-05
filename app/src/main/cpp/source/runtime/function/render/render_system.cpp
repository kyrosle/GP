#include "render_system.h"

#include <memory>

#include "runtime/core/log/android_out.h"
#include "runtime/function/render/render_utility.h"

#include "runtime/function/render/render_command.h"
#include "runtime/function/render/render_camera_controller.h"
#include "runtime/function/render/render_texture.h"
#include "runtime/function/render/render_render2D.h"
#include "runtime/function/render/render_render2D_batch.h"
#include "runtime/function/render/render_pipe_line.h"
#include "runtime/function/render/render_shader_library.h"

#include "runtime/function/render/layer/layerExample/render_picture_layer.h"

namespace Gp {
  void RenderSystem::initialize(const RenderSystemInitInfo &init_info) {
    //TODO: render initialize
    Renderer2D::init();
    Renderer2DBatch::init();
//    RenderShaderLibrary::Load("FlatColorShader");
//    RenderShaderLibrary::Load("TextureShader");

    m_render_resource = std::make_shared<RenderResource>();
    // upload global render resource (level_resource_desc)

    // setup render camera
    // aspectRatio = 2159 / 1080 ≈ 1.998 my testing phone screen size
    m_render_camera =
        std::make_shared<RenderCameraController>(1.998f, 4.f);

    // setup up render scene
    m_render_scene = std::make_shared<RenderScene>();
    m_render_scene->setVisibleNodesReference();

    // initialize render pipeline
    RenderPipelineInitInfo pipeline_init_info;
    pipeline_init_info.render_resource = m_render_resource;
    m_render_pipeline = std::make_shared<RenderPipeline>();
    m_render_pipeline->initialize(pipeline_init_info);

    // initialize imgui framework(imgui layer)
    m_imgui_layer = std::make_shared<ImguiLayer>();
    m_imgui_layer->OnAttach();

    // Render Picture Layer
//    auto render_picture_layer = new RenderPictureLayer("Picture Layer");
//    pushLayer(RenderLayer::ptr(render_picture_layer));
//    // Imgui Layer
  }

  // render tick
  void RenderSystem::tick(float delta_time) {
    // process swap data between logic and render contexts
    processSwapData();
    // prepare render command context
    // update per frame buffer
    m_render_resource->updatePerFrameBuffer(m_render_scene, m_render_camera->getCamera());

    // update pre-frame visible objects
    m_render_scene->updateVisibleObjects(
        std::static_pointer_cast<RenderResource>(m_render_resource),
        m_render_camera->getCamera());

    // prepare pipeline's render passes data
    m_render_pipeline->preparePassData(m_render_resource);

    // debug-draw manager tick

    // submit render data in render one frame
    RenderCommand::Clear();
    RenderCommand::SetClearColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

    Renderer2D::beginScene(m_render_camera->getCamera());
    m_render_pipeline->forwardRender(m_render_resource);

//    Renderer2D::drawQuad(glm::vec3(0.f), 0.f, glm::vec2(1.f), glm::vec4(1.f, 1.f, 0.f, 1.f));
    auto texture = Texture2D::Create("Resources/planet.png");
    Renderer2D::drawCircle(glm::vec3(0.f), 1.f, texture);
    Renderer2D::endScene();

    // batch rendering
    Renderer2DBatch::beginScene(m_render_camera->getCamera());
    Renderer2DBatch::drawQuad(
        glm::vec3(0.f), 0.f, glm::vec2(1.f), glm::vec4(1.f, 1.f, 0.f, 1.f), 4);
    Renderer2DBatch::endScene();



    // RenderPictureLayer
//    for (auto &layer: m_layer_stack) {
//      layer->OnUpdate(delta_time);
//    }
//    for (auto &layer: m_layer_stack) {
//      layer->OnImGuiRender();
//    }
    m_imgui_layer->Begin();
    m_imgui_layer->OnImGuiRender();
    m_imgui_layer->End();
  }

  RenderSystem::~RenderSystem() {
    Renderer2D::shutdown();
    m_imgui_layer->OnDetach();
  }

  void RenderSystem::clear() {}

  void RenderSystem::processSwapData() {
    RenderSwapData &swap_data = m_swap_context.getRenderSwapData();

    // update global resource if needed

    // update game object if needed(from mesh component now)
    if (swap_data.m_game_object_resource_desc.has_value()) {
      cout("game object resource desc has value");
      while (!swap_data.m_game_object_resource_desc->isEmpty()) {
        /*
         * GameObjectDesc
         *  vec<GameObjectPartDesc> {
         *      GameObjectMeshDesc m_mesh_desc;
         *      GameObjectTextureDesc m_texture_desc;
         *      GameObjectTransformDesc m_transform_desc;
         *  }
         */
        GameObjectDesc gobject =
            swap_data.m_game_object_resource_desc->getNextProcessObject();

        for (size_t part_index = 0; part_index < gobject.getObjectParts().size(); ++part_index) {
          // GameObjectPartDesc
          const auto &game_object_part = gobject.getObjectParts()[part_index];

          GameObjectPartId part_id = {gobject.getID(), part_index};

          bool is_entity_in_scene =
              m_render_scene->getInstanceIdAllocator().hasElement(part_id);

          // RenderEntity -> render scene
          RenderEntity render_entity;

          // instance id
          render_entity.m_instance_id =
              static_cast<uint32_t>(m_render_scene->getInstanceIdAllocator().allocGuid(part_id));
          // model matrix
          render_entity.m_model_matrix =
              game_object_part.m_transform_desc.m_transform_matrix;

          m_render_scene->addInstanceIdToMap(render_entity.m_instance_id, gobject.getID());

          // mesh properties
          MeshSourceDesc mesh_source = {game_object_part.m_mesh_desc.m_mesh_file};
          bool is_mesh_loaded = m_render_scene->getMeshAssetIdAllocator().hasElement(mesh_source);

          RenderMeshData mesh_data;
          if (!is_mesh_loaded) {
            mesh_data =
                m_render_resource->loadMeshData(mesh_source, render_entity.m_bounding_box);
          } else {
            render_entity.m_bounding_box =
                m_render_resource->getCachedBoundingBox(mesh_source);
          }

          render_entity.mesh_asset_id =
              m_render_scene->getMeshAssetIdAllocator().allocGuid(mesh_source);

          TextureSourceDesc texture_source = {game_object_part.m_texture_desc.m_texture_file};
          bool is_texture_loaded =
              m_render_scene->getTextureAssetIdAllocator().hasElement(texture_source);

          RenderTextureData texture_data;
          if (!is_texture_loaded) {
            texture_data = m_render_resource->loadTextureData(texture_source);
          }
          render_entity.texture_asset_id =
              m_render_scene->getTextureAssetIdAllocator().allocGuid(texture_source);

          // upload render resource
          if (!is_mesh_loaded) {
            m_render_resource->uploadGameObjectRenderResource(render_entity, mesh_data);
          }

          if (!is_texture_loaded) {
            m_render_resource->uploadGameObjectRenderResource(render_entity, texture_data);
          }

          // render scene marked or refresh the render entity record
          if (!is_entity_in_scene) {
            m_render_scene->m_render_entities.push_back(render_entity);
          } else {
            for (auto &entity: m_render_scene->m_render_entities) {
              if (entity.m_instance_id == render_entity.m_instance_id) {
                entity = render_entity;
                break;
              }
            }
          }
        }
        // after finished processing, pop this game object
        swap_data.m_game_object_resource_desc->pop();
      }
      // reset game object swap data to a clean state.
      m_swap_context.resetGameObjectResourceSwapData();
    }

    // remove deleted objects

    // process camera swap data
  }

}