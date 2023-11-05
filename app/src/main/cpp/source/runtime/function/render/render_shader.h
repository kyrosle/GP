#pragma once

#include <memory>
#include <GLES3/gl3.h>
#include <glm/glm.hpp>

namespace Gp {
  enum class ShaderType : unsigned int {
    VertexShader = GL_VERTEX_SHADER,
    FragmentShader = GL_FRAGMENT_SHADER,
  };

  class Shader {
  public:
    typedef std::shared_ptr<Shader> ptr;
    typedef std::unique_ptr<Shader> u_ptr;
    typedef uint32_t ShaderId;

    virtual ~Shader() {};

    virtual void Bind() const = 0;

    virtual void UnBind() const = 0;

    virtual void
    UploadUniformMat4(const std::string &uniformName, glm::mat4 matrix) = 0;

    virtual void
    UploadUniformVec4(const std::string &uniformName, glm::vec4 vec4) = 0;

    virtual void UploadUniformI1(const std::string &uniformName, int id) = 0;

    static std::shared_ptr<Shader> CreateFromFiles(
      const std::string &, const std::string &);

    static std::shared_ptr<Shader> CreateFromSource(
      const std::string &, const std::string &);

  protected:
    // shader program id
    ShaderId m_RendererID;
  };
}
