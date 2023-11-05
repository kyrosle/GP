#pragma once

#include <string>
#include <glm/glm.hpp>

#include "runtime/function/framework/level/level.h"
#include "runtime/function/render/layer/render_layer.h"
#include "runtime/function/event/event.h"
#include "runtime/function/event/mouse_event.h"

namespace Gp {

  class GameLayer : public RenderLayer {
  public:
    GameLayer(const std::string &name = "Game Layer");

    ~GameLayer();

    void OnAttach() override;

    void OnDetach() override;

    void OnEvent(Event::ptr event) override;

    bool OnMouseButtonPressed(MouseButtonPressedEvent::ptr e);

    void OnUpdate(const float deltaTime) override;

    void OnImGuiRender() override;

  private:
    Level::ptr m_level;
  };

}
