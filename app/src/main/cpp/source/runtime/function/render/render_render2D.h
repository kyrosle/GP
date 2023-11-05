#pragma once

#include <memory>

#include "runtime/function/render/render_vertex_array.h"
#include "runtime/function/render/render_shader.h"
#include "runtime/function/render/render_texture.h"
#include "runtime/function/render/render_camera.h"

#include "runtime/core/log/android_out.h"

namespace Gp {
  class Render2DBatch;

  class Renderer2D {
  public:
    friend class Render2DBatch;

    static void init();

    static void shutdown();

    static void beginScene(const RenderCamera &);

    static void endScene();

    static void drawQuad(
        const glm::vec2 &position,
        float rotatedAngle,
        const glm::vec2 &size,
        const glm::vec4 &color
    );

    static void drawQuad(
        const glm::vec3 &position,
        float rotatedAngle,
        const glm::vec2 &size,
        const glm::vec4 &color
    );

    static void drawQuad(
        const glm::vec2 &position,
        float rotatedAngle,
        const glm::vec2 &size,
        const Texture2D::ptr &texture
    );

    static void drawQuad(
        const glm::vec3 &position,
        float rotatedAngle,
        const glm::vec2 &size,
        const Texture2D::ptr &texture
    );

    static void drawCircle(
        const glm::vec3 &position,
        const float radius,
        const glm::vec4 &color);

    static void drawCircle(
        const glm::vec3 &position,
        const float radius,
        const Texture2D::ptr &texture);

  private:
    static void initQuad();

    static void initCircle();
  };
}
