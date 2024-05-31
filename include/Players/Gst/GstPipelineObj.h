#pragma once

#include <gst/gst.h>

namespace Players
{
    namespace GstPlayer
    {
        class GstPipelineObj
        {
            public:
                GstPipelineObj();
                ~GstPipelineObj();
            private:
                GstElement *pipeline, *source, *sink;
                GstBus *bus;
                GstMessage *msg;
                GstStateChangeReturn ret;
        };
    }
}