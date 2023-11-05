#include "opengl_es_shader.h"

#include <string>
#include <glm/gtc/type_ptr.hpp>

#include "runtime/core/log/android_out.h"
#include "runtime/function/render/render_utility.h"

namespace Gp {

  void OpenglESShader::LoadFromFile(const std::string &vertPath,
                                    const std::string &fragPath) {
    std::string vertSource, fragSource;
    if (!RenderUtility::AssetReadFile(vertPath, vertSource)) {
      acout << "vertex file not exist" << std::endl;
    }
    if (!RenderUtility::AssetReadFile(fragPath, fragSource)) {
      acout << "fragment file not exist" << std::endl;
    }
    return LoadFromSource(vertSource, fragSource);
  }

  void OpenglESShader::LoadFromSource(const std::string &vertSource,
                                      const std::string &fragSource) {
    // load vertex shade from source code
    uint32_t vertexShader = loadShader(ShaderType::VertexShader,
                                       vertSource);
    if (!vertexShader) {
      acout << "vertex shader load failed" << std::endl;
    }

    // load fragment shader from source code
    uint32_t fragmentShader = loadShader(ShaderType::FragmentShader,
                                         fragSource);
    if (!fragmentShader) {
      acout << "fragment shader load failed" << std::endl;
      glDeleteShader(vertexShader);
    }

    // create shader program(ID)
    uint32_t program = glCreateProgram();
    if (program) {
      glAttachShader(program, vertexShader);
      glAttachShader(program, fragmentShader);

      glLinkProgram(program);
      int linkStatus = GL_FALSE;
      glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
      if (linkStatus != GL_TRUE) {
        int logLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);

        // If we fail to link the shader program, log the result for debugging
        if (logLength) {
          auto *log = new GLchar[logLength];
          glGetProgramInfoLog(program, logLength, nullptr, log);
          acout << "Failed to link program with:\n" << log << std::endl;
          delete[] log;
        }
        glDeleteProgram(program);
      }
      m_RendererID = program;
    }

  }

  void OpenglESShader::Bind() const {
    glUseProgram(m_RendererID);
  }

  void OpenglESShader::UnBind() const {
    glUseProgram(0);
  };

  uint32_t
  OpenglESShader::loadShader(ShaderType shaderType,
                             const std::string &shaderSource) {
    uint32_t shader = glCreateShader((uint32_t) shaderType);
    if (shader) {
      auto *shaderRawString = (char *) shaderSource.c_str();
      auto shaderLength = static_cast<GLint>(shaderSource.length());
      glShaderSource(shader, 1, &shaderRawString, &shaderLength);
      glCompileShader(shader);

      int shaderCompiled = 0;
      glGetShaderiv(shader, GL_COMPILE_STATUS, &shaderCompiled);

      // If the shader doesn't compile, log the result to the terminal for debugging
      if (!shaderCompiled) {
        int infoLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLength);

        if (infoLength) {
          auto *infoLog = new GLchar[infoLength];
          glGetShaderInfoLog(shader, infoLength, nullptr, infoLog);
          acout << "Failed to compile with:\n" << infoLog << std::endl;
          delete[] infoLog;
        }

        glDeleteShader(shader);
        shader = 0;
      }
    }
    return shader;
  }

  OpenglESShader::~OpenglESShader() {
    glDeleteShader(m_RendererID);
  }

  void OpenglESShader::UploadUniformMat4(const std::string &uniformName,
                                         glm::mat4 matrix) {
    glUniformMatrix4fv(
      glGetUniformLocation(m_RendererID, uniformName.c_str()),
      1, GL_FALSE, glm::value_ptr(matrix)
    );
  }

  void OpenglESShader::UploadUniformVec4(const std::string &uniformName,
                                         glm::vec4 vec4) {
    glUniform4fv(
      glGetUniformLocation(m_RendererID, uniformName.c_str()),
      1, glm::value_ptr(vec4)
    );
  }

  void OpenglESShader::UploadUniformI1(const std::string &uniformName, int id) {
    glUniform1i(
      glGetUniformLocation(m_RendererID, uniformName.c_str()),
      id
    );
  }
}