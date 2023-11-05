#pragma once

#include <cassert>
#include <GLES3/gl3.h>
#include <android/asset_manager.h>
#include <vector>

#include "runtime/function/global/global_context.h"
#include "runtime/function/render/render_guid_allocator.h"
#include "runtime/function/render/render_entity.h"
#include "runtime/core/log/android_out.h"
#include "runtime/platform/file_service/file_service.h"


namespace Gp {

  class RenderUtility {
  public:
    static bool CheckAndLogGlError(bool alwaysLog = false);

    static inline void AssertGlError() { assert(CheckAndLogGlError()); }

    /**
     * Generates an orthographic projection matrix given the half height, aspect ratio, near, and far
     * planes
     *
     * @param outMatrix the matrix to write into
     * @param halfHeight half of the height of the screen
     * @param aspect the width of the screen divided by the height
     * @param near the distance of the near plane
     * @param far the distance of the far plane
     * @return the generated matrix, this will be the same as @a outMatrix so you can chain calls
     *     together if needed
     */
    static float *BuildOrthographicMatrix(
        float *outMatrix,
        float halfHeight,
        float aspect,
        float near,
        float far);

    static float *BuildIdentityMatrix(float *outMatrix);

    /**
     * Read file from `asset` directory
     * @param assetManager always passing from struct android_app
     * @param assetPath the asset path from asset directory
     * @param buf the data render_buffer,
     * `T` type has check: std::vector<uint_8>, * std::string,
     * ! whether T.data() to acquire the buffer raw pointer
     *
     * @return the raw data from the corresponding file and storing in `buf`,
     * if the file was successfully read return true(read size == actual size),
     * otherwise return false
     */
    template<typename T>
    static bool AssetReadFile(
        const std::string &assetPath,
        T &buffer
    ) {
      if (assetPath.empty()) {
        // log out
        return false;
      }
      FileSystem::File *file =
          g_runtime_global_context.m_file_system
              ->open(assetPath.c_str(),
                     FileSystem::FileMode::BUFFER);

      if (file == nullptr) {
        // log out
        return false;
      }

      // attention! if the file is large, use u_int64_t, and getLength64
      uint32_t fileLength = FileSystem::getLength(file);

      buffer.resize(fileLength);
      int32_t readSize = FileSystem::read(file, buffer.data(), fileLength);

      FileSystem::file_close(file);
      return (readSize == buffer.size());
    }
  };

}

