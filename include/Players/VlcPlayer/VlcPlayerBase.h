#pragma once

#include "vlc/vlc.h"
#include "Logger.h"
#include "RenderSurface.h"
#include "Memory/DataObject.h"

namespace Players
{
    namespace VlcPlayer
    {
        typedef class struct Player
        {
            public:
                libvlc_instance_t* _instance;
                libvlc_media_t* _media;
                libvlc_media_player_t* _player;

                Player() : _instance(nullptr), _media(nullptr), _player(nullptr) {};
                ~Player() 
                {
                    libvlc_media_release(_media);
                    libvlc_media_player_release(_player);
                    libvlc_release(_instance);
                };
        } Player;

        class VlcPlayerBase
        {
            public:
                std::shared_ptr<spdlog::logger> _logger;
                bool _logging = false;
                std::shared_ptr<RenderSurface> _renderSurface;
                VlcPlayerBase(bool &enableVlcLogging);
                void SetupSurface(void* surface);
                bool SetSurface(std::shared_ptr<RenderSurface> renderSurface);
                bool SetMedia(std::string path);
            private:
                void LogCb(int size, const libvlc_log_t* logT, std::string message);

        };
    }
}
