#include "Players/Gst/GstVideoPlayer.h"

namespace Players::Gst  
{
    GstVideoPlayer::GstVideoPlayer(int argc, char *argv[]) {
        logger_ = Logger::GetClassLogger("GstVideoPlayer");
        GError* error = nullptr;
        auto res = gst_init_check(&argc, &argv, &error);

        if(!res) {
            logger_->critical("Cannot initialize GST: {}: {}", error->code, error->message);
            g_clear_error(&error);
            throw std::runtime_error("Cannot initialize GST");
        }

        Init();
    }

    GstVideoPlayer::~GstVideoPlayer()
    {
        Release();
    }

    void GstVideoPlayer::Init()
    {
        currentMedia_.duration = GST_CLOCK_TIME_NONE;
        currentMedia_.playbin = MakeGstElement("playbin", "playbin");

        videoSink_ = MakeGstElement("glsinkbin", "video_sink");
        gtkGlSink_ = MakeGstElement("gtkglsink", "gtk_gl_sink");

        if(gtkGlSink_ && videoSink_) {
            logger_->debug("Sinks created.");

            g_object_set(videoSink_.get(), "sink", gtkGlSink_.get(), nullptr);
            g_object_set(currentMedia_.playbin.get(), "video-sink", videoSink_.get(), nullptr);

            GtkWidget* widget = nullptr;
            g_object_get(gtkGlSink_.get(), "widget", &widget, nullptr);
            
            if (widget) {
                currentMedia_.sinkWidget = std::shared_ptr<GtkWidget>(widget, [](GtkWidget* w) {
                    if (w) {
                        g_object_unref(w);
                    }
                });
            }
        }

        // Ustawienie busa do obsługi komunikatów GStreamer
        gstBus_ = std::shared_ptr<GstBus>(gst_element_get_bus(currentMedia_.playbin.get()), gst_object_unref);
    }

    const GstVideoPlayer::MediaContext& GstVideoPlayer::GetContext()
    {
        return currentMedia_;
    }

    bool GstVideoPlayer::Play()
    {
        if (currentMedia_.playbin) {
            GstStateChangeReturn ret = gst_element_set_state(currentMedia_.playbin.get(), GST_STATE_PLAYING);
            if (ret == GST_STATE_CHANGE_FAILURE) {
                logger_->error("Unable to set the pipeline to the playing state.");
                return false;
            }
            currentMedia_.state = GST_STATE_PLAYING;
            return true;
        }
        return false;
    }

    bool GstVideoPlayer::Pause()
    {
        if (currentMedia_.playbin) {
            GstStateChangeReturn ret = gst_element_set_state(currentMedia_.playbin.get(), GST_STATE_PAUSED);
            if (ret == GST_STATE_CHANGE_FAILURE) {
                logger_->error("Unable to set the pipeline to the paused state.");
                return false;
            }
            currentMedia_.state = GST_STATE_PAUSED;
            return true;
        }
        return false;
    }

    bool GstVideoPlayer::Stop(bool rewind)
    {
        if (currentMedia_.playbin) {
            GstStateChangeReturn ret = gst_element_set_state(currentMedia_.playbin.get(), GST_STATE_READY);
            if (ret == GST_STATE_CHANGE_FAILURE) {
                logger_->error("Unable to set the pipeline to the ready state.");
                return false;
            }
            currentMedia_.state = GST_STATE_READY;
            if (rewind) {
                return Rewind();
            }
            return true;
        }
        return false;
    }

    bool GstVideoPlayer::Rewind()
    {
        return Seek(std::chrono::milliseconds(0));
    }

    bool GstVideoPlayer::Seek(std::chrono::milliseconds position)
    {
        if (currentMedia_.playbin) {
            gboolean success = gst_element_seek_simple(
                currentMedia_.playbin.get(),
                GST_FORMAT_TIME,
                (GstSeekFlags)(GST_SEEK_FLAG_FLUSH | GST_SEEK_FLAG_KEY_UNIT),
                position.count() * GST_MSECOND
            );
            if (!success) {
                logger_->error("Seek failed.");
                return false;
            }
            return true;
        }
        return false;
    }

    bool GstVideoPlayer::Load(const Memory::Storage::FileCommon &file)
    {
        if (currentMedia_.playbin) {
            std::string uri = std::string(file.GetPath());
            g_object_set(currentMedia_.playbin.get(), "uri", uri.c_str(), nullptr);
            g_object_set (currentMedia_.playbin.get(), "video-sink", videoSink_.get(), NULL);

            return true;
        }

        return false;
    }

    std::chrono::milliseconds GstVideoPlayer::GetDuration()
    {
        if (currentMedia_.playbin) {
            gint64 duration = GST_CLOCK_TIME_NONE;
            if (gst_element_query_duration(currentMedia_.playbin.get(), GST_FORMAT_TIME, &duration)) {
                return std::chrono::milliseconds(duration / GST_MSECOND);
            }
        }

        return std::chrono::milliseconds(0);
    }

    std::chrono::milliseconds GstVideoPlayer::GetTime()
    {
        if (currentMedia_.playbin) {
            gint64 position = GST_CLOCK_TIME_NONE;
            if (gst_element_query_position(currentMedia_.playbin.get(), GST_FORMAT_TIME, &position)) {
                return std::chrono::milliseconds(position / GST_MSECOND);
            }
        }

        return std::chrono::milliseconds(0);
    }

    bool GstVideoPlayer::IsPlaying()
    {
        if (currentMedia_.playbin) {
            GstState state;
            GstState pending;
            gst_element_get_state(currentMedia_.playbin.get(), &state, &pending, GST_CLOCK_TIME_NONE);

            return (state == GST_STATE_PLAYING);
        }

        return false;
    }

    bool GstVideoPlayer::CanPlay()
    {
        return currentMedia_.playbin != nullptr;
    }

    bool GstVideoPlayer::Release()
    {
        if (currentMedia_.playbin) {
            gst_element_set_state(currentMedia_.playbin.get(), GST_STATE_NULL);
            currentMedia_.playbin.reset();
            gtkGlSink_.reset();
            videoSink_.reset();
            currentMedia_.sinkWidget.reset();

            return true;
        }
        
        return false;
    }

    std::shared_ptr<GstElement> GstVideoPlayer::MakeGstElement(const char *factory_name, const char *element_name){
        GstElement* elem = gst_element_factory_make(factory_name, element_name);

        if (!elem) {
            logger_->error("Failed to create element {}:{}", factory_name, element_name);
            return nullptr;
        }
        return std::shared_ptr<GstElement>(elem, [](GstElement* e) {
            if (e) {
                gst_object_unref(e);
            }
        });
    }
} // namespace Players::Gst
