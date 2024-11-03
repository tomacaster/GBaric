#include "Players/Gst/GstPipelineObj.h"

namespace Players :: GstPlayer
{
    Players::GstPlayer::GstPipelineObj::GstPipelineObj() :
        _bin(nullptr),
        _pipeline(nullptr),
        _bus(nullptr),
        _msg(nullptr)
    {}
    GstPipelineObj::~GstPipelineObj() { }

    void GstPlayer::GstPipelineObj::SetPipeline(GstElement *pipeline)
    {
        _pipeline = std::shared_ptr<GstElement>(pipeline, gst_object_unref);
        gst_object_ref(pipeline);
    }

    void GstPipelineObj::AddSink(GstElement *sink)
    {
        _sinks.push_back(std::shared_ptr<GstElement>(sink, gst_object_unref));
    }

    void GstPlayer::GstPipelineObj::AddSource(GstElement *source)
    {
        _sources.push_back(std::shared_ptr<GstElement>(source, gst_object_unref));
    }    
}

