#include "Memory.h"

Memory::Memory() : _memory(nullptr)
{
}

int Memory::Open(void *opaque, void **datap, uint64_t *sizep)
{
    auto stream = std::shared_ptr<DataObject>(static_cast<DataObject*>(opaque));
    if(!stream)
    {
        return 1;
    }
    else
    {
        *datap = static_cast<void*>(stream->GetData().get());
    }
    return 0;
}

ptrdiff_t Memory::Read(void *opaque, unsigned char *buf, size_t len)
{
    return ptrdiff_t();
}

int Memory::Seek(void *opaque, uint64_t offset)
{
    return 0;
}

void Memory::Close(void *opaque)
{
}
