#pragma once

#include <gtkmm-4.0/gtkmm.h>
#include "MainWindow.h"
#include "Players/VlcPlayer/VlcMemoryPlayer.h"
#include "Memory/Storage.h"

namespace VlcPlayer = Players::VlcPlayer;

class ApplicationBase : public Gtk::Application
{
    protected:
        ApplicationBase(std::string appName);
        static std::shared_ptr<spdlog::logger> _logger;
    private:
        std::shared_ptr<VlcPlayer::VlcMemoryPlayer> player;
        std::unique_ptr<Memory::StorageBase> _storage;
        Glib::RefPtr<Gtk::Builder> _builder;
        MainWindow *window;
        void OnSurfaceRealize();
        void onWindowRealize();
    public:
        static Glib::RefPtr<ApplicationBase> create(std::string &appName);
        
        void on_startup() override;
        void on_activate() override;
        void on_shutdown() override;
        ~ApplicationBase();
};