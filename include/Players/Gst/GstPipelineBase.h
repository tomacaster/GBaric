#pragma once

#include "Logger.h"
#include <memory>
#include <string>
#include "Players/Gst/GstPipelineObj.h"

namespace GstPlayer = Players::GstPlayer;

namespace Players
{
    namespace GstPlayer
    {
        class GstPipeLineBase
        {
            public:
                GstPipeLineBase(int argc, char *argv[]);
                ~GstPipeLineBase();
                std::shared_ptr<GstPlayer::GstPipelineObj> InitPipeline(std::string& name);
                template<typename T> bool BinAddMany(T &obj, std::vector<T> &elements);
            private:
                std::shared_ptr<spdlog::logger> _logger;
                GstElement *_bus;
                std::shared_ptr<GstPlayer::GstPipelineObj> _gstObj;
        };
    }
}