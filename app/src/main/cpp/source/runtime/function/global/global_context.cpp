#include "global_context.h"

#include "runtime/resource/asset_manager/asset_manager.h"

namespace Gp {
  RuntimeGlobalContext g_runtime_global_context;

  void
  RuntimeGlobalContext::startSystems(
      struct android_app *app, const std::string &config_file_path) {
    // store the reference of android app context
    m_app = app;

    acout << "log system startup" << std::endl;
    // log system
    m_logger_system = std::make_shared<LogSystem>(LogSystem());

    acout << "asset manager startup" << std::endl;
    m_asset_manager = std::make_shared<AssetManager>();

    acout << "file system startup" << std::endl;
    m_file_system = std::make_shared<FileSystem>(FileSystem());
    m_file_system->initialize(app->activity->assetManager);

    acout << "window system startup" << std::endl;
    // window system
    m_window_system = std::make_shared<WindowSystem>();
    m_window_system->initialize(app);

    acout << "render system startup" << std::endl;
    // render system
    m_render_system = std::make_shared<RenderSystem>();
    Gp::RenderSystemInitInfo render_info;
    render_info.window_system = m_window_system;
    m_render_system->initialize(render_info);

    acout << "world manager startup" << std::endl;
    m_world_manager = std::make_shared<WorldManager>();
    m_world_manager->initialize();
  }

  void RuntimeGlobalContext::shutdownSystems() {
    m_asset_manager.reset();
    m_logger_system.reset();
    m_render_system->clear();
    m_render_system.reset();
    m_window_system.reset();
    m_world_manager.reset();
  }
}
