#pragma once

#include <vector>

#include <GL/gl.h>
#include <gtkmm/builder.h>
#include <gtkmm.h>
#include <gtkmm/window.h>
#include <gdkmm/cairocontext.h>
#include <gtkmm/glarea.h>

class RenderSurface : public Gtk::GLArea
{
public:
    RenderSurface(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);
    GdkSurface* GetHandle();
    ~RenderSurface() override;
    GLuint videoTexture;
    // Video frame data

    std::vector<uint8_t> videoFrameBuffer;
    bool frameAvailable;
    int videoWidth;
    int videoHeight;
    std::mutex frameMutex;

protected:
    Glib::RefPtr<Gtk::Builder> m_builder;
    void on_realize() override;
    void on_unrealize() override;
    bool on_render(const Glib::RefPtr<Gdk::GLContext>& context) override;
    void on_new_frame(void* pixels, int width, int height);
    // OpenGL texture

};
