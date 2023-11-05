#include "render_buffer.h"

namespace Gp {
  bool BufferElement::IsIntegerType() const {
    return m_type == ShaderDataType::Int;
  }

  void BufferLayout::CalculateOffsetAndStride() {
    m_stride = 0;
    for (auto &element: m_elements) {
      if (element.HasInstancing()) {
        continue;
      }
      element.SetOffset(m_stride);
      m_stride += element.GetSize();
    }
  }

  BufferElement
  BufferElement::CreateInstancingBufferElement(
      ShaderDataType type,
      const std::string &name,
      uint32_t bind_buffer,
      bool normalized) {
    auto buffer_element = BufferElement(type, name, normalized);
    buffer_element.SetInstancing(bind_buffer);
    return buffer_element;
  }
}