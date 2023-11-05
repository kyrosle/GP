#pragma once

#include <imgui.h>
#include <memory>

#include "runtime/function/render/layer/render_layer.h"

namespace Gp {

  class ImguiLayer : public RenderLayer {
  public:
    typedef std::shared_ptr<ImguiLayer> ptr;

    ImguiLayer();

    ~ImguiLayer() = default;

    void OnAttach() override;

    void OnDetach() override;

    void OnEvent(Event::ptr) override;

    void OnImGuiRender() override;

    void Begin();

    void End();

    void SetDarkThemeColors();

    bool checkFocus() { return m_is_focus; }

    inline void hasFocus(bool state = false) {
      m_is_focus |= ImGui::IsWindowFocused() | state;
    }

    void clearFocus() { m_is_focus = false; }

  private:
    bool m_is_focus;

  };

}
