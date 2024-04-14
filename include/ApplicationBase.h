#pragma once

#include <gtkmm-4.0/gtkmm.h>
#include "Logger.h"
#include "MainWindow.h"
#include "RenderSurface.h"
#include "VlcPlayer.h"

class ApplicationBase : public Gtk::Application
{
    protected:
        ApplicationBase(std::string appName);
       // static std::shared_ptr<spdlog::logger> _logger;
    private:
        std::shared_ptr<VlcPlayer> player;
        Glib::RefPtr<Gtk::Builder> _builder;
        MainWindow *window;
        void onSurfaceRealize();
        void onWindowRealize();
    public:
        static Glib::RefPtr<ApplicationBase> create(std::string appName);
        
        void on_startup() override;
        void on_activate() override;

        ~ApplicationBase();




};