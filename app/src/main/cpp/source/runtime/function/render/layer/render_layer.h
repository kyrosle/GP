#pragma once

#include <string>
#include <memory>

#include "runtime/function/event/event.h"

namespace Gp {

  class RenderLayer {
  public:
    typedef std::shared_ptr<RenderLayer> ptr;

    RenderLayer(std::string name = "Layer");

    virtual ~RenderLayer() = default;

    virtual void OnAttach() {};

    virtual void OnDetach() {};

    virtual void OnEvent(Event::ptr event) {};

    virtual void OnUpdate(const float deltaTime) {};

    virtual void OnImGuiRender() {};

  protected:
    bool isEnabled;
    std::string m_DebugName;
  };

}

