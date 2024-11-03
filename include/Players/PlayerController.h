#pragma once

#include <chrono>

#include "Storage/FileCommon.h"
#include "PlayerCommon.h"

namespace Players {
    class PlayerController {
    public:
        virtual ~PlayerController() = default;

        virtual void Init() = 0;
        virtual bool Play() = 0;
        virtual bool Pause() = 0;
        virtual bool Stop(bool rewind = false) = 0;
        virtual bool Rewind() = 0;
        virtual bool Seek(std::chrono::milliseconds position) = 0;
        virtual bool Load(const Memory::Storage::FileCommon& file) = 0;
        virtual std::chrono::milliseconds GetDuration() = 0;
        virtual std::chrono::milliseconds GetTime() = 0;
        virtual bool IsPlaying() = 0;
        virtual bool CanPlay() = 0;
        virtual bool Release() = 0;
    };
}