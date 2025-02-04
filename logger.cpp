// logger.cpp

#include "logger.h"
#include <fstream>
#include <cstdarg>
#include <debugapi.h>
#include <ShlObj.h>

namespace bigred
{
  void Logger::Print(const wchar_t* fmt, ...)
  {
    wchar_t buffer[4096];
    va_list arguments;

    va_start(arguments, fmt);
    vswprintf_s(buffer, fmt, arguments);
    va_end(arguments);

    OutputDebugString(buffer);

    // example: %AppData%/BigRed/br.logg

    std::wfstream output_file;
    std::wstring output_path;
    //output_path = get_log_directory() + L"/" + get_log_filename();

    //output_file.open(output_path, std::ios_base::app);
  }

  std::wstring Logger::get_log_directory()
  {
    wchar_t path[1024];
    wchar_t* p_app_data_local;

    SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, nullptr, &p_app_data_local);
    wcscpy_s(path, p_app_data_local);
    wcscat_s(path, L"\\");
    wcscat_s(path, L"BigRed"); // TODO: replace with variable
    CreateDirectory(path, NULL); // TODO: error handling
    wcscat_s(path, L"\\logg");
    CreateDirectory(path, NULL);
    return path;
  }

  std::wstring Logger::get_log_filename()
  {
    return std::wstring();
  }


}
