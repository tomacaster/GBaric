#include "VlcPlayerBase.h"
#ifdef __linux__
#include <gdk/x11/gdkx.h>
#else
#include <gdk/win32/gdkwin32.h>
#endif
#include "Memory/FileManagerBase.h"
#include <filesystem>
#include <iostream>
#include <fstream>

VLcPlayerBase::VlcPlayerBase() :
_logger(nullptr),
_logging(enableLogging),
_renderSurface(nullptr)
{
    
}

bool VLcPlayerBase::SetSurface(std::shared_ptr<RenderSurface> renderSurface)
{
    if(_player->_instance == nullptr)
    {
        std::cerr << "You should create player first" << std::endl; 
        
        return false;
    }
    _renderSurface = renderSurface;

#ifdef __linux__

    auto handle = GDK_SURFACE_XID(renderSurface->GetHandle());
    libvlc_media_player_set_xwindow(_player->_player, handle);
   // _mediaPlayer->setXwindow(handle);
    
#else
        auto handle = (GTK_WINDOW_HANDLE(_renderSurface->GetHandle()));
        libvlc_media_player_set_hwnd(*_mediaPlayer, handle);
#endif
    _logger->info("Player created");
    return true;
}

bool VLcPlayerBase::SetMedia(std::string path)
{    
    try
    {
        Memory::FileManagerBase manager = Memory::FileManagerBase();
        std::filesystem::path pth = std::filesystem::path("/home/michal/Documents/Projekty/video.mp4");
        auto file = manager.OpenFile(path, std::ios_base::openmode::_S_bin, false);
        std::vector<char> file_content((std::istreambuf_iterator<char>(*file)), std::istreambuf_iterator<char>());
        auto obj = std::make_shared<Memory::DataObject>();

        obj->SetData(file_content);
        _memory = obj;
        auto media = libvlc_media_new_callbacks(_player->_instance, 
                                                *this->Open, 
                                                *this->Read, 
                                                *this->Seek, 
                                                *this->Close, 
                                                static_cast<void*>(_memory.get()));        
        libvlc_media_player_set_media(_player->_player, media);
        libvlc_media_player_play(_player->_player);
        
        return true;
    }
    catch(const std::exception& e)
    {
        _logger->error(e.what());
    }

    return true;
}

void VLcPlayerBase::LogCb(int size, const libvlc_log_t *logT, std::string message)
{
    _logger->debug(message);
}
