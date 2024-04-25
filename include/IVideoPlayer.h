#pragma once

#include <string>
#include "RenderSurface.h"

class IVideoPlayer
{
    public:
        virtual bool SetSurface(std::shared_ptr<RenderSurface> renderSurface) = 0;
        virtual bool SetMedia(std::string path) = 0;
        virtual bool Play() = 0;
        virtual bool Pause() = 0;
        virtual bool Stop() = 0;
        virtual bool Rewind() = 0;
        virtual bool SetLoop() = 0;

}