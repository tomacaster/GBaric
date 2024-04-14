#include "ApplicationBase.h"

#include <iostream>
#include <chrono>
#include <thread>


ApplicationBase::ApplicationBase(std::string appName) : 
    Gtk::Application(appName), 
    player(std::make_shared<VlcPlayer>(false))
{}

void ApplicationBase::onSurfaceRealize()
{
    player->SetSurface(window->getSurface());
    player->SetMedia("/home/michal/Documents/video.mp4");
}

void ApplicationBase::onWindowRealize()
{

}

Glib::RefPtr<ApplicationBase> ApplicationBase::create(std::string appName)
{
    try
    {
        auto res = Gio::Resource::create_from_file("resources/resources.gresource");
        res->register_global();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;

      //  _logger->error(e.what());
    }
    

    return Glib::RefPtr<ApplicationBase>(new ApplicationBase(appName));
}

void ApplicationBase::on_startup()
{
        // mainWindow =  Glib::RefPtr<MainWindow>(Gtk::Builder::get_widget_derived<MainWindow>(refBuilder, Glib::ustring("MainWindow")));
    // if(mainWindow)
    // {
        
    //    // mainWindow->show();
    //     // mainWindow->signal_delete_event().connect(sigc::mem_fun(*this, &ApplicationBase::OnDestroy));    
    //     // mainWindow->playButton->signal_clicked().connect( sigc::mem_fun(*this,&ApplicationBase::OnPlayButtonPressed) ); 
    //     // mainWindow->pauseButton->signal_clicked().connect( sigc::mem_fun(*this,&ApplicationBase::OnPauseButtonPressed) ); 
    //     // mainWindow->sliderData->sliderData->signal_button_press_event().connect(sigc::mem_fun(*this,&ApplicationBase::OnSliderButtonPressed));
    //     // mainWindow->sliderData->sliderData->signal_button_release_event().connect(sigc::mem_fun(*this,&ApplicationBase::OnSliderReleased));
    //     // mainWindow->renderSurface->signal_realize().connect(sigc::mem_fun(*this, &ApplicationBase::OnCreateMain));
    // }
    Gtk::Application::on_startup();
}

void ApplicationBase::on_activate()
{
    try
    {
        _builder = Gtk::Builder::create();
      //  _logger = Logger::GetLogger();
#ifdef __linux__

        auto res = _builder->add_from_resource("/resources/gui.glade"); //("resources/gui.glade");
        if(!res)
        {
            std::cout << "Cannot load resources" << std::endl;

           // return false;
        }  
#else
        auto res = _builder->add_from_file("resources\\gui.glade");
        if(!res)
        {
            std::cout << "Cannot load resources" << std::endl;

          //  return false;
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
    catch(const std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
    }

    window = Gtk::Builder::get_widget_derived<MainWindow>(_builder, Glib::ustring("MainWindow"));
    window->signal_realize().connect(sigc::mem_fun(*this, &ApplicationBase::onWindowRealize));
    window->getSurface()->signal_realize().connect(sigc::mem_fun(*this, &ApplicationBase::onSurfaceRealize));
    window->set_size_request(800, 600);
    add_window(*window);
    window->show();

}

ApplicationBase::~ApplicationBase()
{

}