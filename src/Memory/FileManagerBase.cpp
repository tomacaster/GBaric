#include "Memory/FileManagerBase.h"
#include <iostream>
#include <fstream>

using namespace Memory;
using std::fstream;

std::shared_ptr<spdlog::logger> FileManagerBase::_logger { nullptr };

FileManagerBase::FileManagerBase()
{
    _logger = Logger::GetClassLogger("FileManager");
}

std::shared_ptr<std::fstream> FileManagerBase::OpenFile(const fs::path& path, std::ios_base::openmode mode, bool createIf)
{
    try
    {        
        if(createIf && !fs::exists(path))      
        {
            std::ofstream {path};
        }
        auto fb = std::make_shared<std::fstream>(path, mode);
        if(fb->is_open())
        {
            _logger->debug("Opening: \"{}\"", path.string());
            
            return fb;
        }
        else
        {
            _logger->error("Cannot open file \"{}\"", path.string());

            return nullptr;
        }
    }
    catch(const std::exception& e)
    {
        _logger->error("Error during opening file \"{}\": \n", path.string(), e.what());

        return nullptr;
    }
}

bool FileManagerBase::SaveFile(const fs::path& path, bool overwrite)
{
    return false;
}

bool FileManagerBase::CreateFile(const fs::path& path, bool overwrite)
{
    try
    {
        if(fs::exists(path))
        {
            if(!overwrite)
            {
                _logger->warn("Cannot overwrite: \"{}\"", path.string());
                return false;
            }
            else
            {
                std::fstream file(path, std::ios::out);
                if (file.is_open()) 
                {
                    file.close();
                    _logger->debug("File created: \"{}\"", path.string());
                    return true;
                } 
                else 
                {
                    _logger->error("Cannot create file: \"{}\"", path.string());
                    return false;
                }
            }
        }
    }
    catch(const std::exception& e)
    {
        _logger->error("Error during creating file \"{}\": \n", path.string(), e.what());
        return false;
    }
}

bool Memory::FileManagerBase::CreateDirectory(const fs::path &path)
{
    try
    {
        _logger->debug("Creating dir: {}", path.string());

        if(fs::exists(path) || fs::create_directory(path))
        {
            _logger->debug("Directory created: \"{}\"", path.string());
            return true;
        }
        else
        {
            _logger->error("Cannot create directory: \"{}\"", path.string());
            return false;
        }
    }
    catch(const std::exception& e)
    {
        _logger->error("Error during creating directory \"{}\": \n", path.string(), e.what());
        return false;
    }
}
