#include "Players/VlcPlayer/VlcMemoryPlayer.h"
#include "Memory/FileManagerBase.h"
#include "vlc/libvlc_media.h"
#include <vector>
#include <iterator>
#include <memory>
#include <cstring>

namespace Players {
    namespace VlcPlayer {
        std::shared_ptr<Memory::DataObject> VlcMemoryPlayer::_memory;
        std::shared_mutex VlcMemoryPlayer::_mutex;

        VlcMemoryPlayer::VlcMemoryPlayer(bool enableLogging) : VlcPlayerBase(enableLogging) 
        {
            _logger = Logger::GetClassLogger("VlcPlayer");
            if (!_logger) 
            {
                _logger = spdlog::stdout_color_mt("vlc_logger");
            }

            _player = std::make_shared<VlcPlayer::PlayerObject>();
            _player->_instance = libvlc_new(0, nullptr);
            _player->_player = libvlc_media_player_new(_player->_instance);
        }

        VlcMemoryPlayer::~VlcMemoryPlayer() {
            // Proper resource release is handled in PlayerObject destructor
        }

        bool VlcMemoryPlayer::SetMedia(const std::string& path) 
        {
            try 
            {
                Memory::FileManagerBase manager;
                auto file = manager.OpenFile(path, std::ios_base::binary, false);
                std::vector<char> file_content((std::istreambuf_iterator<char>(*file)), std::istreambuf_iterator<char>());
                auto obj = std::make_shared<Memory::DataObject>();
                obj->SetData(std::vector<char>(file_content));
                _memory = obj;
                
                auto media = libvlc_media_new_callbacks(*this->Open, *this->Read, *this->Seek, *this->Close, static_cast<void*>(_memory.get()));

                libvlc_media_player_set_media(_player->_player, media);
                libvlc_media_player_play(_player->_player);
                return true;
            } 
            catch (const std::exception& e) 
            {
                _logger->error(e.what());
                return false;
            }
        }

        int VlcMemoryPlayer::Open(void *opaque, void **datap, uint64_t *sizep)
        {
            std::shared_lock lock(_mutex);
            auto dataPtr = static_cast<Memory::DataObject*>(opaque);
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
        ssize_t VlcMemoryPlayer::Read(void* opaque, unsigned char* buf, size_t len)
        {
            std::shared_lock lock(_mutex); 
          //  auto dataPtr = static_cast<std::shared_ptr<std::vector<std::byte>>*>(opaque);

            if (!_memory ) {

                return 0;
            }

            auto& data = *_memory; 

            size_t bytesToCopy = std::min(len, data.Size()); 
            std::memcpy(buf, data.GetData()->data(), bytesToCopy);

            return static_cast<ssize_t>(bytesToCopy);

        }

        int VlcMemoryPlayer::Seek(void *opaque, uint64_t offset)
        {
            std::shared_lock lock(_mutex);
            return 0;
        }

        void VlcMemoryPlayer::Close(void *opaque) 
        {
            // Clean up resources if needed
        }
    }
}
