#include "opengl_es_texture2D.h"

#include <stb/stb_image.h>
#include <string>


namespace Gp {
  OpenglESTexture2D::OpenglESTexture2D(const std::string &path) {
    stbi_set_flip_vertically_on_load(true);

    glGenTextures(1, &m_textureID);
    glBindTexture(GL_TEXTURE_2D, m_textureID);

    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    std::vector<uint8_t> buffer;
    if (!RenderUtility::AssetReadFile(path, buffer)) {
      // log out error
      acout << "Can't not read texture file=" + path << std::endl;
      m_is_valid = false;
    }

    uint32_t channels;
    // flip the picture whiling forming from raw data
//  stbi_set_flip_vertically_on_load(true);
    uint8_t *image_data =
        stbi_load_from_memory(buffer.data(), static_cast<int>(buffer.size()),
                              reinterpret_cast<int *>(&m_width),
                              reinterpret_cast<int *>(&m_height),
                              reinterpret_cast<int *> (&channels),
                              0);

    acout << "Image: width=" << m_width
          << " height=" << m_height
          << " channels=" << channels << std::endl;
    switch (channels) {
      case 3:
        glTexImage2D(
            GL_TEXTURE_2D, 0,
            GL_RGB,
            static_cast<int>(m_width),
            static_cast<int>(m_height),
            0, GL_RGB,
            GL_UNSIGNED_BYTE, image_data);
        break;
      case 4:
        glTexImage2D(
            GL_TEXTURE_2D, 0,
            GL_RGBA,
            static_cast<int>(m_width),
            static_cast<int> (m_height),
            0, GL_RGBA,
            GL_UNSIGNED_BYTE, image_data);
        break;
      default:
        // log out channel unknown
        acout << "Texture channel unknown: " << channels << std::endl;
        m_is_valid = false;
        break;
    }
    // generate mip levels. Not really needed for 2D, but good to do
    glGenerateMipmap(GL_TEXTURE_2D);


    stbi_image_free(image_data);
  }

  OpenglESTexture2D::OpenglESTexture2D(uint32_t width, uint32_t height)
      : m_height(height), m_width(width) {
    glGenTextures(1, &m_textureID);
    glBindTexture(GL_TEXTURE_2D, m_textureID);

    // register as GL_RGBA8
    glTexStorage2D(
        m_textureID, 1, GL_RGBA8,
        static_cast<int>(m_width),
        static_cast<int>(m_height)
    );

    glTexParameteri(m_textureID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(m_textureID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(m_textureID, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(m_textureID, GL_TEXTURE_WRAP_T, GL_REPEAT);

  }

  OpenglESTexture2D::~OpenglESTexture2D() {
    glDeleteTextures(1, &m_textureID);
  }

  uint32_t OpenglESTexture2D::GetWidth() const {
    return m_width;
  }

  uint32_t OpenglESTexture2D::GetHeight() const {
    return m_height;
  }

  uint32_t OpenglESTexture2D::GetTextureId() {
    return m_textureID;
  }

  void OpenglESTexture2D::SetData(void *data, uint32_t size) {
    // bbp: bytes per pixel
    uint32_t bbp = 4;
    assert(size == m_width * m_height * bbp);
    glTexSubImage2D(m_textureID, 0, 0, 0,
                    static_cast<int>(m_width),
                    static_cast<int>(m_height),
                    GL_RGBA,
                    GL_UNSIGNED_BYTE, data);
  }

  void OpenglESTexture2D::Bind(uint32_t slot) const {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_textureID);
  }
}