#pragma once

#include <memory>

#include "runtime/function/render/render_vertex_array.h"
#include "runtime/function/render/render_command.h"
#include "runtime/function/render/render_shader.h"

namespace Gp {

  class RenderControl {
  public:
    typedef std::shared_ptr<RenderControl> ptr;
    typedef std::unique_ptr<RenderControl> u_ptr;

    /*!
     * Accept the relevant parameters of the Scene scene,
     * such as Camera, lighting, to ensure that shaders can
     * get the correct environment-related uniforms.
     */
    static void BeginScene();

    static void EndScene();

    /*!
     * vao set command by RenderCommand, and then transfer command
     * to RenderCommandQueue
     */
    static void
    Submit(const Shader::ptr &, const VertexArray::ptr &, const glm::mat4 &);

    // opengl es
  private:
  };

}

