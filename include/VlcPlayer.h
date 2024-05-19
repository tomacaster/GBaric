#pragma once

#include "Logger.h"
#include  "vlcpp/vlc.hpp"
#include "RenderSurface.h"

class VlcPlayer
{
    protected:
        
    public:
        VlcPlayer(bool enableLogging);        
        void SetupSurface(void* surface);
        bool SetSurface(std::shared_ptr<RenderSurface> renderSurface);
        bool SetMedia(std::string path);
        ~VlcPlayer();
    private:
        static std::shared_ptr<spdlog::logger> _logger;
        bool logging = false;
        std::shared_ptr<VLC::MediaPlayer> _mediaPlayer;
        std::shared_ptr<VLC::Instance> _instance;
        std::shared_ptr<RenderSurface> _renderSurface;
        VLC::MediaPtr _media;

        void logCb(int size, const libvlc_log_t* logT, std::string message);

};