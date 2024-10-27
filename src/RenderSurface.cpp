#include "RenderSurface.h"
#include <iostream>
#include <cstring>

RenderSurface::RenderSurface(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder)
    : Gtk::GLArea(cobject),
      m_builder(builder),
      videoTexture(0),
      frameAvailable(false)
{
    set_required_version(3, 3);
    set_has_depth_buffer(false);
    signal_render().connect(sigc::mem_fun(*this, &RenderSurface::on_render), false);
}

GdkSurface* RenderSurface::GetHandle()
{
    return this->get_native()->get_surface()->gobj();
}

RenderSurface::~RenderSurface()
{

}

void RenderSurface::on_new_frame(void* pixels, int width, int height)
{
    std::lock_guard<std::mutex> lock(frameMutex);

    // Skopiuj dane ramki
    size_t frame_size = width * height * 4;
    videoFrameBuffer.resize(frame_size);
    std::memcpy(videoFrameBuffer.data(), pixels, frame_size);

    videoWidth = width;
    videoHeight = height;
    frameAvailable = true;
}


bool RenderSurface::on_render(const Glib::RefPtr<Gdk::GLContext>& context)
{
    std::lock_guard<std::mutex> lock(frameMutex);

    if (frameAvailable)
    {
        glBindTexture(GL_TEXTURE_2D, videoTexture);

        if (videoWidth != texWidth || videoHeight != texHeight)
        {
            texWidth = videoWidth;
            texHeight = videoHeight;
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texWidth, texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, videoFrameBuffer.data());
        }
        else
        {
            glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, texWidth, texHeight, GL_RGBA, GL_UNSIGNED_BYTE, videoFrameBuffer.data());
        }

        frameAvailable = false;
    }

    // Renderowanie tekstury
    // ... (Twoje kod renderowania OpenGL)

    return true;
}
