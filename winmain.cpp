// main.cpp

#include "pch.h"
#include "application.h"
#include "resource.h"

//------------------------------------------------------------------- WinMain()

int WINAPI wWinMain(HINSTANCE this_instance, HINSTANCE prev_instance, PWSTR lp_command_line, int show_command)
{
  bigred::Application::Run(this_instance);

  return 0;
}