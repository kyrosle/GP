/* ----------------------------------
 * | -- form piccolo game engine -- |
 * ----------------------------------
 */
#pragma once

/*
 * not enable self defined math library,
 * for now stage, 2d game engine use glm library instead
 */

#include <glm/glm.hpp>
#include "runtime/core/math/transform2D.h"
#include "runtime/core/math/axis_aligned2D.h"

//#define ENABLE_SELF_MATRH
#ifdef ENABLE_SELF_MATRH

#include "runtime/core/math/axis_aligned.h"
#include "runtime/core/math/math.h"
#include "runtime/core/math/math_marcos.h"
#include "runtime/core/math/matrix3.h"
#include "runtime/core/math/matrix4.h"
#include "runtime/core/math/quaternion.h" /* 2d game engine not used */
#include "runtime/core/math/random.h"
#include "runtime/core/math/transform.h"
#include "runtime/core/math/vector2.h"
#include "runtime/core/math/vector3.h"
#include "runtime/core/math/vector4.h"

namespace Gp {
  glm::vec3 toGLM(const Vector3 &vec3) {
    return glm::vec3(vec3.x, vec3.y, vec3.z);
  }

  Vector3 fromGLM(const glm::vec3 &vec3) {
    return Vector3(vec3.x, vec3.y, vec3.z);
  }
}

#endif
