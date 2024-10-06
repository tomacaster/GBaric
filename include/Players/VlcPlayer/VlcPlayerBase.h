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
            libvlc_instance_t* _instance;
            libvlc_media_t* _media;
            libvlc_media_player_t* _player;

            PlayerObject() : _instance(nullptr), _media(nullptr), _player(nullptr) {}
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
            std::shared_ptr<spdlog::logger> _logger;
            bool _logging;
            std::shared_ptr<RenderSurface> _renderSurface;
            std::shared_ptr<PlayerObject> _player;

            VlcPlayerBase(bool enableVlcLogging);
            void SetupSurface(void* surface);
            bool SetSurface(std::shared_ptr<RenderSurface> renderSurface);
            virtual bool SetMedia(const std::string& path) = 0;
        private:
            void LogCb(int size, const libvlc_log_t* logT, const std::string& message);
        };
    }
}