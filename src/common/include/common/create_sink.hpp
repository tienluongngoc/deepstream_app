#include <gst/gst.h>
#include <glib.h>

class Sink {
  public:
    static GstElement* Create(int current_sink_id); 
};