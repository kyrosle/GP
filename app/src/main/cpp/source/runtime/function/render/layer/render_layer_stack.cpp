#include "render_layer_stack.h"

namespace Gp {
  RenderLayerStack::RenderLayerStack() {
    m_cur_stack = m_stack.begin();
  }

  RenderLayerStack::~RenderLayerStack() {
    for (auto &layer: m_stack) {
      layer->OnDetach();
      layer.reset();
    }
  }

  void RenderLayerStack::pushLayer(const RenderLayer::ptr &layer) {
    m_stack.emplace(m_stack.begin(), layer);
    layer->OnAttach();
  }

  void RenderLayerStack::pushOverlay(const RenderLayer::ptr &overlay) {
    m_stack.emplace_back(overlay);
    overlay->OnAttach();
  }

  RenderLayer::ptr RenderLayerStack::popLayer() {
    if (!m_stack.empty()) {
      auto top = m_stack[0];
      m_stack.erase(m_stack.begin(), m_stack.begin() + 1);
      return top;
    } else {
      return nullptr;
    }
  }

  void RenderLayerStack::popOverlay(const RenderLayer::ptr &overlay) {
    auto it = std::find(m_stack.begin(), m_stack.end(), overlay);
    if (it != m_stack.end()) {
      m_stack.erase(it);
    }
  }
}