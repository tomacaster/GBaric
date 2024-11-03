#pragma once

#include <chrono>

#include <gtkmm.h>
#include <glibmm.h>
#include <gst/gst.h>

#include "Players/PlayerController.h"
#include "Players/PlayerCommon.h"
#include "Storage/FileCommon.h"

namespace Players::Gst 
{
	using OnTimeChangeEventPtr = void(*)(int);	
	
	class GstVideoPlayer : Players::PlayerController
	{
		public:
		    struct MediaContext {
				std::shared_ptr<GtkWidget> sinkWidget;
				std::shared_ptr<GstElement> playbin { nullptr };           /* Our one and only pipeline */
				gulong sliderUpdateSignalId; /* Signal ID for the slider update signal */
				GstState state;                 /* Current state of the pipeline */
				gint64 duration;  
    		};

			GstVideoPlayer(int argc, char *argv[]);
			~GstVideoPlayer();

			void Init() override;
			const MediaContext& GetContext();

			bool Play() override;
			bool Pause() override;
			bool Stop(bool rewind = false) override;
			bool Rewind() override;
			bool Seek(std::chrono::milliseconds position) override;
			bool Load(const Memory::Storage::FileCommon& file) override;
			std::chrono::milliseconds GetDuration() override;
			std::chrono::milliseconds GetTime() override;
			bool IsPlaying() override;
			bool CanPlay() override;
			bool Release() override;
		private:
			std::shared_ptr<spdlog::logger> logger_ { nullptr };
			MediaContext currentMedia_;
			std::shared_ptr<GstBus> gstBus_ { nullptr };
			std::shared_ptr<GstElement> gtkGlSink_ { nullptr };
			std::shared_ptr<GstElement> videoSink_ { nullptr };
			std::shared_ptr<GstElement> MakeGstElement(const char* factory_name, const char* element_name);
	};
} // namespace players::gst