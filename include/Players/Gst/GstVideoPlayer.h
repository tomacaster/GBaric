#pragma once

#include "Players/Gst/GstPipelineBase.h"

namespace Players::Gst 
{
	class GstVideoPlayer : Players::GstPlayer::GstPipeLineBase
	{
		public:
			GstVideoPlayer(int argc, char *argv[]);
			int PlayVideo();
			template<typename T> void AddMany(T &obj, std::vector<T> &elements);

		private:
			std::shared_ptr<spdlog::logger> _logger;
			GstElement *_bus;
			std::shared_ptr<GstPlayer::GstPipelineObj> _gstObj;
	};
} // namespace players::gst
