#include "MainWindow.h"
#ifdef __linux__
#include <gdk/x11/gdkx.h>
#else
#include <gdk/win32/gdkwin32.h>
#endif
#include <gtk/gtk.h>
#include <iostream>

MainWindow::MainWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder) :  Gtk::ApplicationWindow(cobject), _builder(builder)
{
    set_title("GBaric");
    
    box = std::shared_ptr<Gtk::Box>(_builder->get_widget<Gtk::Box>("Box"));
    if(box) {} else std::cerr << "Cannot box" << std::endl;

    // _menuButton = std::shared_ptr<Gtk::MenuButton>(_builder->get_widget<Gtk::MenuButton>("MenuButton"));
    // if(_menuButton) {
    // }
    surface = std::shared_ptr<RenderSurface>(Gtk::Builder::get_widget_derived<RenderSurface>(_builder, "RenderSurface"));
    if(surface) {} else std::cerr << "Cannot surface" << std::endl;
    scale = std::shared_ptr<Gtk::Scale>(_builder->get_widget<Gtk::Scale>("ProgressBar"));
    if(scale) {} else std::cerr << "Cannot scale" << std::endl;
    grid = std::shared_ptr<Gtk::Grid>(_builder->get_widget<Gtk::Grid>("Grid"));
    if(grid) {} else std::cerr << "Cannot grid" << std::endl;
    
    playButton = std::shared_ptr<Gtk::Button>(_builder->get_widget<Gtk::Button>("PlayButton"));
    if(playButton) {} else std::cerr << "Cannot playButton" << std::endl;
    pauseButton = std::shared_ptr<Gtk::Button>(_builder->get_widget<Gtk::Button>("PauseButton"));
    if(pauseButton) {} else std::cerr << "Cannot pauseButton" << std::endl;

}

MainWindow::~MainWindow()
{
}