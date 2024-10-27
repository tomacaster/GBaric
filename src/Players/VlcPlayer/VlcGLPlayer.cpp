#include "Players/VlcPlayer/VlcGLPlayer.h"

#include <vlc/vlc.h>

namespace Players::VlcPlayer
{
    VlcGLPlayer::VlcGLPlayer(RenderSurface& renderSurface, bool enableLogging) : VlcPlayerBase(renderSurface, enableLogging)
    {
        _logger = Logger::GetClassLogger("VlcPlayer");
        if (!_logger) 
        {
            _logger = spdlog::stdout_color_mt("vlc_logger");
        }

        _player = std::make_shared<VlcPlayer::PlayerObject>();
        _player->_instance = libvlc_new(0, nullptr);
        _player->_player = libvlc_media_player_new(_player->_instance);
        _renderSurface = &renderSurface;

        libvlc_video_engine_t engine = libvlc_video_engine_opengl;

        // Set the video output callbacks
        bool result = libvlc_video_set_output_callbacks(
            _player->_player,
            engine,
            vlc_video_setup_cb,
            vlc_video_cleanup_cb,
            nullptr, // window_cb (optional, can be nullptr)
            vlc_video_update_output_cb,
            vlc_video_swap_cb,
            vlc_video_make_current_cb,
            vlc_video_get_proc_address_cb,
            nullptr, // metadata_cb (optional, can be nullptr)
            nullptr, // select_plane_cb (optional, can be nullptr)
            _renderSurface // opaque pointer passed to callbacks
        );

        if (!result)
        {
            _logger->error("Failed to set video output callbacks");
        }
    }

    VlcGLPlayer::~VlcGLPlayer()
    {
    }

    bool VlcGLPlayer::SetMedia(const std::string &path)
    {
        auto media = libvlc_media_new_path( path.c_str());
        if (!media) {
            _logger->error("Failed to create media for path {}", path);
            return false;
        }

        libvlc_media_player_set_media(_player->_player, media);
        libvlc_media_release(media);

        int ret = libvlc_media_player_play(_player->_player);
        if (ret != 0) {
            _logger->error("libvlc_media_player_play failed with error code {}", ret);
            return false;
        }

        return true;
    }
    void VlcGLPlayer::format_cleanup(void* opaque)
    {
        // Cleanup if necessary
    }
static void* vlc_video_setup_cb(void* opaque, libvlc_video_engine_t* engine, unsigned* width, unsigned* height)
{
    RenderSurface* render_surface = static_cast<RenderSurface*>(opaque);

    // Initialize OpenGL context if necessary
    render_surface->make_current();

    // Set the desired video dimensions
    *width = render_surface->get_width();
    *height = render_surface->get_height();

    // Return a pointer to the rendering context (if needed)
    return render_surface;
}

static void vlc_video_cleanup_cb(void* opaque)
{
    RenderSurface* render_surface = static_cast<RenderSurface*>(opaque);

    // Perform any necessary cleanup
    render_surface->cleanup();
}
static void vlc_video_swap_cb(void* opaque)
{
    RenderSurface* render_surface = static_cast<RenderSurface*>(opaque);

    // Swap buffers or present the frame
    render_surface->queue_draw();
}

static bool vlc_video_make_current_cb(void* opaque, bool current)
{
    RenderSurface* render_surface = static_cast<RenderSurface*>(opaque);

    if (current)
    {
        // Make the OpenGL context current
        render_surface->make_current();
    }
    else
    {
        // Release the OpenGL context if necessary
        render_surface->release_current();
    }

    return true; // Return true on success
}

static void* vlc_video_get_proc_address_cb(void* opaque, const char* name)
{
    // Use your platform-specific function to get OpenGL function addresses
    return (void*)glXGetProcAddressARB(reinterpret_cast<const GLubyte*>(name));
}

static int vlc_video_update_output_cb(void* opaque, libvlc_video_engine_t engine, unsigned width, unsigned height)
{
    RenderSurface* render_surface = static_cast<RenderSurface*>(opaque);

    // Update the render surface dimensions
    //render_surface->set_dimensions(width, height);

    return 0; // Return 0 on success
}