#pragma once

#include "VlcPlayerBase.h"
#include <memory>
#include <shared_mutex>
#include <vector>

namespace Players {
    namespace VlcPlayer {

        class VlcMemoryPlayer : public VlcPlayerBase {
        public:
            VlcMemoryPlayer(bool enableLogging);
            ~VlcMemoryPlayer();

            bool SetMedia(const std::string& path) override;

            static int Open(void* opaque, void** datap, uint64_t* sizep);
            static ssize_t Read(void* opaque, unsigned char* buf, size_t len);
            static int Seek(void* opaque, uint64_t offset);
            static void Close(void* opaque);

        private:
            static std::shared_ptr<Memory::DataObject> _memory;
            static std::shared_mutex _mutex;
        };

    }
}