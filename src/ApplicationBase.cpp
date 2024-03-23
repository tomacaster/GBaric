#include "ApplicationBase.h"

#include <iostream>
#include <chrono>
#include <thread>
#ifdef __linux__
#include <gdk/x11/gdkx.h>
#else
#include <gdk/win32/gdkwin32.h>
#endif
#include <gtk/gtk.h>

ApplicationBase::ApplicationBase(std::string appName) : Gtk::Application(appName), refBuilder(Gtk::Builder::create()), mainWindow(nullptr)
{
    try
    {
#ifdef __linux__
        auto res = refBuilder->add_from_file("resources/gui.glade");
        if(!res)
        {
            std::cout << "Cannot load resources" << std::endl;

           // return false;
        }  
#else
        auto res = refBuilder->add_from_file("resources\\gui.glade");
        if(!res)
        {
            std::cout << "Cannot load resources" << endl;

            return false;
        } 
#endif    
    }
    catch(const Glib::FileError& ex)
    {
        std::cerr << "FileError: " << ex.what() << std::endl;
        // return Glib::RefPtr<ApplicationBase>();
    }
    catch(const Glib::MarkupError& ex)
    {
        std::cerr << "MarkupError: " << ex.what() << std::endl;
        // return Glib::RefPtr<ApplicationBase>();
    }
    catch(const Gtk::BuilderError& ex)
    {
        std::cerr << "BuilderError: " << ex.what() << std::endl;
        // return Glib::RefPtr<ApplicationBase>();
    }

   
}

Glib::RefPtr<ApplicationBase> ApplicationBase::create(std::string appName)
{
    return Glib::RefPtr<ApplicationBase>(new ApplicationBase(appName));
}

void ApplicationBase::on_startup()
{


    auto win =  Gtk::Builder::get_widget_derived<MainWindow>(refBuilder, Glib::ustring("MainWindow"));
    if(win)
    {
        win->show();
        // mainWindow->signal_delete_event().connect(sigc::mem_fun(*this, &ApplicationBase::OnDestroy));    
        // mainWindow->playButton->signal_clicked().connect( sigc::mem_fun(*this,&ApplicationBase::OnPlayButtonPressed) ); 
        // mainWindow->pauseButton->signal_clicked().connect( sigc::mem_fun(*this,&ApplicationBase::OnPauseButtonPressed) ); 
        // mainWindow->sliderData->sliderData->signal_button_press_event().connect(sigc::mem_fun(*this,&ApplicationBase::OnSliderButtonPressed));
        // mainWindow->sliderData->sliderData->signal_button_release_event().connect(sigc::mem_fun(*this,&ApplicationBase::OnSliderReleased));
        // mainWindow->renderSurface->signal_realize().connect(sigc::mem_fun(*this, &ApplicationBase::OnCreateMain));
    }

    Gtk::Application::on_startup();
}

void ApplicationBase::on_activate()
{
}

ApplicationBase::~ApplicationBase()
{

}