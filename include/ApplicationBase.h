#pragma once

#include <gtkmm-4.0/gtkmm.h>
#include "vlc/vlc.h"
class ApplicationBase : public Gtk::Application
{
    protected:
        ApplicationBase(std::string appName);

    public:
        static Glib::RefPtr<ApplicationBase> create(std::string appName);
        void on_startup() override;
        void on_activate() override;
        ~ApplicationBase();
    private:


};