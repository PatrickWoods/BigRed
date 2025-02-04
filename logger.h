#pragma once
/******************************************************************************
*
*     logger.h
*
*     patrick woods
*     patrick.woods@rogers.com
*
*     - singleton class for loggin' duties
*
******************************************************************************/

#include <string>

namespace bigred
{
  class Logger
  {
  public:
    inline static Logger& GetInstance() { static Logger logger; return logger; }

    static void Print(const wchar_t* fmt, ...);

  protected:
  private:
    Logger();
    ~Logger() {}
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    static std::wstring get_log_directory();
    static std::wstring get_log_filename();
  };
}