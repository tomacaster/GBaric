#include <iostream>
#include "VlcPlayer.h"
#include "Memory/MemoryStream.h"
#ifdef __linux__
#include <gdk/x11/gdkx.h>
#else
#include <gdk/win32/gdkwin32.h>
#endif

using namespace Memory;

std::shared_ptr<spdlog::logger> VlcPlayer::_logger {nullptr};

VlcPlayer::VlcPlayer(bool enableLogging)  : logging(enableLogging)
{   
    _logger = Logger::GetClassLogger("VlcPlayer");
    if(_logger == nullptr)
    {
        
    }
    _instance = std::make_shared<VLC::Instance>(VLC::Instance(0, nullptr));
    if(enableLogging) _instance->logSet([this](int s, const libvlc_log_t *l, std::string m){ this->logCb(s, l, m); });
    _mediaPlayer = std::make_shared<VLC::MediaPlayer>(VLC::MediaPlayer(*_instance.get()));
}

bool VlcPlayer::SetSurface(std::shared_ptr<RenderSurface> renderSurface)
{
    if(_instance == nullptr)
    {
        std::cerr << "You should create player first" << std::endl; 
        
        return false;
    }
    _renderSurface = renderSurface;

#ifdef __linux__

    auto handle = GDK_SURFACE_XID(renderSurface->GetHandle());

    _mediaPlayer->setXwindow(handle);
    
#else
        auto handle = (GTK_WINDOW_HANDLE(_renderSurface->GetHandle()));
        libvlc_media_player_set_hwnd(*_mediaPlayer, handle);
#endif
    _logger->info("Player created");
    return true;
}

bool VlcPlayer::SetMedia(std::string path)
{
    auto stream = Memory::MemoryStream();
    VLC::Media med(*_instance, MemoryStream::Open, MemoryStream::Read, MemoryStream::Seek, MemoryStream::Close);
    _mediaPlayer->setMedia(med);
    
   _mediaPlayer->play();

    return true;
}

VlcPlayer::~VlcPlayer()
{

}

void VlcPlayer::logCb(int size, const libvlc_log_t *logT, std::string message)
{
    _logger->debug(message);
}
