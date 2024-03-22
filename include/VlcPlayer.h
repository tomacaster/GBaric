#pragma once

#include  "vlcpp/vlc.hpp"

class VlcPlayer
{
    protected:
        
    public:
        VlcPlayer(bool enableLogging = false);        
        bool SetMedia(std::string path);
        ~VlcPlayer();
    private:

        bool logging = false;
        std::unique_ptr<VLC::MediaPlayer> _mediaPlayer;
        std::unique_ptr<VLC::Instance> _instance;
        VLC::MediaPtr _media;

        void logCb(int size, const libvlc_log_t* logT, std::string message);

};