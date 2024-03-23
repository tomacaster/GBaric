#pragma once

#include <gtkmm/builder.h>
#include "gtkmm/drawingarea.h"

class RenderSurface : public Gtk::DrawingArea
{
public:
    RenderSurface(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);
    ~RenderSurface();
    protected:
        Glib::RefPtr<Gtk::Builder> m_builder;
};