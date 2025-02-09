#pragma once
/******************************************************************************
*
*     logger.h
*
*     patrick woods
*     patrick.woods@rogers.com
*
*     - defines a class that loggs the output of this program
*
******************************************************************************/

#include "pch.h"

namespace bigred
{
  class Logger
  {
  public:
    Logger();
    ~Logger() {}

    void Post(const wchar_t* p_write_string, ...);

    std::wstring GetLogDirectory();
    std::wstring GetLogFilename();

    bool Activate();
    bool Deactivate();
    
  protected:
  private:

    std::wstring        m_log_directory;
    std::wstring        m_log_filename;

    bool                m_is_active;
  };
}