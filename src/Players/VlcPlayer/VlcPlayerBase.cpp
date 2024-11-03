#include "Players/VlcPlayer/VlcPlayerBase.h"
#ifdef __linux__
#include <gdk/x11/gdkx.h>
#else
#include <gdk/win32/gdkwin32.h>
#endif
#include <iostream>

namespace Players
{
    namespace VlcPlayer
    {
        VlcPlayerBase::VlcPlayerBase(RenderSurface& surface, bool enableVlcLogging) :
            _logger(spdlog::get("vlc_logger")),
            _logging(enableVlcLogging),
            _renderSurface(&surface),
            _player(std::make_shared<PlayerObject>())
        {
            if (_logging && !_logger) 
            {
                _logger = spdlog::stdout_color_mt("vlc_logger");
            }
        }

        bool VlcPlayerBase::SetSurface()
        {
            if (_player->_instance == nullptr) {
                std::cerr << "You should create player first" << std::endl;
                return false;
            }

// #ifdef __linux__
//             auto handle = GDK_SURFACE_XID(_renderSurface->GetHandle());
//             libvlc_media_player_set_xwindow(_player->_player, handle);
// #else
//             auto handle = (GTK_WINDOW_HANDLE(_renderSurface->GetHandle()));
//             libvlc_media_player_set_hwnd(_player->_player, handle);
// #endif
//             _logger->info("Player created");
            return true;
        }

        void VlcPlayerBase::LogCb(int size, const libvlc_log_t* logT, const std::string& message)
        {
            _logger->debug(message);
        }
    }
}
