#pragma once
/******************************************************************************
*
*     datetime.h
*
*     patrick woods
*     patrick.woods@rogers.com
*
*     - global utility functions for getting the date and time
*
******************************************************************************/

#include <string>

namespace datetime
{
  /*  decorated -->       tt:tt:tt    dd/dd/dd
  *   undecorated -->     tttttt      dddddd
  */
  std::wstring GetTimeString(bool is_decorated = true);
  std::wstring GetDateString(bool is_decorated = true);
  std::wstring GetDateAndTimeString(bool is_decorated = true);
}