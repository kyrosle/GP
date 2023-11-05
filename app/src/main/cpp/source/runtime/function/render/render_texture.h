#pragma once

#include <memory>

namespace Gp {

  class Texture {
  public:
    typedef std::shared_ptr<Texture> ptr;

    virtual ~Texture() = default;

    virtual uint32_t GetWidth() const = 0;

    virtual uint32_t GetHeight() const = 0;

    // for multi platform, the return value should be void*
    // buf for opengl/opengl es, is u_int32_t a id value
    virtual uint32_t GetTextureId() = 0;

    virtual void SetData(void *data, uint32_t size) = 0;

    virtual void Bind(uint32_t slot = 0) const = 0;

    bool validate() { return m_is_valid; }

  protected:
    bool m_is_valid{true};
  };

  class Texture2D : public Texture {
  public:
    typedef std::shared_ptr<Texture2D> ptr;

    static Texture2D *CreateRaw(const std::string &path);

    static Texture2D::ptr Create(const std::string &path);

    static Texture2D::ptr Create(uint32_t width, uint32_t height);
  };

}
