#include "MainWindow.h"
#include <iostream>

MainWindow::MainWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder) : 
    Gtk::ApplicationWindow(cobject),
    m_builder(builder),
    box(m_builder->get_widget<Gtk::Box>("Box")),
    surface(Gtk::Builder::get_widget_derived<RenderSurface>(m_builder, "RenderSurface")),
    grid(m_builder->get_widget<Gtk::Grid>("Grid")),
    playButton(m_builder->get_widget<Gtk::Button>("PlayButton")),
    pauseButton(m_builder->get_widget<Gtk::Button>("PauseButton")),
    scale(m_builder->get_widget<Gtk::Scale>("ProgressBar"))
{
    set_title("ldasdsa");
    if(box) {} else std::cerr << "Cannot box" << std::endl;
    if(surface) {} else std::cerr << "Cannot surface" << std::endl;
    if(grid) {} else std::cerr << "Cannot grid" << std::endl;
    if(playButton) {} else std::cerr << "Cannot playButton" << std::endl;
    if(pauseButton) {} else std::cerr << "Cannot pauseButton" << std::endl;
    if(scale) {} else std::cerr << "Cannot scale" << std::endl;
}


MainWindow::~MainWindow()
{
}
