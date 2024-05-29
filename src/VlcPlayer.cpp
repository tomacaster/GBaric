#include <iostream>
#include "VlcPlayer.h"
#include "Memory/MemoryStream.h"
#ifdef __linux__
#include <gdk/x11/gdkx.h>
#else
#include <gdk/win32/gdkwin32.h>
#endif
#include "Memory/FileManagerBase.h"
#include <filesystem>
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <memory>
#include "vlc/libvlc.h"

std::shared_ptr<Memory::DataObject> VlcPlayer::_memory;
std::shared_mutex VlcPlayer::_mutex;
std::shared_ptr<Player> VlcPlayer::_player;

VlcPlayer::VlcPlayer(bool enableLogging) :
_logger(nullptr),
_logging(enableLogging),
_renderSurface(nullptr)
{   
    _logger = Logger::GetClassLogger("VlcPlayer");
    if(_logger == nullptr)
    {
        
    }

    _player = std::make_shared<Player>();
    _player->_instance = libvlc_new(0, NULL);
    _player->_player = libvlc_media_player_new(_player->_instance);


    //_instance = std::make_shared<VLC::Instance>(VLC::Instance(0, nullptr));
   // if(enableLogging) _instance->logSet([this](int s, const libvlc_log_t *l, std::string m){ this->logCb(s, l, m); });
   // _mediaPlayer = std::make_shared<VLC::MediaPlayer>(VLC::MediaPlayer(*_instance.get()));
}

bool VlcPlayer::SetSurface(std::shared_ptr<RenderSurface> renderSurface)
{
    if(_player->_instance == nullptr)
    {
        std::cerr << "You should create player first" << std::endl; 
        
        return false;
    }
    _renderSurface = renderSurface;

#ifdef __linux__

    auto handle = GDK_SURFACE_XID(renderSurface->GetHandle());
    libvlc_media_player_set_xwindow(_player->_player, handle);
   // _mediaPlayer->setXwindow(handle);
    
#else
        auto handle = (GTK_WINDOW_HANDLE(_renderSurface->GetHandle()));
        libvlc_media_player_set_hwnd(*_mediaPlayer, handle);
#endif
    _logger->info("Player created");
    return true;
}

bool VlcPlayer::SetMedia(std::string path)
{    
    try
    {
        Memory::FileManagerBase manager = Memory::FileManagerBase();
        std::filesystem::path pth = std::filesystem::path("/home/michal/Documents/Projekty/video.mp4");
        auto file = manager.OpenFile(path, std::ios_base::openmode::_S_bin, false);

        std::vector<char> file_content((std::istreambuf_iterator<char>(*file)), std::istreambuf_iterator<char>());
        auto obj = std::make_shared<Memory::DataObject>();
        obj->SetData(file_content);
        _memory = obj;

        auto media = libvlc_media_new_callbacks(_player->_instance, *this->Open, *this->Read, *this->Seek, *this->Close, static_cast<void*>(_memory.get()));
        
        libvlc_media_player_set_media(_player->_player, media);
        libvlc_media_player_play(_player->_player);
        return true;
    }
    catch(const std::exception& e)
    {
        _logger->error(e.what());
      //  std::cerr << e.what() << '\n';
    }

    return true;
}

VlcPlayer::~VlcPlayer()
{

}

void VlcPlayer::logCb(int size, const libvlc_log_t *logT, std::string message)
{
    _logger->debug(message);
}



int VlcPlayer::Open(void *opaque, void **datap, uint64_t *sizep)
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
ptrdiff_t VlcPlayer::Read(void *opaque, unsigned char *buf, size_t len)
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

int VlcPlayer::Seek(void *opaque, uint64_t offset)
{
    std::shared_lock lock(_mutex);
    return 0;
}

void VlcPlayer::Close(void *opaque)
{
}
