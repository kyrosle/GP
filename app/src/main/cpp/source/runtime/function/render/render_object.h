#pragma once

#include <string>
#include <limits>
#include <vector>

#include "runtime/core/math/math_header.h"
#include "runtime/function/framework/object/object_id_allocator.h"

namespace Gp {
  struct GameObjectMeshDesc {
    std::string m_mesh_file;
  };

//  struct GameObjectMaterialDesc {
//    std::string m_base_color_texture_file;
//    std::string m_metallic_roughness_texture_file;
//    std::string m_normal_texture_file;
//    std::string m_occlusion_texture_file;
//    std::string m_emission_texture_file;
//    bool m_with_texture{false};
//  };

  struct GameObjectTextureDesc {
    std::string m_texture_file;
  };

  struct GameObjectTransformDesc {
    glm::mat4 m_transform_matrix{glm::mat4(1.f)};
  };

  struct GameObjectPartDesc {
    GameObjectMeshDesc m_mesh_desc;
    GameObjectTextureDesc m_texture_desc;
//    GameObjectMaterialDesc m_material_desc;
    GameObjectTransformDesc m_transform_desc;
  };

  constexpr size_t k_invalid_part_id = std::numeric_limits<size_t>::max();

  struct GameObjectPartId {
    GObjectID m_go_id{k_invalid_part_id};
    size_t m_part_id{k_invalid_part_id};

    bool operator==(const GameObjectPartId &rhs) const {
      return m_go_id == rhs.m_go_id && m_part_id == rhs.m_part_id;
    }

    size_t getHashValue() const { return m_go_id ^ (m_part_id << 1); }

    bool isValid() const { return m_go_id != k_invalid_part_id && m_part_id != k_invalid_part_id; }
  };

  class GameObjectDesc {
  public:
    GameObjectDesc() : m_go_id(0) {}

    GameObjectDesc(size_t go_id, const std::vector<GameObjectPartDesc> &parts)
        : m_go_id(go_id), m_object_parts(parts) {}

    GObjectID getID() const { return m_go_id; }

    const std::vector<GameObjectPartDesc> &getObjectParts() const { return m_object_parts; }

  private:
    GObjectID m_go_id{k_invalid_gobject_id};
    std::vector<GameObjectPartDesc> m_object_parts;
  };

}

template<>
struct std::hash<Gp::GameObjectPartId> {
  size_t operator()(const Gp::GameObjectPartId &rhs) const noexcept {
    return rhs.getHashValue();
  }
};