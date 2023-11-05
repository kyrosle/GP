#include "render_scene.h"

#include <utility>

#include "runtime/function/render/render_pass.h"

namespace Gp {
  GuidAllocator<GameObjectPartId> &RenderScene::getInstanceIdAllocator() {
    return m_instance_id_allocator;
  }

  GuidAllocator<MeshSourceDesc> &RenderScene::getMeshAssetIdAllocator() {
    return m_mesh_asset_id_allocator;
  }

  GuidAllocator<TextureSourceDesc> &RenderScene::getTextureAssetIdAllocator() {
    return m_texture_asset_id_allocator;
  }

  void RenderScene::addInstanceIdToMap(uint32_t instance_id, GObjectID go_id) {
    m_mesh_object_id_map[instance_id] = go_id;
  }

  GObjectID RenderScene::getGObjectIDByMeshID(uint32_t mesh_id) const {
    auto find_it = m_mesh_object_id_map.find(mesh_id);
    if (find_it != m_mesh_object_id_map.end()) {
      return find_it->second;
    }
    return GObjectID();
  }

  void RenderScene::deleteEntityByGObjectID(GObjectID go_id) {
    for (auto it = m_mesh_object_id_map.begin(); it != m_mesh_object_id_map.end(); ++it) {
      if (it->second == go_id) {
        m_mesh_object_id_map.erase(it);
        break;
      }
    }

    GameObjectPartId part_id = {go_id, 0};
    size_t find_guid;
    if (m_instance_id_allocator.getElementGuid(part_id, find_guid)) {
      for (auto it = m_render_entities.begin(); it != m_render_entities.end(); ++it) {
        m_render_entities.erase(it);
        break;
      }
    }
  }

  void RenderScene::updateVisibleObjects(
      RenderResource::ptr render_resource,
      RenderCamera &camera) {
    updateVisibleObjectMainCamera(std::move(render_resource), camera);
  }

  void RenderScene::updateVisibleObjectMainCamera(
      RenderResource::ptr render_resource,
      RenderCamera &camera) {
    m_main_camera_visible_mesh_nodes.clear();

    // create cluster frustum from matrix

//    Matrix4x4 view_matrix = camera->getViewMatrix();

    for (const RenderEntity &entity: m_render_entities) {
      // if (tiled frustum intersect box) check with bounding box
      m_main_camera_visible_mesh_nodes.emplace_back();

      RenderMeshNode &temp_node = m_main_camera_visible_mesh_nodes.back();
      temp_node.model_matrix = &entity.m_model_matrix;

      temp_node.node_id = entity.m_instance_id;
      MeshNodeData &mesh_asset = render_resource->getEntityMesh(entity);
      TextureNodeData &texture_asset = render_resource->getEntityTexture(entity);
      temp_node.ref_mesh = &mesh_asset;
      temp_node.ref_texture = &texture_asset;
    }
  }

  void RenderScene::clear() {}

  void RenderScene::setVisibleNodesReference() {
    RenderPass::m_visible_nodes.p_main_camera_visible_mesh_nodes = &m_main_camera_visible_mesh_nodes;
  }

}