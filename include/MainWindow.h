#pragma once
#include <gtkmm-4.0/gtkmm.h>
#include "Logger.h"
#include <gtkmm/applicationwindow.h>
#include <gtkmm/button.h>
#include <gtkmm/box.h>
#include <gtkmm/menubutton.h>
#include <gtkmm/builder.h>
#include <gtkmm/scale.h>
#include <gtkmm/grid.h>
#include "RenderSurface.h"

class MainWindow : public Gtk::ApplicationWindow 
{
    public:
        MainWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);
        Glib::RefPtr<RenderSurface> getSurface() { return surface; }
        virtual ~MainWindow();
    private:
        Glib::RefPtr<Gtk::Builder> _builder;
        Glib::RefPtr<Gtk::Box> box;
        Glib::RefPtr<Gtk::MenuButton> _menuButton;
        Glib::RefPtr<RenderSurface> surface;
        Glib::RefPtr<Gtk::Grid> grid;
        Glib::RefPtr<Gtk::Button> playButton;
        Glib::RefPtr<Gtk::Button> pauseButton;
        Glib::RefPtr<Gtk::Scale> scale;
    protected: 
       // static std::shared_ptr<spdlog::logger> _logger;

};