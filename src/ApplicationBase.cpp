#include "ApplicationBase.h"
#include "MainWindow.h"
#include <iostream>
#include <chrono>
#include <thread>
#ifdef __linux__
#include <gdk/gdkx.h>
#else
#include <gdk/win32/gdkwin32.h>
#endif
#include <gtk/gtk.h>

ApplicationBase::ApplicationBase(std::string appName) : Gtk::Application(appName)
{
auto refBuilder = Gtk::Builder::create();
    try
    {
#ifdef __linux__
        auto res = refBuilder->add_from_resource("/resources/gui.glade");
        if(!res)
        {
            std::cout << "Cannot load resources" << endl;

            return false;
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
        std::cerr << "FileError: " << ex.what() << endl;
        return false;
    }
    catch(const Glib::MarkupError& ex)
    {
        std::cerr << "MarkupError: " << ex.what() << endl;
        return false;
    }
    catch(const Gtk::BuilderError& ex)
    {
        std::cerr << "BuilderError: " << ex.what() << endl;
        return false;
    }

    refBuilder->get_widget_derived("MainWindow", windowMain);
    if(windowMain)
    {
        windowMain->signal_delete_event().connect(sigc::mem_fun(*this, &ApplicationBase::OnDestroy));    
        windowMain->playButton->signal_clicked().connect( sigc::mem_fun(*this,&ApplicationBase::OnPlayButtonPressed) ); 
        windowMain->pauseButton->signal_clicked().connect( sigc::mem_fun(*this,&ApplicationBase::OnPauseButtonPressed) ); 
        windowMain->sliderData->sliderData->signal_button_press_event().connect(sigc::mem_fun(*this,&ApplicationBase::OnSliderButtonPressed));
        windowMain->sliderData->sliderData->signal_button_release_event().connect(sigc::mem_fun(*this,&ApplicationBase::OnSliderReleased));
        windowMain->renderSurface->signal_realize().connect(sigc::mem_fun(*this, &ApplicationBase::OnCreateMain));
    }
}

Glib::RefPtr<ApplicationBase> ApplicationBase::create(std::string appName)
{
    return Glib::RefPtr<ApplicationBase>(new ApplicationBase(appName));
}

void ApplicationBase::on_startup()
{
    Gtk::Application::on_startup();
}

void ApplicationBase::on_activate()
{
}

ApplicationBase::~ApplicationBase()
{

}