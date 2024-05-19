#pragma once

#include "FileManagerBase.h"
#include <string>
#include "Logger.h"

namespace Memory
{
    class StorageBase : FileManagerBase
    {
        public:
            StorageBase();
            static std::string& InitStorage(std::string appName);
            bool CleanStorage(bool force);
            std::string& GetHomedir();
        private:
            static std::shared_ptr<spdlog::logger> _logger;
            static std::string _homeDir;
            static bool CreateAppFolders();
    };
}
