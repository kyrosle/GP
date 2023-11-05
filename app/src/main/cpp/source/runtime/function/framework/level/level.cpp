#include "level.h"

#include "runtime/core/log/android_out.h"

#include "runtime/function/framework/component/mesh/mesh_component.h"
#include "runtime/function/framework/component/transform/transform_component.h"

namespace Gp {

  bool Level::load(const std::string &level_res_url) {
    acout << "Loading level: " << level_res_url << std::endl;

    m_level_url = level_res_url;

    LevelRes level_res;
    // load asset form asset_manager -> &level_res

    // create object -> level_res.m_objects
//    for (const ObjectInstanceRes &object_instance_res: level_res.m_objects) {
//      createObject(object_instance_res);
//    }


    // create active character
    for (const auto &object_pair: m_gobjects) {
      GObject::ptr object = std::get<1>(object_pair);
      if (object == nullptr) {
        continue;
      }

      if (level_res.m_character_name == object->getName()) {
        m_current_active_character = std::make_shared<Character>(object);
        break;
      }
    }
    m_is_loaded = true;

    return true;
  }

  void Level::loadDefault() {
    // add testing gobject here:

    acout << "create default object" << std::endl;
    createDefaultObjects();
    m_is_loaded = true;
  }

  void Level::unload() {
    clear();
  }

  GObjectID Level::createObject(const ObjectInstanceRes &object_instance_res) {
    GObjectID object_id = ObjectIDAllocator::alloc();
    assert(object_id != k_invalid_gobject_id);

    GObject::ptr gobject;
    try {
      gobject = std::make_shared<GObject>(object_id);
    } catch (const std::bad_alloc &) {
      acout << "cannot allocate memory for new gobject" << std::endl;
    }

    gobject->load(object_instance_res);

    // gobject load
    m_gobjects.emplace(object_id, gobject);

    return object_id;
  }

  void Level::createDefaultObjects() {
    for (int i = 0; i < 2; ++i) {
      GObjectID object_id = ObjectIDAllocator::alloc();
      assert(object_id != k_invalid_gobject_id);

      GObject::ptr gobject;
      try {
        gobject = std::make_shared<GObject>(object_id);
      } catch (const std::bad_alloc &) {
        acout << "cannot allocate memory for new gobject" << std::endl;
      }

      acout << "gobject default load" << std::endl;
      gobject->defaultLoad(i);

      // gobject load
      m_gobjects.emplace(object_id, gobject);
    }
  }

  void Level::tick(float delta_time) {
    if (!m_is_loaded) {
      return;
    }

    // tick all object in current level
    for (const auto &id_object_pair: m_gobjects) {
      assert(std::get<1>(id_object_pair));
      // gobject
      if (std::get<1>(id_object_pair)) {
        // gobject -> tick
        std::get<1>(id_object_pair)->tick(delta_time);
      }
    }
    // tick character in current level
    if (m_current_active_character) {
      m_current_active_character->tick(delta_time);
    }
  }

  GObject::w_ptr Level::getGObjectByID(GObjectID go_id) const {
    auto iter = m_gobjects.find(go_id);
    if (iter != m_gobjects.end()) {
      return iter->second;
    }

    return {};
  }

  void Level::deleteGObjectByID(GObjectID go_id) {}

  void Level::clear() {
    m_current_active_character.reset();
    m_gobjects.clear();
  }


}