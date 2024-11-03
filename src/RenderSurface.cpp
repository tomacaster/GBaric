#include "RenderSurface.h"
#include <iostream>
#include <cstring>

RenderSurface::RenderSurface(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder)
    : Gtk::Widget(cobject),
      m_builder(builder)
{}

RenderSurface::~RenderSurface()
{
}