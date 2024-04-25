#include "ApplicationBase.h"

#include <iostream>
#include <chrono>
#include <thread>

std::shared_ptr<spdlog::logger> ApplicationBase::_logger {nullptr};

ApplicationBase::ApplicationBase(std::string appName) : 
    Gtk::Application(appName), 
    player(std::make_shared<VlcPlayer>(false))
{}

void ApplicationBase::OnSurfaceRealize()
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
        _logger = Logger::GetClassLogger("AppBase");
        auto res = Gio::Resource::create_from_file("resources/resources.gresource");
        res->register_global();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return Glib::RefPtr<ApplicationBase>();
        _logger->error(e.what());
    }
    

    return Glib::RefPtr<ApplicationBase>(new ApplicationBase(appName));
}

void ApplicationBase::on_startup()
{
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
    window->getSurface()->signal_realize().connect(sigc::mem_fun(*this, &ApplicationBase::OnSurfaceRealize));
    window->set_size_request(800, 600);

    add_window(*window);
    window->show();
}

void ApplicationBase::on_shutdown()
{
}

ApplicationBase::~ApplicationBase()
{

}