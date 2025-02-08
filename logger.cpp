// logger.cpp

#include "pch.h"
#include "logger.h"
#include "datetime.h"

namespace bigred
{
  Logger::Logger()
  {
    m_log_directory = GetLogDirectory();
    m_log_filename = GetLogFilename();

    m_is_active = true;

    std::wfstream out_file;

    std::wstring os = m_log_directory + L"\\" + m_log_filename;
    out_file.open(os, std::ios_base::app);

    if (out_file.is_open())
    {
      out_file << L"Big Red Log File" << L'\n' << L"----------------\n\n";
      out_file.close();
    }
    else
    {
      MessageBox(NULL, L"Unable to open .logg file!", L"Logg error", MB_OK);
    }
  }

  void Logger::Post(const wchar_t* p_write_string, ...)
  {
    wchar_t buffer[4096];
    va_list args;

    va_start(args, p_write_string);
    vswprintf_s(buffer, p_write_string, args);
    va_end(args);

    std::wfstream out_file;

    std::wstring os = m_log_directory + L"\\" + m_log_filename;
    out_file.open(os, std::ios_base::app);

    if (out_file.is_open())
    {
      std::wstring s = buffer;
      out_file << L"[" << datetime::GetDateAndTimeString() << L"] " << s << L'\n';
      out_file.close();
    }
    else
    {
      MessageBox(NULL, L"Unable to open .logg file!", L"Logg error", MB_OK);
    }
  }

  std::wstring Logger::GetLogDirectory()
  {
    wchar_t path[1024];
    wchar_t* p_appdatalocal;

    SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, nullptr, &p_appdatalocal);

    wcscpy_s(path, p_appdatalocal);
    wcscat_s(path, L"\\");
    wcscat_s(path, L"BigRed");
    CreateDirectory(path, NULL);

    wcscat_s(path, L"\\Logg");
    CreateDirectory(path, NULL);

    return path;
  }

  std::wstring Logger::GetLogFilename()
  {
    wchar_t filename[1024];
    wcscpy_s(filename, L"bigred");
    wcscat_s(filename, datetime::GetDateAndTimeString(false).c_str()); 
    wcscat_s(filename, L".logg");
    return filename;
  }
  bool Logger::Activate()
  {
    if (m_is_active)
    {
      return false;
    }
    else
    {
      Post(L"Logger activated.");
      return m_is_active = true;
    }
  }

  bool Logger::Deactivate()
  {
    if (!m_is_active)
    {
      return false;
    }
    else
    {
      Post(L"Logger deactivated.");
      m_is_active = false;
      return true;
    }
  }
}
