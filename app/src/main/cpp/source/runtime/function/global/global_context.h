#pragma once

#include <string>
#include <game-activity/native_app_glue/android_native_app_glue.h>

#include "runtime/core/log/android_out.h"
#include "runtime/core/log/log_system.h"
#include "runtime/platform/file_service/file_service.h"
#include "runtime/function/render/render_system.h"
#include "runtime/function/render/window_system.h"
#include "runtime/function/framework/world/world_manager.h"

namespace Gp {
  class LogSystem;

  class RenderSystem;

  class WindowSystem;

  class FileSystem;

  class WorldManager;

  class AssetManager;

  /*
   * Manage the lifetime and creation/destruction
   * order of all global system.
   */
  class RuntimeGlobalContext {
  public:
    typedef std::shared_ptr<RuntimeGlobalContext> ptr;

    /*!
     * create all global systems and initialize these system.
     * @param config_file_path
     */
    void startSystems(
        struct android_app *app, const std::string &config_file_path);

    /*!
     * destroy all global systems.
     */
    void shutdownSystems();

  public:
    struct android_app *m_app;


    std::shared_ptr<LogSystem> m_logger_system;
    std::shared_ptr<RenderSystem> m_render_system;
    std::shared_ptr<WindowSystem> m_window_system;
    std::shared_ptr<FileSystem> m_file_system;
    std::shared_ptr<WorldManager> m_world_manager;
    std::shared_ptr<AssetManager> m_asset_manager;
  };

  extern RuntimeGlobalContext g_runtime_global_context;
}

