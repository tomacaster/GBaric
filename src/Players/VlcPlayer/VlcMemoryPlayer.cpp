#include <iostream>
#include "VlcMemoryPlayer.h"
#include "Memory/MemoryStream.h"
#include <vector>
#include <iterator>
#include <memory>

std::shared_ptr<Memory::DataObject> VlcPlayer::_memory;
std::shared_mutex VlcPlayer::_mutex;
std::shared_ptr<Player> VlcPlayer::_player;

VlcMemorVlcMemoryPlayeryPlayerVlcMemoryPlayer::VlcPlayer(bool enableLogging) :
{   
    _logger = Logger::GetClassLogger("VlcPlayer");
    if(_logger == nullptr)
    {
        
    }

    _player = std::make_shared<Player>();
    _player->_instance = libvlc_new(0, NULL);
    _player->_player = libvlc_media_player_new(_player->_instance);
}

VlcMemoryPlayer::~VlcPlayer()
{

}


int VlcMemoryPlayer::Open(void *opaque, void **datap, uint64_t *sizep)
{
    std::shared_lock lock(_mutex);
    auto dataPtr = static_cast<DataObject*>(opaque);
    if(!dataPtr)
    {
        return 1;
    }
    else
    {
        auto data = dataPtr->GetData();
        if(data)
        {
            *datap = data->data();
        }
    }
    return 0;
}
ptrdiff_t VlcMemoryPlayer::Read(void *opaque, unsigned char *buf, size_t len)
{
    std::shared_lock lock(_mutex); 
    auto dataPtr = static_cast<std::shared_ptr<std::vector<std::byte>>*>(opaque);

    if (!_memory ) {
        
        return 0;
    }

    auto& data = *_memory; 

    size_t bytesToCopy = std::min(len, data.size()); 
    std::memcpy(buf, data.GetData()->data(), bytesToCopy);

    return static_cast<ptrdiff_t>(bytesToCopy);

}

int VlcMemoryPlayer::Seek(void *opaque, uint64_t offset)
{
    std::shared_lock lock(_mutex);
    return 0;
}

void VlcMemoryPlayer::Close(void *opaque)
{
}
