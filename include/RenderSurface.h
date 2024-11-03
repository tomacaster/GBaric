#pragma once

#include <gtkmm/builder.h>
#include <gtkmm.h>
#include <gtkmm/window.h>

class RenderSurface : public Gtk::Widget
{
public:
    RenderSurface(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);
    ~RenderSurface() override;

protected:
    Glib::RefPtr<Gtk::Builder> m_builder;
};
