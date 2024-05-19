#include <iostream>
#include <cstdlib>
#ifdef _WIN32
#include <Windows.h>
#endif
#include "Consts.h"
#include "Memory/Storage.h"

using namespace Memory;
namespace fs = std::filesystem;

std::shared_ptr<spdlog::logger> StorageBase::_logger { nullptr };
std::string StorageBase::_homeDir {""};

StorageBase::StorageBase()
{

}

std::string& StorageBase::InitStorage(std::string appName)
{
#ifdef __linux__
    auto appEnv = getenv(Consts::APP_DIR_ENV);
    if(appEnv) 
    {
        _homeDir = appEnv;
    }
    else
    {
        _homeDir = fs::path(getenv("HOME")).string() + "/." + appName;
        setenv(Consts::APP_DIR_ENV, _homeDir.c_str(), 1);
    }
    
#else
    _homeDir = fs::path(getenv("USERPROFILE")).string() +  "\\" + appName;
#endif

    if(!fs::exists(_homeDir))
    {
        try
        {
            auto res = fs::create_directory(_homeDir);

            if(!res)
            {
                std::cerr << "Cannot create home directory" << std::endl;
            }
            else 
            {
                
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << "Error during initialization: " << e.what() << std::endl;
        }

    }
    CreateFolders();
    Logger::InitLogger(_homeDir);

    return _homeDir;
}

std::string &StorageBase::GetHomedir()
{
    return _homeDir;
}

bool StorageBase::CreateFolders()
{
    auto res = fs::create_directory(fs::path(fs::path(_homeDir) / "Data"));

    return res;
}
