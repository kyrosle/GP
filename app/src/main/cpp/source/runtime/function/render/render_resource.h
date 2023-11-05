#pragma once

#include <memory>
#include <unordered_map>
#include <map>

#include "runtime/core/math/math_header.h"
#include "runtime/function/render/render_type.h"
#include "runtime/function/render/render_entity.h"
#include "runtime/function/render/render_camera_controller.h"
#include "runtime/function/render/render_common.h"

namespace Gp {
  class RenderScene;

  class RenderResourceBase {
  public:
    typedef std::shared_ptr<RenderResourceBase> ptr;

    virtual ~RenderResourceBase() {};

    virtual void clear() = 0;

    virtual void uploadGameObjectRenderResource(
        RenderEntity renderEntity, RenderMeshData meshData) = 0;

    virtual void uploadGameObjectRenderResource(
        RenderEntity renderEntity, RenderTextureData textureData) = 0;

    virtual void updatePerFrameBuffer(
        std::shared_ptr<RenderScene> render_scene, RenderCamera render_camera) = 0;

    // TODO: data catching

    RenderTextureData loadTextureData(const TextureSourceDesc &textureData);

    RenderMeshData loadMeshData(const MeshSourceDesc &source, AxisAlignedBox2D &bounding_box);

    AxisAlignedBox2D getCachedBoundingBox(const MeshSourceDesc &source) const;

  private:
    std::unordered_map<MeshSourceDesc, AxisAlignedBox2D> m_bounding_box_cache_map;
  };

  class RenderResource : public RenderResourceBase {
  public:
    typedef std::shared_ptr<RenderResource> ptr;

    void clear() override final;

    virtual void uploadGameObjectRenderResource(
        RenderEntity renderEntity,
        RenderMeshData meshData) override final;

    virtual void uploadGameObjectRenderResource(
        RenderEntity renderEntity, RenderTextureData textureData) override final;

    virtual void updatePerFrameBuffer(
        std::shared_ptr<RenderScene> render_scene,
        RenderCamera render_camera) override final;

    MeshNodeData &getEntityMesh(RenderEntity entity);

    TextureNodeData &getEntityTexture(RenderEntity entity);

    // cached mesh
    std::map<size_t, MeshNodeData> m_meshes;
    std::map<size_t, TextureNodeData> m_textures;
  private:
//    void createSamplers();

    /*!
     * @param color_texture Represents a color map for 2D rendering.
     * This texture can be used for backgrounds, character maps, or other 2D rendering effects.
     * @param ui_texture Represents a texture for 2D interface (UI) rendering.
     * This texture can be used to render user interface elements such as buttons, text, icons, etc.
     */
    void createTextures(
        std::shared_ptr<TextureData> color_texture,
        std::shared_ptr<TextureData> ui_texture);

    MeshNodeData &getOrCreateMesh(
        RenderEntity entity,
        const RenderMeshData &mesh_data
    );

    TextureNodeData &getOrCreateTexture(
        RenderEntity entity,
        const RenderTextureData &texture_data
    );

    void updateMeshData(
        uint32_t index_buffer_size,
        void *index_buffer_data,
        uint32_t vertex_buffer_size,
        struct MeshVertexDataDefinition const *vertex_buffer_data,
        std::optional<BufferLayout> buffer_layout,
        MeshNodeData &now_mesh);

    void updateVertexBuffer(
        uint32_t vertex_buffer_size,
        struct MeshVertexDataDefinition const *vertex_buffer_data,
        std::optional<BufferLayout> buffer_layout,
        MeshNodeData &now_mesh);

    void updateIndexBuffer(
        uint32_t index_buffer_size,
        void *index_buffer_data,
        MeshNodeData &now_mesh);
  };

}