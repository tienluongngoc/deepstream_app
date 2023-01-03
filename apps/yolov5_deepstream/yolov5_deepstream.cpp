#include <iostream>
#include <gst/gst.h>
#include <glib.h>
#include <stdio.h>
#include "gstnvdsmeta.h"
#include "nvds_yml_parser.h"
#include "common/create_source.hpp"
#include "config/config.hpp"
#include "common/create_primary_gie.hpp"

#define CONFIG "apps/yolov5_deepstream/config.json"

int main (int argc, char *argv[])
{  
  gst_init (NULL, NULL);
  Config::Instance()->Initialize(CONFIG);
  auto all_config = Config::Instance()->GetAllConfig();

  auto source = Source::Create();
  auto person_detection = PrimaryGie::Create("person_detection");

  std::cout << "Hello world \n";
  return 0;
}
