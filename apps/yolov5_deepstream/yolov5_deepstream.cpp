#include <iostream>
#include <gst/gst.h>
#include <glib.h>
#include <stdio.h>
#include "gstnvdsmeta.h"
#include "nvds_yml_parser.h"
#include "common/create_source.hpp"
#include "config/config.hpp"
#include "common/create_primary_gie.hpp"
#include "common/create_osd.hpp"
#include "common/create_tiler.hpp"
#include "common/create_sink.hpp"
#define CONFIG "apps/yolov5_deepstream/config.json"


static gboolean bus_call (GstBus * bus, GstMessage * msg, gpointer data) {
  GMainLoop *loop = (GMainLoop *) data;
  switch (GST_MESSAGE_TYPE (msg)) {
    case GST_MESSAGE_EOS:
      g_print ("End of stream\n");
      g_main_loop_quit (loop);
      break;
    case GST_MESSAGE_ERROR:{
      gchar *debug;
      GError *error;
      gst_message_parse_error (msg, &error, &debug);
      g_printerr ("ERROR from element %s: %s\n",
          GST_OBJECT_NAME (msg->src), error->message);
      if (debug)
        g_printerr ("Error details: %s\n", debug);
      g_free (debug);
      g_error_free (error);
      g_main_loop_quit (loop);
      break;
    }
    default:
      break;
  }
  return TRUE;
}

int main (int argc, char *argv[])
{  
  gst_init (NULL, NULL);
  Config::Instance()->Initialize(CONFIG);
  auto all_config = Config::Instance()->GetAllConfig();


  auto pipeline = gst_pipeline_new ("pipeline");

  auto source = Source::Create();
  auto detection = PrimaryGie::Create("person_detection");
  auto osd = OSD::Create();
  auto tiler = Tiler::Create();
  auto sink = Sink::Create(0);

  gst_bin_add_many(GST_BIN (pipeline), source, osd, tiler, sink, NULL);
  gst_element_link_many(source, osd, tiler, sink, NULL);

  GMainLoop *loop = g_main_loop_new (NULL, FALSE);
  auto bus = gst_pipeline_get_bus (GST_PIPELINE (pipeline));
  auto bus_watch_id = gst_bus_add_watch (bus, bus_call, loop);
  gst_object_unref (bus);

  gst_element_set_state (pipeline, GST_STATE_PLAYING);
  g_main_loop_run (loop);
  
  return 0;
}
