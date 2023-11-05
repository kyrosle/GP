#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "runtime/function/framework/level/level.h"
#include "runtime/resource/res_type/common/world.h"

namespace Gp {

  class WorldManager {
  public:
    typedef std::shared_ptr<WorldManager> ptr;

    ~WorldManager() { clear(); }

    void initialize();

    void clear();

//    void reloadCurrentLevel();

//    void saveCurrentLevel();

    void tick(float delta_tim);

    Level::w_ptr getCurrentActiveLevel() const { return m_current_active_level; }

  private:
    void loadDefaultWorld();

    void loadDefaultLevel();
//    bool loadWorld(const std::string &world_url);
//
//    bool loadLevel(const std::string &level_url);

    bool m_is_world_loaded{false};
//    std::string m_current_world_url;
    WorldRes::ptr m_current_world_res;

    // all loaded level, key: level url, value: level instance
    std::unordered_map<std::string, Level::ptr> m_loaded_levels;

    // active level, currently we just support one active level
    Level::w_ptr m_current_active_level;
  };

}

