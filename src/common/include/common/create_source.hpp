#include <gst/gst.h>
#include <glib.h>
#include "deepstream_sources.h"
#include "nlohmann/json.hpp"

class Source {
  public:
    /**
     * It creates a source element.
     * 
     * @return GstElement*
     */
    static GstElement* Create();
};