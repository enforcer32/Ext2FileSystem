#pragma once

#include <string>
#include <spdlog/spdlog.h>

namespace Ext2
{
	class Logger
	{
	public:
		static void Init(const std::string& name = "Logger");
		inline static std::shared_ptr<spdlog::logger> GetLogger() { return s_Logger; }

	private:
		inline static std::shared_ptr<spdlog::logger> s_Logger;
	};
}

#define LOGGER_INFO(...)		Ext2::Logger::GetLogger()->info(__VA_ARGS__)
#define LOGGER_WARN(...)		Ext2::Logger::GetLogger()->warn(__VA_ARGS__)
#ifdef BUILD_DEBUG
#define LOGGER_DEBUG(...)		Ext2::Logger::GetLogger()->debug(__VA_ARGS__)
#else
#define LOGGER_DEBUG(...)
#endif
#define LOGGER_ERROR(...)		Ext2::Logger::GetLogger()->error(__VA_ARGS__)
#define LOGGER_CRITICAL(...)	Ext2::Logger::GetLogger()->critical(__VA_ARGS__)
#define LOGGER_TRACE(...)		Ext2::Logger::GetLogger()->trace(__VA_ARGS__)
