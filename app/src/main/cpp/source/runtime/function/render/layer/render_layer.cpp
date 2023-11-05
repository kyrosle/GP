#include "render_layer.h"

#include <utility>

namespace Gp {
  RenderLayer::RenderLayer(std::string name)
    : m_DebugName(std::move(name)), isEnabled(true) {}
}