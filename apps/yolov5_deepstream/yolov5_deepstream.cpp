#include <iostream>
#include <gst/gst.h>
#include <glib.h>
#include <stdio.h>
#include "gstnvdsmeta.h"
#include "nvds_yml_parser.h"
#include "common/create_source.hpp"

int main (int argc, char *argv[])
{   
  auto source = Source::CreateSource();
  std::cout << "Hello world \n";
  return 0;
}