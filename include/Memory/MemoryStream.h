#pragma once

#include <thread>
#include <shared_mutex>
#include <cstddef>
#include <cstdint>
#include "DataObject.h"

namespace Memory
{
    class MemoryStream
    {
        public:
            MemoryStream();
            static int Open(void *opaque, void **datap, uint64_t *sizep);
            static ptrdiff_t Read(void *opaque, unsigned char *buf, size_t len);
            static int Seek(void *opaque, uint64_t offset);
            static void Close(void *opaque);
        private:
            std::shared_ptr<DataObject> _memory;
            std::shared_mutex _mutex;
    };
}
