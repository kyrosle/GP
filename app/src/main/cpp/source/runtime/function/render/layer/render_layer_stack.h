#pragma once

#include <memory>
#include <vector>

#include "runtime/function/render/layer/render_layer.h"

namespace Gp {

  class RenderLayerStack {
  public:
    typedef std::shared_ptr<RenderLayerStack> ptr;

    RenderLayerStack();

    ~RenderLayerStack();

    void pushLayer(const RenderLayer::ptr &layer);

    void pushOverlay(const RenderLayer::ptr &overlay);

    RenderLayer::ptr popLayer();

    void popOverlay(const RenderLayer::ptr &overlay);

    std::vector<RenderLayer::ptr>::iterator
    begin() { return m_stack.begin(); }

    std::vector<RenderLayer::ptr>::iterator end() { return m_stack.end(); }

  private:
    std::vector<RenderLayer::ptr> m_stack;
    std::vector<RenderLayer::ptr>::iterator m_cur_stack;
  };

}
