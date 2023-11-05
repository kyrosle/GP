#pragma once

#include <memory>

#include "runtime/function/render/render_shader.h"

namespace Gp {

  class OpenglESShader : public Shader {
  public:
    typedef std::shared_ptr<OpenglESShader> ptr;
    typedef std::unique_ptr<OpenglESShader> u_ptr;

    void LoadFromFile(const std::string &vertPath,
                      const std::string &fragPath);

    void LoadFromSource(const std::string &vertSource,
                        const std::string &fragSource);

    virtual ~OpenglESShader() override;

    void Bind() const override;

    void UnBind() const override;

    void UploadUniformMat4(const std::string &uniformName,
                           glm::mat4 matrix) override;

    void
    UploadUniformVec4(const std::string &uniformName, glm::vec4 vec4) override;

    void UploadUniformI1(const std::string &uniformName, int id) override;

  private:
    static unsigned int loadShader(
      ShaderType shaderType, const std::string &shaderSource);
  };

}

