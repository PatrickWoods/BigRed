#pragma once
/******************************************************************************
*
*     hexmap.h
*
*     patrick woods
*     patrick.woods@rogers.com
*
******************************************************************************/

namespace bigred
{
  /*----------------------------------------------------------------- constants
  * 
  *     - ALPHA is just an alias for SQRT_3 / 2
  */
  const float SQRT_3 = 1.7320508f;
  const float ALPHA = 0.8660254f;

  /*************************************************************** class HexMap
  * 
  *     - this class must be initialized before use with the width and height
  *     of the map
  *
  *     - initialization will be refused if the map is less than 2 hexes wide
  *     and tall; this is for two reasons: a) smaller maps do not guarantee 
  *     movement to all hexes and b) every rwo and column will then have the 
  *     same number of hexes
  * 
  ****************************************************************************/

  class HexMap
  {
  public:
    HexMap();
    ~HexMap() {}

    inline bool IsInitialized() { return m_is_initialized; }

    bool Initialize(int width, int height);

  protected:

    int m_map_width;
    int m_map_height;

    int m_rows;
    int m_columns;

    bool m_is_initialized;

  private:
  };
}
