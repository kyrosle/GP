#pragma once

#include <memory>

#include "runtime/function/global/global_context.h"

namespace Gp {
  class AssetManager {
  public:
    typedef std::shared_ptr<AssetManager> ptr;

    template<typename AssetType>
    bool loadAsset(const std::string &asset_url, AssetType &out_asset) const {
      // read json file to string
      return false;
    }

    template<typename AssetType>
    bool saveAsset(AssetType &out_asset, const std::string &asset_url) const {
      return false;
    }

    template<typename AssetContainer /* vector<uint8_t>, std::string */>
    bool loadAssetToString(const std::string &asset_url, AssetContainer &out_asset) const {
      if (asset_url.empty()) {
        // log out
        return false;
      }
      FileSystem::File *file =
          g_runtime_global_context.m_file_system
              ->open(asset_url.c_str(),
                     FileSystem::FileMode::BUFFER);

      if (file == nullptr) {
        // log out
        return false;
      }

      // attention! if the file is large, use u_int64_t, and getLength64
      uint32_t fileLength = FileSystem::getLength(file);

      out_asset.resize(fileLength);
      int32_t readSize = FileSystem::read(file, out_asset.data(), fileLength);

      FileSystem::file_close(file);
      return (readSize == out_asset.size());
    }
  };

  // get full path
}