#pragma once
#include "deepstream_primary_gie.h"
#include "config/config.hpp"

class PrimaryGie{
  public:
    static GstElement* Create(std::string name);
};