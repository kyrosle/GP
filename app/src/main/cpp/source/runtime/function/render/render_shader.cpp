#include "render_shader.h"

#include "runtime/function/render/interface/opengles/opengl_es_shader.h"

namespace Gp {

  Shader::ptr Shader::CreateFromFiles(
    const std::string &vertPath, const std::string &fragPath) {
    auto shader = new OpenglESShader();
    shader->LoadFromFile(vertPath, fragPath);
    return Shader::ptr(shader);
  }

  Shader::ptr
  Shader::CreateFromSource(
    const std::string &vertSource, const std::string &fragSource) {
    auto shader = new OpenglESShader();
    shader->LoadFromSource(vertSource, fragSource);
    return Shader::ptr(shader);
  }
}