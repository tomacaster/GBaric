#include <iostream>
#include <cstdlib>
#include <fmt/core.h>
#ifdef _WIN32
#include <Windows.h>
#endif
#include "Consts.h"
#include "Memory/Storage.h"

using namespace Memory;

std::shared_ptr<spdlog::logger> StorageBase::_logger { nullptr };
std::string StorageBase::_homeDir { "" };

StorageBase::StorageBase()
{

}

std::string& StorageBase::InitStorage(std::string appName)
{

    auto appEnv = getenv(Consts::APP_DIR_ENV);
    if(appEnv) 
    {
        _homeDir = appEnv;
    }
    else
    {
#ifdef __linux__
        std::string path = fmt::format("{}/.{}", getenv("HOME"), appName.c_str());
#else
        std::string path = fmt::format("{}\\{}", getenv("USERPROFILE"), appName.c_str());
#endif
        _homeDir = fs::path(path);
        setenv(Consts::APP_DIR_ENV, _homeDir.c_str(), 1);
    }

    if(!fs::exists(_homeDir))
    {
        try
        {
            auto res = CreateDirectory(_homeDir); //fs::create_directory(_homeDir);

            if(!res)
            {
                std::cerr << "Cannot create home directory" << std::endl;
            }
            else 
            {
                CreateAppFolders();
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << "Error during initialization: " << e.what() << std::endl;
        }
    }
    Logger::InitLogger(_homeDir);

    return _homeDir;
}

std::string &StorageBase::GetHomedir()
{
    return _homeDir;
}

bool StorageBase::CreateAppFolders()
{
    auto res = CreateDirectory(fmt::format("{}/{}", _homeDir, "Data"));

    return res;
}
