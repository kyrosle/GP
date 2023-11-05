#pragma once

#include <optional>
#include <deque>

#include "runtime/core/math/math_header.h"
#include "runtime/function/render/render_object.h"

namespace Gp {

  struct CameraSwapData {
    std::optional<float> m_fov_x;
    std::optional<glm::mat4> m_view_matrix;
  };

  struct GameObjectResourceDesc {
    std::deque<GameObjectDesc> m_game_object_descs;

    void add(GameObjectDesc &desc);

    void pop();

    bool isEmpty() const;

    GameObjectDesc &getNextProcessObject();
  };

  struct RenderSwapData {
    std::optional<GameObjectResourceDesc> m_game_object_resource_desc;
    std::optional<GameObjectResourceDesc> m_game_object_to_delete;
    std::optional<CameraSwapData> m_camera_swap_data;

    void addDirtyGameObject(GameObjectDesc &&desc);

    void addDeleteGameObject(GameObjectDesc &&desc);
  };

  enum class SwapDataType : uint8_t {
    LogicSwapDataType = 0,
    RenderSwapDataType,
    SwapDataTypeCount
  };

  class RenderSwapContext {
  public:
    RenderSwapData &getLogicSwapData();

    RenderSwapData &getRenderSwapData();

    void swapLogicRenderData();

    void resetGameObjectResourceSwapData();

    void resetGameObjectToDelete();

    void resetCameraSwapData();

  private:
    uint8_t m_logic_swap_data_index{(uint8_t) SwapDataType::LogicSwapDataType};
    uint8_t m_render_swap_data_index{(uint8_t) SwapDataType::RenderSwapDataType};
    RenderSwapData m_swap_data[(uint8_t) SwapDataType::SwapDataTypeCount];

    bool isReadyToSwap() const;

    void swap();
  };
}

