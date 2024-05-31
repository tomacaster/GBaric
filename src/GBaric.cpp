#include <string>
#include <chrono>
#include <thread>
#include <string>
#include "Players/Gst/GstPipelineBase.h"
#include "Logger.h"
#include "ApplicationBase.h"
#include "MainWindow.h"
#include "Memory/Storage.h"
#include "Memory/DataObject.h"
#include "Memory/DBEngineBase.h"

std::string appName { "iotoys.gbaric.player" };

int main(int argc, char *argv[])
{
    auto g = Players::GstPlayer::GstPipeLineBase(argc, argv);
//   GstElement *pipeline;
//   GstBus* gstBus;
//   GstMessage* msg;
//   gst_init(&argc, &argv);

//   pipeline = gst_parse_launch("playbin uri=https://gstreamer.freedesktop.org/data/media/sintel_trailer-480p.webm",
//       NULL);

//       gst_element_set_state(pipeline, GST_STATE_PLAYING);
//   gstBus = gst_element_get_bus(pipeline);
//   msg = gst_bus_timed_pop_filtered (gstBus, GST_CLOCK_TIME_NONE,
//       GST_MESSAGE_EOS);

//   if (GST_MESSAGE_TYPE (msg) == GST_MESSAGE_ERROR) {
//     g_error ("An error occurred! Re-run with the GST_DEBUG=*:WARN environment "
//         "variable set for more details.");
//   }

//   gst_message_unref (msg);
//   gst_object_unref (gstBus);
//   gst_element_set_state (pipeline, GST_STATE_NULL);
//   gst_object_unref (pipeline);
  auto homedir = Memory::StorageBase::InitStorage(appName);
  // auto db = DBEngineBase(homedir + "/Data/db.db3");
  // db.CreateTable("Playlist", "ID INTEGER PRIMARY KEY AUTOINCREMENT,""Nazwa TEXT NOT NULL,""Plik TEXT NOT NULL");
	auto app = ApplicationBase::create(appName);

	return app->run(0, nullptr);
}