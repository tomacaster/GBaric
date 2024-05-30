#pragma once
#include "Logger.h"
#include <gtkmm-4.0/gtkmm.h>
#include <gtkmm-4.0/gtkmm/mediastream.h>
#include <gtkmm-4.0/gtkmm/mediafile.h>

#include "IVideoPlayer.h"

class GMediaPlayer : IVideoPlayer
{
    public:
        GMediaPlayer();
        bool SetSurface(std::shared_ptr<RenderSurface> renderSurface) override;
        bool SetMedia(std::string path) override;
        bool Play() override;
        bool Pause() override;
        bool Stop() override;
        bool Rewind() override;
        bool SetLoop() override;
    private:
        static std::unique_ptr<Logger> _logger;
        Glib::RefPtr<Gtk::MediaFile> _mediaFile;
        Glib::RefPtr<Gtk::MediaStream> _mediaStream;

};