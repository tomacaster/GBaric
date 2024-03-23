#pragma once

#include <gtkmm/builder.h>
#include "gtkmm/drawingarea.h"
#include <gtkmm/window.h>

class RenderSurface : public Gtk::DrawingArea
{
public:
    RenderSurface(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);
    GdkSurface* GetHandle() { return this->get_native()->get_surface()->gobj(); };
    ~RenderSurface();
    protected:
        Glib::RefPtr<Gtk::Builder> m_builder;
};