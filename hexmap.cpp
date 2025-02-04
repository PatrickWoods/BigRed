// hexmap.cpp

#include "hexmap.h"

namespace bigred
{
  HexMap::HexMap()
  {
    map_width = 0;
    map_height = 0;
    is_initialized = false;
  }

  bool HexMap::Initialize(int width, int height)
  {
    map_width = 0;
    map_height = 0;
    is_initialized = false;

    if ((width >= 3) && (height >= 3))
    {
      map_width = width;
      map_height = height;
      is_initialized = true;
    }

    return is_initialized;
  }
}