#pragma once

#include <gtkmm-4.0/gtkmm.h>
#include "MainWindow.h"
#include "RenderSurface.h"
#include "VlcPlayer.h"

class ApplicationBase : public Gtk::Application
{
    protected:
        ApplicationBase(std::string appName);
    private:
        Glib::RefPtr<MainWindow> mainWindow;
        Glib::RefPtr<Gtk::Builder> refBuilder;
        std::shared_ptr<VlcPlayer> player;
    public:
        static Glib::RefPtr<ApplicationBase> create(std::string appName);
        
        void on_startup() override;
        void on_activate() override;
        std::shared_ptr<RenderSurface> getSurface() { return mainWindow->getSurface(); }
        ~ApplicationBase();




};