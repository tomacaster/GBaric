#include "RenderSurface.h"

RenderSurface::RenderSurface(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder) : 
    Gtk::GLArea(cobject),
    m_builder(builder)
{
    Gtk::GLArea::set_required_version(3, 3);
   // set_draw_func(sigc::mem_fun(*this, &RenderSurface::OnDraw));
}

GdkSurface* RenderSurface::GetHandle()
{ 
    return this->get_native()->get_surface()->gobj();
}

RenderSurface::~RenderSurface()
{

}

void RenderSurface::OnDraw(const Cairo::RefPtr<Cairo::Context> &cr, int width, int height)
{
    // GtkWidget *widget = GTK_WIDGET(gobj());
    // GtkStyleContext *context;
    // GtkAllocation alloc;
    // cairo_t *ccr = const_cast<cairo_t*>(cr->cobj());

    // context = gtk_widget_get_style_context (widget);
    // gtk_widget_get_allocation (widget, &alloc);

    // gtk_render_background(context, ccr, 0, 0, alloc.width, alloc.height);
    // gtk_render_frame(context, ccr, 0, 0, alloc.width, alloc.height);

}
