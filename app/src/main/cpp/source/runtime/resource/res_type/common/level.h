#pragma once

#include <string>
#include <vector>

#include "runtime/core/math/math_header.h"
#include "runtime/resource/res_type/common/object.h"

namespace Gp {

  class ObjectInstanceRes;

  class LevelRes {
  public:
    std::string m_character_name;

    std::vector<ObjectInstanceRes> m_objects;
  };

}