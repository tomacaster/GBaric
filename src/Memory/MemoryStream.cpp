#include "Memory/MemoryStream.h"


using namespace Memory;

MemoryStream::MemoryStream() : _memory(nullptr)
{
}

int MemoryStream::Open(void *opaque, void **datap, uint64_t *sizep)
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

ptrdiff_t MemoryStream::Read(void *opaque, unsigned char *buf, size_t len)
{
    return ptrdiff_t();
}

int MemoryStream::Seek(void *opaque, uint64_t offset)
{
    return 0;
}

void MemoryStream::Close(void *opaque)
{
}
