#include "axis_aligned2D.h"

#include <glm/common.hpp>

namespace Gp {
  AxisAlignedBox2D::AxisAlignedBox2D(const glm::vec3 &center,
                                     const glm::vec3 &half_extent) {
    update(center, half_extent);
  }

  void AxisAlignedBox2D::merge(const glm::vec3 &new_point) {
    m_min_corner = glm::floor(new_point);
    m_max_corner = glm::ceil(new_point);

    m_center = 0.5f * (m_min_corner + m_max_corner);
    m_half_extent = m_center - m_min_corner;
  }

  void
  AxisAlignedBox2D::update(const glm::vec3 &center, const glm::vec3 &half_extent) {
    m_center = center;
    m_half_extent = half_extent;
    m_min_corner = center - half_extent;
    m_max_corner = center + half_extent;
  }
}