#pragma once

#include <mutex>

#include "VlcPlayerBase.h"

namespace Players::VlcPlayer
{
    class VlcGLPlayer : protected VlcPlayerBase
    {
        public:
                typedef struct libvlc_video_setup_device_cfg_t {
                unsigned width;
                unsigned height;
                unsigned full_range;
                // Dodatkowe pola, jeśli potrzebne
            } libvlc_video_setup_device_cfg_t;
            VlcGLPlayer(RenderSurface& renderSurface, bool enableLogging);
            ~VlcGLPlayer();
            bool SetMedia(const std::string& path) override;
        protected:

            static void* lock(void* opaque, void** planes);
            static void unlock(void* opaque, void* picture, void* const* planes);
            static void display(void* opaque, void* picture);
            static unsigned format_setup(void** opaque, char* chroma, unsigned* width, unsigned* height, unsigned* pitches, unsigned* lines);
            static void format_cleanup(void* opaque);
    };
}