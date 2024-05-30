#pragma once

#include <filesystem>
#include <fstream>
#include <ostream>
#include <iostream>
#include <shared_mutex>
#include "Logger.h"

namespace Memory
{
    namespace fs = std::filesystem;
    class FileManagerBase
    {
        public:
            FileManagerBase();
            std::shared_ptr<std::ifstream> OpenFile(const fs::path& path, std::ios_base::openmode mode, bool createIf = true);
            bool SaveFile(const fs::path& path, bool overwrite = false);
            static bool CreateFile(const fs::path& path, bool overwrite = false);
            static bool CreateDirectory(const fs::path& path);
        private:
            static std::shared_ptr<spdlog::logger> _logger;
            std::shared_mutex _mutex;
    };
}


