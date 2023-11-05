#pragma once

#include <memory>

#include "runtime/function/framework/object/object.h"
#include "runtime/core/math/math_header.h"

namespace Gp {

  class Character {
  public:
    typedef std::shared_ptr<Character> ptr;
    typedef std::weak_ptr<Character> w_ptr;

    Character(GObject::ptr character_object);

    GObjectID getObjectID() const;

    void setObject(GObject::ptr gObject);

    GObject::w_ptr getObject() const { return m_character_object; }

    void tick(float deltaTime);

  private:
    glm::vec3 m_position;
    float m_rotation;

    GObject::ptr m_character_object;

    // hack for setting rotation frame buffer
//    Quaternion m_rotation_buffer;
//    bool m_rotation_dirty{false};
  };

}
