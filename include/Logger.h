#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

class Logger
{
    public:
    static void InitLogger() {
        // Sink do logowania w konsoli
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        console_sink->set_level(spdlog::level::info);
        console_sink->set_pattern("[%^%l%$] %v");

        // Sink do logowania do pliku
        auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/mylogfile.txt", true);
        file_sink->set_level(spdlog::level::trace);
        file_sink->set_pattern("[%Y-%m-%d %H:%M:%S] [%l] %v");

        // Logger używający obu sinków
        spdlog::logger logger("multi_sink", {console_sink, file_sink});
        logger.set_level(spdlog::level::trace); // Najniższy poziom logowania
        spdlog::register_logger(std::make_shared<spdlog::logger>(logger));

        spdlog::set_default_logger(spdlog::get("multi_sink")); // Ustaw jako domyślny
        spdlog::set_pattern("[%Y-%m-%d %H:%M:%S] [%^%L%$] %v"); // Globalny pattern
    }

    // Metoda do pobrania globalnego loggera
    static std::shared_ptr<spdlog::logger> GetLogger() {
        return spdlog::get("multi_sink");
    }
    Logger() ;
    ~Logger();

};