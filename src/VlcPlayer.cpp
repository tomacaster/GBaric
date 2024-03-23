#include <iostream>
#include "VlcPlayer.h"
#ifdef __linux__
#include <gdk/x11/gdkx.h>
#else
#include <gdk/win32/gdkwin32.h>
#endif


VlcPlayer::VlcPlayer(bool enableLogging)  : logging(enableLogging)
{   
    _instance = std::make_unique<VLC::Instance>(VLC::Instance(0, nullptr));
    if(enableLogging) _instance->logSet([this](int s, const libvlc_log_t *l, std::string m){ this->logCb(s, l, m); });
    _mediaPlayer = std::make_unique<VLC::MediaPlayer>(VLC::MediaPlayer(*_instance.get()));
}

bool VlcPlayer::SetSurface(std::shared_ptr<RenderSurface> renderSurface)
{
    if(_instance)
    {
        std::cerr << "You should create second player first" << std::endl; 
        
        return false;
    }
    _renderSurface = renderSurface;

#ifdef __linux__
    auto handle = (void*)GTK_WINDOW_HANDLE(renderSurface->GetHandle());
    auto win = static_cast<uint32_t>(reinterpret_cast<std::intptr_t>(handle));
    libvlc_media_player_set_xwindow(*_mediaPlayer, win);
#else
    auto handle = (GTK_WINDOW_HANDLE(_renderSurface->GetHandle()));
        libvlc_media_player_set_hwnd(*_mediaPlayer, handle);
#endif
    std::cout << "Window created" << std::endl;
    return true;
}

bool VlcPlayer::SetMedia(std::string path)
{
    _media = std::make_shared<VLC::Media>(VLC::Media( path, VLC::Media::FromType::FromPath));
    _mediaPlayer->setMedia(*_media);
    _mediaPlayer->play();

    return true;
}

VlcPlayer::~VlcPlayer()
{

}

void VlcPlayer::logCb(int size, const libvlc_log_t *logT, std::string message)
{
    std::cout << message << std::endl;
}
