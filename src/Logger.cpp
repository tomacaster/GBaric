#include "Logger.h"

const std::string Logger::MAIN_LOGGER_PATTERN {"[%d-%m-%Y %H:%M:%S.%e] %n [%^%L%$] %v"};
std::shared_ptr<spdlog::sinks::stdout_color_sink_mt> Logger::_consoleSink {nullptr};
std::shared_ptr<spdlog::sinks::basic_file_sink_mt> Logger::_fileSink {nullptr};

Logger::Logger()
{
   
}

void Logger::InitLogger()
{
    _consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    _consoleSink->set_level(spdlog::level::info);
    _consoleSink->set_pattern("[%^%l%$] %v");

    _fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/logs.log", true);
    _fileSink->set_level(spdlog::level::trace);
    _fileSink->set_pattern("[%d-%m-%Y %H:%M:%S] [%l] %v");

    spdlog::logger logger("mainLogger", {_consoleSink, _fileSink});
    logger.set_level(spdlog::level::trace); 
    spdlog::register_logger(std::make_shared<spdlog::logger>(logger));

    spdlog::set_default_logger(spdlog::get("mainLogger")); 
    spdlog::set_pattern(MAIN_LOGGER_PATTERN); 
}

std::shared_ptr<spdlog::logger> Logger::GetClassLogger(std::string name)
{
    spdlog::logger log(name, {_consoleSink, _fileSink});
    log.set_level(spdlog::level::trace); 
    spdlog::register_logger(std::make_shared<spdlog::logger>(log));
    
    return spdlog::get(name);
}

Logger::~Logger()
{
    
}