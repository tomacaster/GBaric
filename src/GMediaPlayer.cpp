#include "GMediaPlayer.h"

std::unique_ptr<Logger> GMediaPlayer::_logger {nullptr};

GMediaPlayer::GMediaPlayer()
{
    
}

bool GMediaPlayer::SetSurface(std::shared_ptr<RenderSurface> renderSurface)
{
    return false;
}

bool GMediaPlayer::SetMedia(std::string path)
{
    Glib::RefPtr<Gio::File> file;


    return false;
}

bool GMediaPlayer::Play()
{
    return false;
}

bool GMediaPlayer::Pause()
{
    return false;
}

bool GMediaPlayer::Stop()
{
    return false;
}

bool GMediaPlayer::Rewind()
{
    return false;
}

bool GMediaPlayer::SetLoop()
{
    return false;
}
