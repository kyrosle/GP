#include "world_manager.h"

#include "runtime/core/log/android_out.h"

namespace Gp {

  void WorldManager::initialize() {
    m_is_world_loaded = false;

//    m_current_world_url
    loadDefaultWorld();

    // level debugger
  }

  void WorldManager::clear() {
    // upload all level
    for (auto &level: m_loaded_levels) {
    }
    m_loaded_levels.clear();

    m_current_world_res.reset();

//    m_current_world_url.clear();
    m_is_world_loaded = false;
  }

  void WorldManager::tick(float delta_time) {
    if (!m_is_world_loaded) {
      // load world
      // load default for now
      loadDefaultWorld();
    }

    // tick the active level
    Level::ptr active_level = m_current_active_level.lock();
    if (active_level) {
      active_level->tick(delta_time);
      // level debugger tick
    }
  }

  void WorldManager::loadDefaultWorld() {
    WorldRes world_res;
    // load from asset manager ok
    m_current_world_res = std::make_shared<WorldRes>(world_res);

    loadDefaultLevel();

    m_is_world_loaded = true;
  }

  void WorldManager::loadDefaultLevel() {
    Level::ptr level = std::make_shared<Level>();
    // set current level temporarily
    m_current_active_level = level;

    acout << "default level load" << std::endl;
    level->loadDefault();

    m_loaded_levels.emplace("default", level);
  }

}