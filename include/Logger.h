#pragma once
#include <vector>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

class Logger
{
    public:
        static void InitLogger();

        static std::shared_ptr<spdlog::logger> GetClassLogger(std::string name);
        Logger();
        ~Logger();
    private:
        static const std::string MAIN_LOGGER_PATTERN;
        static std::shared_ptr<spdlog::sinks::stdout_color_sink_mt> _consoleSink;
        static std::shared_ptr<spdlog::sinks::basic_file_sink_mt> _fileSink;
};