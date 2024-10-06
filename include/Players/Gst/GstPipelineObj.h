#pragma once

#include <memory>
#include <vector>
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
                void SetPipeline(GstElement *pipeline);
                template<typename T> bool AddMany(T &dst, std::vector<T> &elements);
                void AddSink(GstElement *sink);
                void AddSource(GstElement * source);
                GstElement *GetPipeline();
            private:  
                std::shared_ptr<GstElement> _bin;
                std::shared_ptr<GstElement> _pipeline;
                std::vector<std::shared_ptr<GstElement>> _sources;
                std::vector<std::shared_ptr<GstElement>> _sinks;
                std::shared_ptr<GstBus> _bus;
                std::shared_ptr<GstMessage> _msg;
                GstStateChangeReturn _ret;
        };
    }
}