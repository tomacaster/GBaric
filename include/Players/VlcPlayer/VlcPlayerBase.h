#pragma once

#include "vlc/vlc.h"
#include "Logger.h"
#include "RenderSurface.h"

namespace Players
{
    namespace VlcPlayer
    {
        class PlayerObject
        {
            public:
                libvlc_instance_t* _instance {nullptr};
                libvlc_media_t* _media {nullptr};
                libvlc_media_player_t* _player {nullptr};

                PlayerObject() {}
                ~PlayerObject()
                {
                    if (_media)
                        libvlc_media_release(_media);
                    if (_player)
                        libvlc_media_player_release(_player);
                    if (_instance)
                        libvlc_release(_instance);
                }
        };

        class VlcPlayerBase
        {
            public:
                VlcPlayerBase(RenderSurface& surface, bool enableVlcLogging);
                virtual ~VlcPlayerBase() {};
                bool SetSurface();
                virtual bool SetMedia(const std::string& path) = 0;
            protected:
                void LogCb(int size, const libvlc_log_t* logT, const std::string& message);
                std::shared_ptr<spdlog::logger> _logger;
                bool _logging;
                RenderSurface *_renderSurface;
                std::shared_ptr<PlayerObject> _player;
        };
    }
}