#include "runtime/core/log/log_system.h"
#include "android_out.h"

#include <spdlog/async.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/ostream_sink.h>
#include <spdlog/spdlog.h>

namespace Gp {
  LogSystem::LogSystem() {
    auto console_sink = std::make_shared<spdlog::sinks::ostream_sink_mt>
      (acout, true);
    console_sink->set_level(spdlog::level::trace);
    console_sink->set_pattern("[%^%l%$] %v");

    const spdlog::sinks_init_list sink_list = {console_sink};

    spdlog::init_thread_pool(8192, 1);

    m_logger = std::make_shared<spdlog::async_logger>(
      "console", sink_list.begin(), sink_list.end(),
      spdlog::thread_pool(), spdlog::async_overflow_policy::block);
    m_logger->set_level(spdlog::level::trace);

    spdlog::register_logger(m_logger);
  }

  LogSystem::~LogSystem() {
    m_logger->flush();
    spdlog::drop_all();
  }

} // namespace Piccolo
