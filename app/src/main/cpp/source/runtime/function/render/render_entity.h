#pragma once

#include "runtime/core/math/math_header.h"

namespace Gp {
  class RenderEntity {
  public:
    uint32_t m_instance_id{0};
    glm::mat4 m_model_matrix{glm::mat4(1.f)};

    // mesh
    size_t mesh_asset_id{0};
    AxisAlignedBox2D m_bounding_box;

    // texture
    size_t texture_asset_id{0};
  };
}