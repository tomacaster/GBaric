#pragma once

#include <filesystem>
#include <string>
#include "Logger.h"

class StorageBase
{
    public:
        StorageBase();
        static std::string& InitStorage(std::string appName);
        bool CleanStorage(bool force);
        std::string& GetHomedir();
    private:
        static std::shared_ptr<spdlog::logger> _logger;
        static std::string _homeDir;
        static bool CreateFolders();
};