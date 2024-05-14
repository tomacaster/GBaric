#pragma once

#include <gtkmm/builder.h>
#include <gtkmm.h>
#include "gtkmm/drawingarea.h"
#include <gtkmm/window.h>
#include <gdkmm/cairocontext.h>
#include <gtkmm/video.h>

class RenderSurface : public Gtk::Video
{
    public:
        RenderSurface(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);
        GdkSurface* GetHandle();
        ~RenderSurface();
    protected:
        Glib::RefPtr<Gtk::Builder> m_builder;
        void OnDraw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height);
};