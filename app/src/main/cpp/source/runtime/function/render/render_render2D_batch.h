#pragma once

#include <memory>

#include "runtime/function/render/render_vertex_array.h"
#include "runtime/function/render/render_shader.h"
#include "runtime/function/render/render_texture.h"
#include "runtime/function/render/render_camera.h"

#include "runtime/core/log/android_out.h"

// use render2D scene Data
#include "runtime/function/render/render_render2D.h"
// reuse s_sceneData
// reuse s_data

/*
 * speed:
 *  static batch rendering > instancing > dynamic batch rendering
 *  [reference]: https://www.imooc.com/article/321678
 *
 * dynamic vertexes Buffer
 * dynamic indexes Buffer
 * Vertex:
 *  Position: vec3
 *  FlatColor: vec4
 *  TextureCoord: vec2
 *  TextureID: float(index)
 *
 *  [instancing]: https://learnopengl-cn.github.io/04%20Advanced%20OpenGL/10%20Instancing/
 */

namespace Gp {

  class Renderer2DBatch {
  public:
    static void init();

    static void shutdown();

    static void beginScene(const RenderCamera &);

    static void endScene();

    static void drawQuad(
        const glm::vec3 &position,
        float rotatedAngle,
        const glm::vec2 &size,
        const glm::vec4 &color,
        const uint32_t instances_count
    );

    static void drawQuad(
        const glm::vec3 &position,
        float rotatedAngle,
        const glm::vec2 &size,
        const Texture2D::ptr &texture,
        const uint32_t instances_count
    );

    static void drawCircle(
        const glm::vec3 &position,
        const float radius,
        const glm::vec4 &color);

    static void drawCircle(
        const glm::vec3 &position,
        const float radius,
        const Texture2D::ptr &texture,
        const uint32_t instances_count
    );
  };
}