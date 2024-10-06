#include "Players/Gst/GstPipelineBase.h"
#include <gst/gst.h>

namespace Players::GstPlayer
{
    GstPipeLineBase::GstPipeLineBase(int argc, char * argv[]) :
    _logger(nullptr),
    _gstObj(nullptr)
    {
        _logger = Logger::GetClassLogger("GstPipeLineBase");

        if(!gst_is_initialized())
        {
            GError *error;

            auto res = gst_init_check(&argc, &argv, &error);
            if(!res)
            {
                _logger->critical("Cannot init GStreamer pipeline: {}", error->message);
            }
        }

    }

    template<typename T> bool GstPipeLineBase::BinAddMany(T &obj, std::vector<T> &elements)
    {
        for(auto item : elements)
        {
            bool res = gst_bin_add(GST_BIN(_gstObj->GetPipeline()), item);
            
            if(!res)
            {
                _logger->error("Cannot add element to bin");

                return false;
            }
        }

        return gst_bin_add(GST_BIN(_gstObj->GetPipeline()), NULL);
    } 

    GstPipeLineBase::~GstPipeLineBase()
    {

    }
    std::shared_ptr<GstPlayer::GstPipelineObj> GstPipeLineBase::InitPipeline(std::string& name)
    {
        return std::shared_ptr<GstPlayer::GstPipelineObj>();
    }
}
