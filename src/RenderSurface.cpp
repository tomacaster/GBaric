#include "RenderSurface.h"

RenderSurface::RenderSurface(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder) : 
    Gtk::DrawingArea(cobject),
    m_builder(builder)
{
    set_draw_func(sigc::mem_fun(*this, &RenderSurface::OnDraw));
}

RenderSurface::~RenderSurface()
{

}

void RenderSurface::OnDraw(const Cairo::RefPtr<Cairo::Context> &cr, int width, int height)
{

}
