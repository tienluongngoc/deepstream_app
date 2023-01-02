#include <gst/gst.h>
#include <glib.h>
#include "deepstream_sources.h"

class Source {
  public:
    static GstElement* CreateSource();
};