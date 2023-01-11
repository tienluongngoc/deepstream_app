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

#define CONFIG "apps/yolov5_deepstream/config.json"

int main (int argc, char *argv[])
{  
  gst_init (NULL, NULL);
  Config::Instance()->Initialize(CONFIG);
  auto all_config = Config::Instance()->GetAllConfig();

  auto source = Source::Create();
  auto person_detection = PrimaryGie::Create("person_detection");

  auto osd = OSD::Create();
  auto tiler = Tiler::Create();
  
  return 0;
}
