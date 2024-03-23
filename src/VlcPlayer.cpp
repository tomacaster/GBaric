#include <iostream>
#include "VlcPlayer.h"

VlcPlayer::VlcPlayer(bool enableLogging = false, void* windowHandle)  : logging(enableLogging)
{   
    _instance = std::make_unique<VLC::Instance>(VLC::Instance(0, nullptr));
    if(enableLogging) _instance->logSet([this](int s, const libvlc_log_t *l, std::string m){ this->logCb(s, l, m); });
    _mediaPlayer = std::make_unique<VLC::MediaPlayer>(VLC::MediaPlayer(*_instance.get()));
}

bool VlcPlayer::SetMedia(std::string path)
{
    _media = std::make_shared<VLC::Media>(VLC::Media(path, VLC::Media::FromType::FromPath));
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
