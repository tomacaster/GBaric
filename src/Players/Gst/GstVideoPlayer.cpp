#include "Players/Gst/GstVideoPlayer.h"

namespace GstPlayer = Players::GstPlayer;

namespace Players::Gst  
{
    GstVideoPlayer::GstVideoPlayer(int argc, char *argv[]) :
    GstPipeLineBase(argc, argv),
    _logger(nullptr),
    _bus(nullptr),
    _gstObj(std::make_shared<GstPlayer::GstPipelineObj>())
    {

    }

    int Players::Gst::GstVideoPlayer::PlayVideo()
    {
        return 0;
    }
} // namespace players::gst

