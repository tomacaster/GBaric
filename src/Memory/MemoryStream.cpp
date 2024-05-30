#include "Memory/MemoryStream.h"
#include <mutex>
#include <cstring>

using namespace Memory;

MemoryStream::MemoryStream(std::shared_ptr<Memory::DataObject> data) : _memory(data)
{
}

int MemoryStream::Open(void *opaque, void **datap, uint64_t *sizep)
{
    std::unique_lock lock(_mutex);
    //  auto stream = std::shared_ptr<DataObject>(static_cast<DataObject*>(opaque));
    if(!_memory)
    {
        return 1;
    }
    else
    {
      auto dataPtr = _memory->GetData();
      if(dataPtr)
      {
        auto d = reinterpret_cast<char*>(dataPtr.get());
        *datap = d;
      }
    }
    return 0;
}

ptrdiff_t MemoryStream::Read(void *opaque, unsigned char *buf, size_t len)
{
    std::shared_lock lock(_mutex); 
    auto dataPtr = static_cast<std::shared_ptr<std::vector<std::byte>>*>(opaque);

    if (!dataPtr || !*dataPtr) {
        
        return 0;
    }

    auto& data = *dataPtr; 

    size_t bytesToCopy = std::min(len, data->size()); 
    std::memcpy(buf, data->data(), bytesToCopy);

    return static_cast<ptrdiff_t>(bytesToCopy);

}

int MemoryStream::Seek(void *opaque, uint64_t offset)
{
    std::shared_lock lock(_mutex);
    return 0;
}

void MemoryStream::Close(void *opaque)
{
}
