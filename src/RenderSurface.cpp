#include "RenderSurface.h"

RenderSurface::RenderSurface(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder) : 
    Gtk::DrawingArea(cobject),
    m_builder(builder)
{
    
}

RenderSurface::~RenderSurface()
{

}