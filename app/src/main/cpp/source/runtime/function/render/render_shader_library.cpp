#include "render_shader_library.h"

#include "runtime/core/log/android_out.h"

namespace Gp {
  std::unordered_map<std::string, Shader::ptr> RenderShaderLibrary::m_map;

  void RenderShaderLibrary::Load(const std::string &shaderName) {
    auto prefix_path = "Shaders/";
    auto vertexPath = prefix_path + shaderName + ".vs";
    auto fragmentPath = prefix_path + shaderName + ".fs";
    Shader::ptr shader = Shader::CreateFromFiles(vertexPath, fragmentPath);

    m_map[shaderName] = std::move(shader);
  }

  void RenderShaderLibrary::Load(
      const std::string &shaderVsName,
      const std::string &shaderFsName) {
    auto prefix_path = "Shaders/";
    auto vertexPath = prefix_path + shaderVsName + ".vs";
    auto fragmentPath = prefix_path + shaderFsName + ".fs";
    Shader::ptr shader = Shader::CreateFromFiles(vertexPath, fragmentPath);

    m_map[shaderVsName] = std::move(shader);
  }

  Shader::ptr RenderShaderLibrary::Get(const std::string &shaderName) {
    if (!Contains(shaderName)) {
      acout << "Shader Not Found, name=" << shaderName << std::endl;
    }
    return m_map[shaderName];
  }

  bool RenderShaderLibrary::Contains(const std::string &shaderName) {
    return m_map.find(shaderName) != m_map.end();
  }

}