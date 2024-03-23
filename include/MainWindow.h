#pragma once
#include <gtkmm/applicationwindow.h>
#include <gtkmm/builder.h>

class MainWindow : public Gtk::ApplicationWindow 
{
    public:
        MainWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);
        virtual ~MainWindow();
    private:
        Glib::RefPtr<Gtk::Builder> m_builder;

};