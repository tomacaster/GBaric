#include "MainWindow.h"

MainWindow::MainWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder)
: Gtk::ApplicationWindow(cobject),
  m_builder(builder)
{
    set_title("Przykładowe okno GTKMM");
    set_default_size(200, 200);
}


MainWindow::~MainWindow()
{
}
