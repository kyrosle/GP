#include "mesh_component.h"

#include "runtime/function/global/global_context.h"
#include "runtime/function/render/render_swap_context.h"
#include "runtime/core/math/math_header.h"

namespace Gp {

  void MeshComponent::postLoadResource(std::weak_ptr<GObject> parent_object) {
    m_parent_object = parent_object;

    // call asset manager

    m_raw_meshes.resize(m_mesh_res.m_sub_mesh.size());

    size_t raw_mesh_count = 0;

    for (const SubMeshRes &sub_mesh: m_mesh_res.m_sub_mesh) {
      GameObjectPartDesc &meshComponent = m_raw_meshes[raw_mesh_count];

      // open after implemented serialized and deserialized.
//      meshComponent.m_mesh_desc.m_mesh_file = sub_mesh.m_obj_file_ref;
//      meshComponent.m_texture_desc.m_texture_file = sub_mesh.m_obj_file_ref;

      meshComponent.m_transform_desc.m_transform_matrix = sub_mesh.m_transform.getMatrix();

      ++raw_mesh_count;
    }
  }

  /*
   * Should i put the upload modified render part in a render component?
   */
  void MeshComponent::tick(float deltaTime) {
    if (!m_parent_object.lock()) {
      return;
    }

    TransformComponent::ptr transform_component =
        m_parent_object.lock()->tryGetComponent(TransformComponent);

    TextureComponent::ptr texture_component =
        m_parent_object.lock()->tryGetComponent(TextureComponent);

    if (transform_component->isDirty()) {
      // collect game object part which transform has changed(dirtied)
      std::vector<GameObjectPartDesc> dirty_mesh_parts;

      for (GameObjectPartDesc &mesh_part: m_raw_meshes) {
        glm::mat4 object_transform_matrix = mesh_part.m_transform_desc.m_transform_matrix;

        // update mesh part transform matrix
        mesh_part.m_transform_desc.m_transform_matrix =
            transform_component->getMatrix() * object_transform_matrix;

        mesh_part.m_texture_desc = texture_component->getRawTextureRes();

        dirty_mesh_parts.push_back(mesh_part);

        mesh_part.m_transform_desc.m_transform_matrix = object_transform_matrix;
      }

      // add game object dirtied part into logical swap data
      RenderSwapContext &render_swap_context =
          g_runtime_global_context.m_render_system->getSwapContext();
      RenderSwapData &logic_swap_data = render_swap_context.getLogicSwapData();

      logic_swap_data.addDirtyGameObject(
          GameObjectDesc{
              m_parent_object.lock()->getID(),
              dirty_mesh_parts
          }
      );

      transform_component->setDirtyFlag(false);
    }
  }

}