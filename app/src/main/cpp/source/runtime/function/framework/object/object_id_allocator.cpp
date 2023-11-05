#include "object_id_allocator.h"

#include "runtime/core/log/android_out.h"

namespace Gp {

  std::atomic<std::size_t> ObjectIDAllocator::m_next_id{0};

  GObjectID ObjectIDAllocator::alloc() {
    std::atomic<GObjectID> new_object_ret = m_next_id.load();
    m_next_id++;
    if (m_next_id >= k_invalid_gobject_id) {
      acout << "GObject id overflow" << std::endl;
    }
    return new_object_ret;
  }

}