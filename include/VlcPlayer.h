#pragma once

#include  "vlcpp/vlc.hpp"
#include "RenderSurface.h"

class VlcPlayer
{
    protected:
        
    public:
        VlcPlayer(bool enableLogging = false);        
       // bool SetSurface(std::shared_ptr<RenderSurface> renderSurface);
        bool SetMedia(std::string path);
        ~VlcPlayer();
    private:

        bool logging = false;
        std::unique_ptr<VLC::MediaPlayer> _mediaPlayer;
        std::unique_ptr<VLC::Instance> _instance;
        std::shared_ptr<RenderSurface> _renderSurface;
        VLC::MediaPtr _media;

        void logCb(int size, const libvlc_log_t* logT, std::string message);

};