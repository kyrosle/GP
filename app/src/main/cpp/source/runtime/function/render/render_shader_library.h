#pragma once

#include <unordered_map>
#include <string>

#include "runtime/function/render/render_shader.h"

namespace Gp {

  /*!
   * All shader assets are putting in assets/Shaders/
   * vertex shader has suffix .vs
   * fragment shader has suffix .fs
   */
  class RenderShaderLibrary {
  public:
    /*!
     * Load shader, and put it into the shaders container.
     * @param shaderName shader name,
     */
    static void Load(const std::string &shaderName);

    static void Load(const std::string &shaderVsName, const std::string &shaderFsName);

    /*!
     * Get the shader form shaders container.
     * @param shaderName  shader name,
     * @return the shared_ptr of shader
     * for example: the shader file is `Shaders/FlatColorShader.fs` and `Shaders/FlatColorShader.vs`
     * and then the shader name should be `FlatColorShader`.
     */
    static Shader::ptr Get(const std::string &shaderName);

    static bool Contains(const std::string &shaderName);

  private:
    static std::unordered_map<std::string, Shader::ptr> m_map;
  };

}
