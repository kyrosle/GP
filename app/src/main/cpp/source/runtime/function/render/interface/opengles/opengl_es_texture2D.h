#pragma once

#include <memory>
#include <GLES3/gl3.h>
#include <vector>

#include "runtime/function/render/render_texture.h"
#include "runtime/function/render/render_utility.h"

namespace Gp {

  class OpenglESTexture2D : public Texture2D {
  public:
    typedef std::shared_ptr<OpenglESTexture2D> ptr;

    OpenglESTexture2D(const std::string &path);

    OpenglESTexture2D(uint32_t width, uint32_t height);

    ~OpenglESTexture2D();

    virtual uint32_t GetWidth() const override;

    virtual uint32_t GetHeight() const override;

    // for multi platform, the return value should be void*
    // buf for opengl/opengl es, is u_int32_t a id value
    virtual uint32_t GetTextureId() override;

    virtual void SetData(void *data, uint32_t size) override;

    virtual void Bind(uint32_t slot = 0) const override;

  private:
    uint32_t m_textureID;
    uint32_t m_width;
    uint32_t m_height;
  };

}

