#include "imgui_layer.h"

#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_android.h>

#include "runtime/function/global/global_context.h"

#include "runtime/function/event/mouse_event.h"

namespace Gp {
  ImguiLayer::ImguiLayer() : RenderLayer("Imgui Layer") {}

  void ImguiLayer::OnAttach() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
//    io.ConfigFlags |= ImGuiConfigFlags_IsTouchScreen;
//    io.ConfigFlags |= ImGuiConfigFlags_NavEnableSetMousePos;

//    auto width = window_size[0];
//    auto height = window_size[1];
//    io.DisplaySize = ImVec2(width, height);

//    acout << "imgui window size w:" << width << " h:" << height << std::endl;

    auto g_IniFilename = std::string(
      g_runtime_global_context.m_app->activity->internalDataPath) + "/imgui";
    io.IniFilename = g_IniFilename.c_str();;

    ImGui::StyleColorsDark();

    ImGui_ImplAndroid_Init(g_runtime_global_context.m_app->window);
    ImGui_ImplOpenGL3_Init("#version 300 es");


    ImFontConfig font_cfg;
    font_cfg.SizePixels = 22.0f;
    io.Fonts->AddFontDefault(&font_cfg);

    ImGuiStyle &style = ImGui::GetStyle();
    style.ScaleAllSizes(3.0f);
  }

  void ImguiLayer::OnDetach() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplAndroid_Shutdown();
    ImGui::DestroyContext();
  }

  void ImguiLayer::OnImGuiRender() {
    clearFocus();
    static bool show_demo_window = true;
    static bool show_another_window = false;
    static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    // 1. Show the big demo window (Most of the sample code is in
    // ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear
    // ImGui!).
    if (show_demo_window) {
      ImGui::ShowDemoWindow(&show_demo_window);
    }

    // 2. Show a simple window that we create ourselves. We use a Begin/End pair
    // to created a named window.
    {
      static auto f = 0.0f;
      static int counter = 0;

      // Create a window called "Hello, world!" and append into it.
      ImGui::Begin("Hello, world!");
      hasFocus();

//      ImGui::SetWindowSize(
//        ImVec2(s_window_size[0] * 0.6, s_window_size[1] * 0.8));
      // Display some text (you can use a format strings too
      ImGui::Text("This is some useful text.");
      // Edit bools storing our window open/close state
      ImGui::Checkbox("Demo Window", &show_demo_window);
      ImGui::Checkbox("Another Window", &show_another_window);

      // Edit 1 float using a slider from 0.0f to 1.0f
      ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
      // Edit 3 floats representing a color
      ImGui::ColorEdit3("clear color", (float *) &clear_color);

      // Buttons return true when clicked (most widgets return true when edited/activated)
      if (ImGui::Button("Button"))
        counter++;
      ImGui::SameLine();
      ImGui::Text("counter = %d", counter);

      ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                  1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
      ImGui::End();
    }

    // 3. Show another simple window.
    if (show_another_window) {
      ImGui::Begin(
        "Another Window",
        &show_another_window); // Pass a pointer to our bool variable (the
      hasFocus();
      // window will have a closing button that will
      // clear the bool when clicked)
      ImGui::Text("Hello from another window!");
      if (ImGui::Button("Close Me"))
        show_another_window = false;
      ImGui::End();
    }
  }

  void ImguiLayer::Begin() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplAndroid_NewFrame();
    ImGui::NewFrame();
  }

  void ImguiLayer::End() {
    // Rendering
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  }

  void ImguiLayer::OnEvent(Event::ptr event) {
    ImGuiIO &io = ImGui::GetIO();
//    acout << "Imgui Layer receive event: " << event->GetName() << std::endl;
    // MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    switch (event->GetEventType()) {
      case EventType::MouseButtonPressed: {
        auto mouse_button_press_event =
          std::dynamic_pointer_cast<MouseButtonPressedEvent>(event);
        io.AddMouseButtonEvent(0, true);
      }
        break;
      case EventType::MouseButtonReleased: {
        auto mouse_button_press_event =
          std::dynamic_pointer_cast<MouseButtonReleasedEvent>(event);
        io.AddMouseButtonEvent(0, false);
      }
        break;
      case EventType::MouseMoved: {
        auto mouse_moved_event =
          std::dynamic_pointer_cast<MouseMovedEvent>(event);
        io.AddMousePosEvent(
          mouse_moved_event->GetXPos(),
          mouse_moved_event->GetYPos()
        );
      }
        break;
      default:
        break;
    }
    if (checkFocus()) {
      event->MarkHandled();
      acout << "Imgui Layer focus" << std::endl;
    } else {
      acout << "Imgui Layer has not focus" << std::endl;
    }
  }

  void ImguiLayer::SetDarkThemeColors() {
    auto &colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_WindowBg] = ImVec4{0.1f, 0.105f, 0.11f, 1.0f};

    // Headers
    colors[ImGuiCol_Header] = ImVec4{0.2f, 0.205f, 0.21f, 1.0f};
    colors[ImGuiCol_HeaderHovered] = ImVec4{0.3f, 0.305f, 0.31f, 1.0f};
    colors[ImGuiCol_HeaderActive] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};

    // Buttons
    colors[ImGuiCol_Button] = ImVec4{0.2f, 0.205f, 0.21f, 1.0f};
    colors[ImGuiCol_ButtonHovered] = ImVec4{0.3f, 0.305f, 0.31f, 1.0f};
    colors[ImGuiCol_ButtonActive] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};

    // Frame BG
    colors[ImGuiCol_FrameBg] = ImVec4{0.2f, 0.205f, 0.21f, 1.0f};
    colors[ImGuiCol_FrameBgHovered] = ImVec4{0.3f, 0.305f, 0.31f, 1.0f};
    colors[ImGuiCol_FrameBgActive] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};

    // Tabs
    colors[ImGuiCol_Tab] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};
    colors[ImGuiCol_TabHovered] = ImVec4{0.38f, 0.3805f, 0.381f, 1.0f};
    colors[ImGuiCol_TabActive] = ImVec4{0.28f, 0.2805f, 0.281f, 1.0f};
    colors[ImGuiCol_TabUnfocused] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4{0.2f, 0.205f, 0.21f, 1.0f};

    // Title
    colors[ImGuiCol_TitleBg] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};
    colors[ImGuiCol_TitleBgActive] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};
  }
}