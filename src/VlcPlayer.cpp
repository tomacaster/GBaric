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
 
using namespace Memory;

std::shared_ptr<spdlog::logger> VlcPlayer::_logger {nullptr};

VlcPlayer::VlcPlayer(bool enableLogging)  : logging(enableLogging)
{   
    _logger = Logger::GetClassLogger("VlcPlayer");
    if(_logger == nullptr)
    {
        
    }
    _instance = std::make_shared<VLC::Instance>(VLC::Instance(0, nullptr));
    if(enableLogging) _instance->logSet([this](int s, const libvlc_log_t *l, std::string m){ this->logCb(s, l, m); });
    _mediaPlayer = std::make_shared<VLC::MediaPlayer>(VLC::MediaPlayer(*_instance.get()));
}

bool VlcPlayer::SetSurface(std::shared_ptr<RenderSurface> renderSurface)
{
    if(_instance == nullptr)
    {
        std::cerr << "You should create player first" << std::endl; 
        
        return false;
    }
    _renderSurface = renderSurface;

#ifdef __linux__

    auto handle = GDK_SURFACE_XID(renderSurface->GetHandle());

    _mediaPlayer->setXwindow(handle);
    
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
    // auto rawFile = manager.OpenFile(path, std::ios_base::openmode::_S_bin, false);
        std::basic_ifstream<char> fStream{pth, std::ios::binary};
    std::vector<char> file_content((std::istreambuf_iterator<char>(fStream)), std::istreambuf_iterator<char>());
    
    // Konwertuj vector<char> na vector<std::byte>
    std::vector<std::byte> byte_content(file_content.size());
    std::memcpy(byte_content.data(), file_content.data(), file_content.size());

    auto data = std::make_shared<Memory::DataObject>();
    data->SetData(std::move(byte_content)); // Przekazanie danych do obiektu DataObject

    auto stream = std::make_shared<Memory::MemoryStream>(data);


        VLC::Media med(*_instance, 
                    [stream](void* opaque, void** datap, uint64_t* sizep) { return stream->Open(opaque, datap, sizep); }, 
                    [stream](void* opaque, unsigned char* buf, size_t len) { return stream->Read(opaque, buf, len); },
                    [stream](void* opaque, uint64_t offset) { return stream->Seek(opaque, offset); },
                    [stream](void* opaque) { return stream->Close(opaque); });
        _mediaPlayer->setMedia(med);

    
    
        _mediaPlayer->play();
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
