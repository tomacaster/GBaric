#pragma once

#include <memory>
#include "Players/Gst/GstPipelineObj.h"

namespace Players
{
    namespace GstPlayer
    {
        class GstPipeLineBase
        {
            public:
                GstPipeLineBase(int argc, char *argv[]);
            private:
                std::shared_ptr<Players::GstPlayer::GstPipelineObj> _gstObj;
        };
    }
}