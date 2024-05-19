#include "Memory/MemoryStream.h"


using namespace Memory;

MemoryStream::MemoryStream(std::shared_ptr<DataObject> data) : _memory(std::move(data))
{
}

int MemoryStream::Open(void *opaque, void **datap, uint64_t *sizep)
{
  //  auto stream = std::shared_ptr<DataObject>(static_cast<DataObject*>(opaque));
    if(!_memory)
    {
        return 1;
    }
    else
    {
        auto d = reinterpret_cast<char*>(_memory->GetData().get());
      //  *datap = 
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
