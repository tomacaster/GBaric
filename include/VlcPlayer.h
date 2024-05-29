#pragma once
#include "vlc/vlc.h"
#include "Logger.h"
#include "RenderSurface.h"
#include "Memory/DataObject.h"
#include <thread>
#include <shared_mutex>
 
using namespace Memory;

typedef struct Player
{
    libvlc_instance_t* _instance;
    libvlc_media_t* _media;
    libvlc_media_player_t* _player;
} Player;

class VlcPlayer
{
    protected:
        
    public:
        VlcPlayer(bool enableLogging);        
        void SetupSurface(void* surface);
        bool SetSurface(std::shared_ptr<RenderSurface> renderSurface);
        bool SetMedia(std::string path);
        ~VlcPlayer();
    private:
        std::shared_ptr<spdlog::logger> _logger;
        bool _logging = false;
        std::shared_ptr<RenderSurface> _renderSurface;
        static std::shared_ptr<Memory::DataObject> _memory;
        static std::shared_mutex _mutex;
        static std::shared_ptr<Player> _player;
        static int Open(void *opaque, void **datap, uint64_t *sizep);
        static ptrdiff_t Read(void *opaque, unsigned char *buf, size_t len);
        static int Seek(void *opaque, uint64_t offset);
        static void Close(void *opaque);
        void logCb(int size, const libvlc_log_t* logT, std::string message);

};