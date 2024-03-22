#include "ApplicationBase.h"
#include "MainWindow.h"

ApplicationBase::ApplicationBase(std::string appName) : Gtk::Application(appName)
{

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