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
            MemoryStream(std::shared_ptr<Memory::DataObject> data);
            int Open(void *opaque, void **datap, uint64_t *sizep);
            ptrdiff_t Read(void *opaque, unsigned char *buf, size_t len);
            int Seek(void *opaque, uint64_t offset);
            void Close(void *opaque);
        private:
            std::shared_mutex _mutex;
            std::shared_ptr<DataObject> _memory;
    };
}
