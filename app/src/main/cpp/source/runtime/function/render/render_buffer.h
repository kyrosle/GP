/*
 * About vertex buffer binding:
 * https://www.haroldserrano.com/blog/what-are-vertex-array-bindings-in-opengl
 */

#pragma once

#include <memory>
#include <string>
#include <vector>
#include <optional>

#include <GLES3/gl3.h>

namespace Gp {
  enum class ShaderDataType {
    None = 0,
    Float,
    Float2,
    Float3,
    Float4,
    Mat3,
    Mat4,
    Int,
    Int2,
    Int3,
    Int4,
    Bool
  };

  static uint32_t ShaderDataTypeSize(ShaderDataType type) {
    switch (type) {
      case ShaderDataType::Float:
        return 4;
      case ShaderDataType::Float2:
        return 4 * 2;
      case ShaderDataType::Float3:
        return 4 * 3;
      case ShaderDataType::Float4:
        return 4 * 4;
      case ShaderDataType::Mat3:
        return 4 * 3 * 3;
      case ShaderDataType::Mat4:
        return 4 * 4 * 4;
      case ShaderDataType::Int:
        return 4;
      case ShaderDataType::Int2:
        return 4 * 2;
      case ShaderDataType::Int3:
        return 4 * 3;
      case ShaderDataType::Int4:
        return 4 * 4;
      case ShaderDataType::Bool:
        return 1;
      default:
//      LOG_ERROR("Unknown ShaderDataType!");
        return 0;
    }
  }

  static int GetShaderTypeDataCount(const ShaderDataType &type) {
    switch (type) {
      case ShaderDataType::Float:
        return 1;
      case ShaderDataType::Float2:
        return 2;
      case ShaderDataType::Float3:
        return 3;
      case ShaderDataType::Float4:
        return 4;
      case ShaderDataType::Mat3:
        return 3 * 3;
      case ShaderDataType::Mat4:
        return 4 * 4;
      case ShaderDataType::Int:
        return 1;
      case ShaderDataType::Int2:
        return 2;
      case ShaderDataType::Int3:
        return 3;
      case ShaderDataType::Int4:
        return 4;
      case ShaderDataType::Bool:
        return 1;
      default:
//      LOG_ERROR("Unknown ShaderDataType!");
        return 0;
    }
  }

  static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
    switch (type) {
      case ShaderDataType::Float:
        return GL_FLOAT;
      case ShaderDataType::Float2:
        return GL_FLOAT;
      case ShaderDataType::Float3:
        return GL_FLOAT;
      case ShaderDataType::Float4:
        return GL_FLOAT;
      case ShaderDataType::Mat3:
        return GL_FLOAT;
      case ShaderDataType::Mat4:
        return GL_FLOAT;
      case ShaderDataType::Int:
        return GL_INT;
      case ShaderDataType::Int2:
        return GL_INT;
      case ShaderDataType::Int3:
        return GL_INT;
      case ShaderDataType::Int4:
        return GL_INT;
      case ShaderDataType::Bool:
        return GL_BOOL;
      default:
//        LOG_ERROR("Unknown ShaderDataType!");
        return 0;
    }

  }


  /*!
   * Belongs to VertexBuffer,
   * the basic element such as:
   * @example { ShaderDataType::Float3, "a_Position" }
   */
  class BufferElement {
  public:
    typedef std::shared_ptr<BufferElement> ptr;

    BufferElement(
        ShaderDataType type, const std::string &name, bool normalized = false)
        : m_name(name),
          m_type(type),
          m_size(ShaderDataTypeSize(type)),
          m_isNormalized(normalized),
          m_offset(0) {}

    static BufferElement CreateInstancingBufferElement(
        ShaderDataType type,
        const std::string &name,
        uint32_t bind_buffer,
        bool normalized = false);

    void SetOffset(uint32_t offset) { m_offset = offset; }

    uint32_t GetSize() const { return m_size; }

    uint32_t GetOffset() const { return m_offset; }

    ShaderDataType GetType() const { return m_type; }

    bool IsIntegerType() const;

    bool IsNormalized() const { return m_isNormalized; }

    void SetInstancing(uint32_t bind_index) { m_instancing_bind = bind_index; }

    bool HasInstancing() const { return m_instancing_bind.has_value(); }

    uint32_t GetInstancing() const { return m_instancing_bind.value(); }

  private:
    std::string m_name;

    ShaderDataType m_type;

    uint32_t m_size;
    uint32_t m_offset;

    bool m_isNormalized;
    std::optional<uint32_t> m_instancing_bind{std::nullopt};
  };


  /*!
   * Constructed by @a BufferElement
   */
  class BufferLayout {
  public:
    BufferLayout() {}

    BufferLayout(const std::initializer_list<BufferElement> &elements)
        : m_elements(elements) {
      CalculateOffsetAndStride();
    }

    inline const std::vector<BufferElement> &
    GetElements() { return m_elements; }

    inline const uint32_t GetCount() const { return m_elements.size(); }

    inline const int GetStride() const { return m_stride; }

    std::vector<BufferElement>::iterator begin() { return m_elements.begin(); }

    std::vector<BufferElement>::iterator end() { return m_elements.end(); }


  private:
    void CalculateOffsetAndStride();

    uint32_t m_stride;
    std::vector<BufferElement> m_elements;
  };
}

