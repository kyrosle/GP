#include "render_resource.h"

#include <optional>

#include "runtime/function/global/global_context.h"
#include "runtime/function/render/render_scene.h"

namespace Gp {
  RenderTextureData RenderResourceBase::loadTextureData(const TextureSourceDesc &textureData) {
    RenderTextureData ret;
    ret.m_static_texture_data.m_texture = TextureData(textureData.m_texture_file);
    return ret;
  }

  RenderMeshData
  RenderResourceBase::loadMeshData(const MeshSourceDesc &source /* mesh source file */,
                                   AxisAlignedBox2D &bounding_box) {
    const float quadVertices[] =
        {
            -0.5f, -0.5f, 0, 0.0f, 0.0f,
            0.5f, -0.5f, 0, 1.0f, 0.0f,
            -0.5f, 0.5f, 0, 0.0f, 1.0f,
            0.5f, 0.5f, 0, 1.0f, 1.0f
        };
    const uint32_t quadIndices[] =
        {0, 1, 2, 2, 1, 3};

    RenderMeshData ret;
    // vertex buffer
    // default 2d
    ret.m_static_mesh_data.m_vertex_buffer = std::make_shared<BufferData>(sizeof(quadVertices));
    memcpy(ret.m_static_mesh_data.m_vertex_buffer->m_data, quadVertices, sizeof(quadVertices));
    ret.m_static_mesh_data.m_buffer_layout = {
        {ShaderDataType::Float3, "a_Pos"},
        {ShaderDataType::Float2, "a_Tex"}
    };
    // index buffer
    // default 2d
    ret.m_static_mesh_data.m_index_buffer = std::make_shared<BufferData>(sizeof(quadIndices));
    memcpy(ret.m_static_mesh_data.m_index_buffer->m_data, quadIndices, sizeof(quadIndices));

    return ret;
  }

  AxisAlignedBox2D RenderResourceBase::getCachedBoundingBox(const MeshSourceDesc &source) const {
    auto find_it = m_bounding_box_cache_map.find(source);
    if (find_it != m_bounding_box_cache_map.end()) {
      return find_it->second;
    }
    return {};
  }

  void RenderResource::clear() {}

  MeshNodeData &RenderResource::getEntityMesh(RenderEntity entity) {
    size_t asset_id = entity.mesh_asset_id;

    auto it = m_meshes.find(asset_id);
    if (it != m_meshes.end()) {
      return it->second;
    } else {
      throw std::runtime_error("failed to get entity mesh");
    }
  }

  TextureNodeData &RenderResource::getEntityTexture(RenderEntity entity) {
    size_t asset_id = entity.texture_asset_id;

    auto it = m_textures.find(asset_id);
    if (it != m_textures.end()) {
      return it->second;
    } else {
      throw std::runtime_error("failed to get entity texture");
    }
  }

  void RenderResource::createTextures(
      std::shared_ptr<TextureData> color_texture,
      std::shared_ptr<TextureData> ui_texture) {}

  MeshNodeData &RenderResource::getOrCreateMesh(
      RenderEntity entity, const RenderMeshData &mesh_data) {
    size_t asset_id = entity.mesh_asset_id;

    auto it = m_meshes.find(asset_id);
    if (it != m_meshes.end()) {
      return it->second;
    } else {
      MeshNodeData temp;
      // res type:
      // std::pair<std::map<size_t, Mesh>::iterator, bool>
      auto res =
          m_meshes.insert(std::make_pair(asset_id, std::move(temp)));
      // insert successfully
      assert(res.second);

      auto index_buffer_size =
          static_cast<uint32_t>(mesh_data.m_static_mesh_data.m_index_buffer->m_size);
      void *index_buffer_data = mesh_data.m_static_mesh_data.m_index_buffer->m_data;

      auto vertex_buffer_size =
          static_cast<uint32_t>(mesh_data.m_static_mesh_data.m_vertex_buffer->m_size);
      assert(vertex_buffer_size % 5 == 0);
      auto vertex_buffer_data =
          reinterpret_cast<MeshVertexDataDefinition *>(
              mesh_data.m_static_mesh_data.m_vertex_buffer->m_data);

      MeshNodeData &now_mesh = res.first->second;
      // update mesh data
      updateMeshData(
          index_buffer_size,
          index_buffer_data,
          vertex_buffer_size,
          vertex_buffer_data,
          mesh_data.m_static_mesh_data.m_buffer_layout,
          now_mesh);
      return now_mesh;
    }
  }

  TextureNodeData &
  RenderResource::getOrCreateTexture(RenderEntity entity, const RenderTextureData &texture_data) {
    size_t asset_id = entity.texture_asset_id;
    auto it = m_textures.find(asset_id);
    if (it != m_textures.end()) {
      return it->second;
    } else {
      TextureNodeData temp{
          std::make_shared<TextureData>(texture_data.m_static_texture_data.m_texture)};
      m_textures.insert(std::make_pair(asset_id, std::move(temp)));
      return temp;
    }
  }

  void RenderResource::updateMeshData(
      uint32_t index_buffer_size,
      void *index_buffer_data,
      uint32_t vertex_buffer_size,
      const struct MeshVertexDataDefinition *vertex_buffer_data,
      std::optional<BufferLayout> buffer_layout,
      MeshNodeData &now_mesh) {
    assert(0 == (vertex_buffer_size % sizeof(MeshVertexDataDefinition)));
    updateVertexBuffer(
        vertex_buffer_size,
        vertex_buffer_data,
        std::move(buffer_layout),
        now_mesh
    );
    assert(0 == (index_buffer_size % sizeof(uint32_t)));
    updateIndexBuffer(index_buffer_size, index_buffer_data, now_mesh);


    now_mesh.m_vertex_array.reset(VertexArray::Create());
    now_mesh.m_vertex_array->Bind();

    now_mesh.m_vertex_buffer->Bind();
    now_mesh.m_index_buffer->Bind();

    now_mesh.m_vertex_array->AddVertexBuffer(now_mesh.m_vertex_buffer);
    now_mesh.m_vertex_array->SetIndexBuffer(now_mesh.m_index_buffer);

    now_mesh.m_vertex_array->UnBind();
//    now_mesh.m_index_buffer->UnBind();
//    now_mesh.m_vertex_buffer->UnBind();
  }

  void RenderResource::updateVertexBuffer(
      uint32_t vertex_buffer_size,
      struct MeshVertexDataDefinition const *vertex_buffer_data,
      std::optional<BufferLayout> buffer_layout,
      MeshNodeData &now_mesh) {
    auto vertex_buffer = VertexBuffer::ptr(
        VertexBuffer::Create(
            reinterpret_cast<const float *>(vertex_buffer_data),
            vertex_buffer_size
        )
    );
    if (buffer_layout.has_value()) {
      vertex_buffer->SetBufferLayout(buffer_layout.value());
    }
    now_mesh.m_vertex_buffer = vertex_buffer;
  }

  void RenderResource::updateIndexBuffer(
      uint32_t index_buffer_size,
      void *index_buffer_data,
      MeshNodeData &now_mesh) {
    auto index_buffer = IndexBuffer::ptr(
        IndexBuffer::Create(
            reinterpret_cast<uint32_t *>(index_buffer_data),
            index_buffer_size
        )
    );
    now_mesh.m_index_buffer = index_buffer;
  }

  void RenderResource::uploadGameObjectRenderResource(
      RenderEntity renderEntity,
      RenderMeshData meshData) {
    getOrCreateMesh(renderEntity, meshData);
  }

  void RenderResource::uploadGameObjectRenderResource(RenderEntity renderEntity,
                                                      RenderTextureData textureData) {
    getOrCreateTexture(renderEntity, textureData);
  }

  void RenderResource::updatePerFrameBuffer(
      RenderScene::ptr render_scene,
      RenderCamera render_camera) {}


}