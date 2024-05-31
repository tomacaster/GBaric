#include "Players/Gst/GstPipelineBase.h"
#include <gst/gst.h>


Players::GstPlayer::GstPipeLineBase::GstPipeLineBase(int argc, char * argv[])
{
    gst_init(&argc, &argv);
}