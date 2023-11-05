#include "main_camera_pass.h"

#include <glm/gtc/matrix_transform.hpp>

#include "runtime/core/log/android_out.h"
#include "runtime/function/render/render_render2D.h"
#include "runtime/function/render/render_shader_library.h"
#include "runtime/function/render/render_command.h"
#include "runtime/function/render/render_type.h"

#include "runtime/function/global/global_context.h"
#include "runtime/function/render/render_system.h"

namespace Gp {
  void MainCameraPass::initialize(const RenderPassInitInfo *init_info) {
    m_shader.insert(std::make_pair("FlatColorShader", RenderShaderLibrary::Get("FlatColorShader")));
    m_shader.insert(std::make_pair("TextureShader", RenderShaderLibrary::Get("TextureShader")));
//    auto _init_info = static_cast<const MainCameraPassInitInfo *> (init_info);
  }

  void MainCameraPass::preparePassData(
      std::shared_ptr<RenderResourceBase> render_resource) {
  }

  void MainCameraPass::draw() {
//    m_shader["TextureShader"]->Bind();
    acout << "-main camera draw mesh-" << std::endl;
//    auto shader = m_shader["FlatColorShader"];
//    // reorganize mesh
//    for (RenderMeshNode &node: *(m_visible_nodes.p_main_camera_visible_mesh_nodes)) {
//      shader->Bind();
//      shader->UploadUniformMat4("u_ViewProjection",
//                                g_runtime_global_context.m_render_system->getViewProjectionMatrix());
//      shader->UploadUniformVec4("u_Color", glm::vec4(1.0f, 0.f, 0.f, 1.f));
////      glm::mat4 transform =
////          glm::scale(glm::mat4(1.0f), glm::vec3(1.0, 1.0, 1.0f));
////      transform = glm::translate(transform, glm::vec3(0.f, 0.f, 0.f));
////      transform = glm::rotate(transform, glm::radians(0.f), {0, 0, 1});
//      shader->UploadUniformMat4("u_Transform", *node.model_matrix);
//      RenderCommand::DrawIndexed(node.ref_mesh->m_vertex_array);
//      shader->UnBind();
//    }

    auto texture_shader = m_shader["TextureShader"];
    auto flat_color_shader = m_shader["FlatColorShader"];
    for (RenderMeshNode &node: *(m_visible_nodes.p_main_camera_visible_mesh_nodes)) {
      // RenderMeshNode:
      //  const glm::mat4 *model_matrix{nullptr};
      //  MeshNodeData *ref_mesh{nullptr};
      //  TextureNodeData *ref_texture{nullptr};
      //  uint32_t node_id;

      // if the texture is existed, use texture shader, otherwise use the flat color shader and show red color:
      // (self defined mesh and texture)
      if (node.ref_texture != nullptr && node.ref_texture->m_texture->isValid()) {
        texture_shader->Bind();
        texture_shader->UploadUniformMat4("u_ViewProjection",
                                          g_runtime_global_context.m_render_system->getViewProjectionMatrix());
        texture_shader->UploadUniformMat4("u_Transform", *node.model_matrix);
        auto texture = node.ref_texture->m_texture->texture;
        texture->Bind();
        RenderCommand::DrawIndexed(node.ref_mesh->m_vertex_array);
        texture_shader->UnBind();
      } else {
        flat_color_shader->Bind();
        flat_color_shader->UploadUniformMat4("u_ViewProjection",
                                             g_runtime_global_context.m_render_system->getViewProjectionMatrix());
        flat_color_shader->UploadUniformVec4("u_Color", glm::vec4(1.0f, 0.f, 0.f, 1.f));
        flat_color_shader->UploadUniformMat4("u_Transform", *node.model_matrix);
        RenderCommand::DrawIndexed(node.ref_mesh->m_vertex_array);
        flat_color_shader->UnBind();
      }
    }

//    Renderer2D::drawQuad(
//        {0, 0, 0},
//        0,
//        {0.5, 0.5},
//        {1.0f, 0.0f, 0.0f, 1.0f}
//    );
//    m_shader["TextureShader"]->UnBind();
  }
}