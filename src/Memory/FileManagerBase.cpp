#include "Memory/FileManagerBase.h"
#include <iostream>

using namespace Memory;

FileManagerBase::FileManagerBase()
{
    _logger = Logger::GetClassLogger("FileManager");
}

std::shared_ptr<std::fstream> FileManagerBase::OpenFile(const fs::path& path, std::ios_base::openmode mode, bool createIf)
{
    try
    {        
        std::fstream fb(path, mode);        
        if(fb.is_open())
        {
            _logger->debug("Opening: \"{}\"", path.string());
            return std::make_shared<std::fstream>(std::move(fb));
        }
        else
        {
            _logger->error("Cannot open file \"{}\"", path.string());

            return nullptr;
        }
    }
    catch(const std::exception& e)
    {
        _logger->error("Error during openning file \"{}\": \n", path.string(), e.what());

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
        std::fstream file(path, std::ios::out);
        if (file.is_open()) 
        {
            file.close();
            _logger->debug("File created: {}", path.string());
            return true;
        } 
        else 
        {
            _logger->error("Cannot create file: {}", path.string());
            return false;
        }
    }
    catch(const std::exception& e)
    {
        _logger->error("Error during creating file \"{}\": \n", path.string(), e.what());
        return false;
    }
}
