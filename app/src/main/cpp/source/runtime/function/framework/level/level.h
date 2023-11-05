#pragma once

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

#include "runtime/resource/res_type/common/level.h"
#include "runtime/function/framework/object/object.h"
#include "runtime/function/framework/object/object_id_allocator.h"
#include "runtime/function/character/character.h"

namespace Gp {
  using LevelObjectsMap = std::unordered_map<Gp::GObjectID, GObject::ptr>;

  class Level {
  public:
    typedef std::shared_ptr<Level> ptr;
    typedef std::weak_ptr<Level> w_ptr;

    virtual ~Level() {};

    bool load(const std::string &level_res_url);

    void loadDefault();

    void unload();

//    void save();

    void tick(float delta_time);

    const std::string &getLevelResUrl() const { return m_level_url; }

    const LevelObjectsMap &getAllGObjects() const { return m_gobjects; }

    GObject::w_ptr getGObjectByID(GObjectID go_id) const;

    Character::w_ptr getCurrentActiveCharacter() const {
      return m_current_active_character;
    }

    GObjectID createObject(const ObjectInstanceRes &object_instance_res);

    void createDefaultObjects();

    void deleteGObjectByID(GObjectID go_id);

  private:
    void clear();

    bool m_is_loaded{false};
    std::string m_level_url;

    // all game objects in this level, key: object id, value: object instance
    LevelObjectsMap m_gobjects;

    Character::ptr m_current_active_character;
  };

}

