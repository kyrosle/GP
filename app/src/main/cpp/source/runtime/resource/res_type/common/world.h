#pragma once

#include <string>
#include <vector>
#include <memory>

namespace Gp {

  class WorldRes {
  public:
    typedef std::shared_ptr<WorldRes> ptr;

    // world name
    std::string m_name;

    // all level for this world
    std::vector<std::string> m_level_urls;

    // the default level for this world, which should be first loading level
    std::string m_default_level_url;
  };

}