#pragma once

#include <thread>
#include <shared_mutex>
#include "VlcPlayerBase.h"
 
using namespace Memory;

namespace Players
{
    namespace VlcPlayer
    {
        class VlcMemoryPlayer : VlcPlayerBase
        {
            public:
                VlcPlayer(bool enableLogging);        
                ~VlcPlayer();
            private:
                static std::shared_ptr<Memory::DataObject> _memory;
                static std::shared_mutex _mutex;
                static std::shared_ptr<Player> _player;
                static int Open(void *opaque, void **datap, uint64_t *sizep);
                static ptrdiff_t Read(void *opaque, unsigned char *buf, size_t len);
                static int Seek(void *opaque, uint64_t offset);
                static void Close(void *opaque);
        };
    }
}
