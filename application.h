#pragma once
/******************************************************************************
*
*     application.h
*
*     patrick woods
*     patrick.woods@rogers.com
*
*     last revision: 1 feb 2025
*
*     - defines a class that creates a window and handles all the Win32 duties
*
******************************************************************************/

#include <windows.h>
#include <string>

namespace bigred
{
  /*--------------------------------------------------------- class Application
  * 
  *     - this is a singleton class that handles all the Win32 duties on
  *     creation
  * 
  ---------------------------------------------------------------------------*/

  class Application
  {
    friend LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

  public:

    inline static Application& GetInstance() { static Application app; return app; }

    inline static void Run(HINSTANCE instance) { GetInstance().start(instance); }

    inline static bool IsRunning() { return GetInstance().is_running; }
    inline static bool IsMinimized() { return GetInstance().is_minimized; }
    inline static bool IsPaused() { return GetInstance().is_paused; }

  protected:

  private:

    Application();
    ~Application() {}
    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    void start(HINSTANCE instance);
    void update(float delta_time);

    HINSTANCE       instance_handle;
    HWND            window_handle;
    bool            is_running;
    bool            is_minimized;
    bool            is_paused;

    std::wstring    window_title;
    int             window_width;
    int             window_height;

    LARGE_INTEGER   time_frequency;
    LARGE_INTEGER   time_last_frame;
    LARGE_INTEGER   time_this_frame;
    float           time_delta;
  };
}