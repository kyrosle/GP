#pragma once


#include <memory>
#include <vector>

#include "runtime/function/framework/component/transform/transform_component.h"
#include "runtime/function/framework/component/component.h"
#include "runtime/function/render/render_object.h"
#include "runtime/resource/res_type/components/texture.h"

namespace Gp {
  /*
   * The texture part of SpriteRenderComponent
   */
  class TextureComponent : public ComponentBase {
  public:
    typedef std::shared_ptr<TextureComponent> ptr;

    TextureComponent() : ComponentBase("TextureComponent") {};

    TextureComponent(TextureComponentRes mesh_res)
        : ComponentBase("TextureComponent"), m_texture_res(mesh_res) {};

    void postLoadResource(std::weak_ptr<GObject> parent_object) override;

    const GameObjectTextureDesc &getRawTextureRes() const { return m_raw_texture_res; }

    void tick(float deltaTime) override;

  private:
    TextureComponentRes m_texture_res;

    GameObjectTextureDesc m_raw_texture_res;
  };

}