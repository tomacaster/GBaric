#pragma once

#include <filesystem>
#include <fstream>
#include "Logger.h"

namespace Memory
{
    namespace fs = std::filesystem;
    class FileManagerBase
    {
        public:
            FileManagerBase();
            std::shared_ptr<std::fstream> OpenFile(const fs::path& path, std::ios_base::openmode mode, bool createIf = true);
            bool SaveFile(const fs::path& path, bool overwrite = false);
            bool CreateFile(const fs::path& path, bool overwrite = false);
        private:
            std::shared_ptr<spdlog::logger> _logger;
    };
}


