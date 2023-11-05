#include "texture_component.h"

namespace Gp {
  void TextureComponent::postLoadResource(std::weak_ptr<GObject> parent_object) {
    m_parent_object = parent_object;

    m_raw_texture_res.m_texture_file = m_texture_res.m_obj_file_ref;
  }

  void TextureComponent::tick(float deltaTime) {
    // it doesn't make sense.
  }
}