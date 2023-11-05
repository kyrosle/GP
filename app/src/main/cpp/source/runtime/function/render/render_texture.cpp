#include "render_texture.h"

#include "runtime/function/render/interface/opengles/opengl_es_texture2D.h"

namespace Gp {
  Texture2D::ptr Texture2D::Create(const std::string &path) {
    // opengl es
    return Texture2D::ptr(new OpenglESTexture2D(path));
  }

  Texture2D::ptr Texture2D::Create(uint32_t width, uint32_t height) {
    // opengl es
    return Texture2D::ptr(new OpenglESTexture2D(width, height));
  }

  Texture2D *Texture2D::CreateRaw(const std::string &path) {
    return static_cast<Texture2D *>(new OpenglESTexture2D(path));
  }
}