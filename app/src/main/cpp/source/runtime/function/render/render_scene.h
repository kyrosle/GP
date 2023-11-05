#pragma once

#include <memory>

#include "runtime/function/render/render_entity.h"
#include "runtime/function/render/render_guid_allocator.h"
#include "runtime/function/render/render_object.h"
#include "runtime/function/render/render_type.h"
#include "runtime/function/render/render_resource.h"

namespace Gp {
  class RenderScene {
  public:
    typedef std::shared_ptr<RenderScene> ptr;

    // render entities
    std::vector<RenderEntity> m_render_entities;

    // visible objects (update per frame)
    std::vector<RenderMeshNode> m_main_camera_visible_mesh_nodes;

    // clear
    void clear();

    // update visible objects in each frame
    void updateVisibleObjects(
        RenderResource::ptr render_resource,
        RenderCamera &camera
    );

    // set visible nodes ptr in render pass
    void setVisibleNodesReference();

    GuidAllocator<GameObjectPartId> &getInstanceIdAllocator();

    GuidAllocator<MeshSourceDesc> &getMeshAssetIdAllocator();

    GuidAllocator<TextureSourceDesc> &getTextureAssetIdAllocator();

    void addInstanceIdToMap(uint32_t instance_id, GObjectID go_id);

    GObjectID getGObjectIDByMeshID(uint32_t mesh_id) const;

    void deleteEntityByGObjectID(GObjectID go_id);


  private:
    void updateVisibleObjectMainCamera(
        RenderResource::ptr render_resource,
        RenderCamera &camera);

  private:
    GuidAllocator<GameObjectPartId> m_instance_id_allocator;
    GuidAllocator<MeshSourceDesc> m_mesh_asset_id_allocator;
    GuidAllocator<TextureSourceDesc> m_texture_asset_id_allocator;

    std::unordered_map<uint32_t, GObjectID> m_mesh_object_id_map;
  };
}