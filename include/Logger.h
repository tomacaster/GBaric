#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

class Logger
{
    public:
        static void InitLogger() 
        {
            auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
            console_sink->set_level(spdlog::level::info);
            console_sink->set_pattern("[%^%l%$] %v");

            auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/logs.log", true);
            file_sink->set_level(spdlog::level::trace);
            file_sink->set_pattern("[%d-%m-%Y %H:%M:%S] [%l] %v");

            spdlog::logger logger("multi_sink", {console_sink, file_sink});
            logger.set_level(spdlog::level::trace); 
            spdlog::register_logger(std::make_shared<spdlog::logger>(logger));

            spdlog::set_default_logger(spdlog::get("multi_sink")); 
            spdlog::set_pattern("[%d-%m-%Y %H:%M:%S] [%^%L%$] %v"); 
        }

        static std::shared_ptr<spdlog::logger> GetLogger() 
        {
            return spdlog::get("multi_sink");
        }
        Logger();
        ~Logger();

};