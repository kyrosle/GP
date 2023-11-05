#pragma once

#include <string>

#include "runtime/function/render/render_buffer.h"
#include "runtime/function/render/render_texture.h"

namespace Gp {
  class BufferData {
  public:
    size_t m_size{0};
    void *m_data{nullptr};

    BufferData() = delete;

    BufferData(size_t size) {
      m_size = size;
      m_data = malloc(size);
    }

    ~BufferData() {
      if (m_data) {
        free(m_data);
      }
    }

    bool isValid() const { return m_data != nullptr; }
  };

  class TextureData {
  public:
    typedef std::shared_ptr<TextureData> ptr;
//    uint32_t m_width{0};
//    uint32_t m_height{0};
//    void *m_pixels{nullptr};
    Texture2D::ptr texture{nullptr};

    // texture format for now: jpg or png
    TextureData() = default;

    TextureData(const std::string &asset_path) {
      texture = Texture2D::Create(asset_path);
    }

    ~TextureData() {
      texture.reset();
//      if (m_pixels) {
//        free(m_pixels);
//      }
    }

//    bool isValid() const { return m_pixels != nullptr; }
    bool isValid() const { return texture != nullptr; }
  };

  struct MeshVertexDataDefinition {
    float x, y, z; // position
    float u, v;    // uv coordinates
  };

  struct MeshSourceDesc {
    // mesh json file
    std::string m_mesh_file;

    bool operator==(const MeshSourceDesc &rhs) const {
      return m_mesh_file == rhs.m_mesh_file;
    }

    size_t getHashValue() const {
      return std::hash<std::string>{}(m_mesh_file);
    }
  };

  struct TextureSourceDesc {
    std::string m_texture_file;

    bool operator==(const TextureSourceDesc &rhs) const {
      return m_texture_file == rhs.m_texture_file;
    }

    size_t getHashValue() const {
      return std::hash<std::string>{}(m_texture_file);
    }
  };

  struct StaticMeshData {
    std::shared_ptr<BufferData> m_vertex_buffer;
    std::shared_ptr<BufferData> m_index_buffer;
    std::optional<BufferLayout> m_buffer_layout;
  };

  struct RenderMeshData {
    StaticMeshData m_static_mesh_data;
  };

  struct StaticTextureData {
    TextureData m_texture;
  };

  struct RenderTextureData {
    StaticTextureData m_static_texture_data;
  };
}

template<>
struct std::hash<Gp::MeshSourceDesc> {
  size_t operator()(const Gp::MeshSourceDesc &rhs) const noexcept {
    return rhs.getHashValue();
  }
};

template<>
struct std::hash<Gp::TextureSourceDesc> {
  size_t operator()(const Gp::TextureSourceDesc &rhs) const noexcept {
    return rhs.getHashValue();
  }
};