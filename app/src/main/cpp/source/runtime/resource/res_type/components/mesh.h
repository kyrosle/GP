#pragma once

#include <string>
#include <vector>

#include "runtime/core/math/math_header.h"

namespace Gp {
  class SubMeshRes {
  public:
    // the json description of mesh
    std::string m_obj_file_ref;
    // sub mesh transform
    Transform2D m_transform;
  };

  /*
   * collection of sub mesh pieces
   */
  class MeshComponentRes {
  public:
    std::vector<SubMeshRes> m_sub_mesh;
  };
}