// datetime.cpp

#include "datetime.h"
#include "pch.h"

namespace datetime
{
  std::wstring GetTimeString(bool is_decorated)
  {
    time_t now = time(0);
    tm local_time;
    localtime_s(&local_time, &now);
    std::wstringstream wss;
    wss << std::put_time(&local_time, L"%T");

    std::wstring time_string = wss.str();

    if (!is_decorated)
    {
      std::wstring remove_char = L":";
      for (wchar_t c: remove_char)
      {
        time_string.erase(std::remove(time_string.begin(), time_string.end(), c), time_string.end());
      }
    }

    return time_string;
  }

  std::wstring GetDateString(bool is_decorated)
  {
    time_t now = time(0);
    tm local_time;
    localtime_s(&local_time, &now);
    std::wstringstream wss;
    wss << std::put_time(&local_time, L"%d/%m/%y");

    std::wstring date_string = wss.str();

    if (!is_decorated)
    {
      std::wstring remove_char = L"/";
      for (wchar_t c : remove_char)
      {
        date_string.erase(std::remove(date_string.begin(), date_string.end(), c), date_string.end());
      }
    }

    return date_string;
  }

  std::wstring GetDateAndTimeString(bool is_decorated)
  {
    std::wstring date_time_string;

    if (is_decorated)
    {
      date_time_string = GetDateString(true) + L" " + GetTimeString(true);
    }
    else
    {
      date_time_string = GetDateString(false) + GetTimeString(false);
    }

    return date_time_string;
  }
}
