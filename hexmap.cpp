// hexmap.cpp

#include "hexmap.h"

namespace bigred
{
  HexMap::HexMap()
  {
    m_map_width = 0;
    m_map_height = 0;
    m_rows = 0;
    m_columns = 0;
    m_is_initialized = false;
  }

  bool HexMap::Initialize(int width, int height)
  {
    m_map_width = 0;
    m_map_height = 0;
    m_rows = 0;
    m_columns = 0;
    m_is_initialized = false;

    // this enforces a minimum map size, one that can be traversed
    if ((width >= 3) && (height >= 3))
    {
      map_width = width;
      map_height = height;

      // odd columns + even columns
      m_columns = (1 + ((m_map_width - 2)/3)) + (m_map_width / 3);

      // odd rows + even rows
      m_rows = ((int)((float)m_map_height / (2 * ALPHA))) + (1 + (int)((((float)m_map_height) - (3 * ALPHA))/(2 * ALPHA)));
      
      is_initialized = true;
    }

    return is_initialized;
  }
}
