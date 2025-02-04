#pragma once
/******************************************************************************
*
*     application.h
*
*     patrick woods
*     patrick.woods@rogers.com
*
*     - defines a class that creates a window and handles all the Win32 duties
*
******************************************************************************/

#include <Windows.h>
#include <string>
#include <ctime>

namespace bigred
{
  /*--------------------------------------------------------- class Application
  * 
  *     - this is a singleton class that handles all the Win32 duties on
  *     creation
  *     - all functions will have to be accessed throught the GetInstance()
  *     function, which returns a reference to the singleton instance
  * 
  *     - Run() is a public function which is only a wrapper for the private
  *     start() function
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

    //--------------------------------------------------------- con/destructors

    Application();
    ~Application() {}
    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    //------------------------------------------------------ critical functions

    /*
    *     - start() is called once to initiate the applciation; thereafter the
    *     class handles all other functions; it is wrapped publically by Run()
    */
    void start(HINSTANCE instance);

    /*
    *     - update() is called once every game cycle inside the windows message
    *     loop
    * 
    *     - delta_time is the numebr of frames (taken fromt he hi-res counter)
    *     since the last call to update()
    */
    void update(float delta_time);

    //------------------------------------------------------- utility functions

    // decorated = 00:00:00; not decorated = 000000
    std::wstring get_time(bool is_decorated = true);

    // decorated = 00/00/00; not decorated = 000000
    std::wstring get_date(bool is_decorated = true);

    //-------------------------------------------------------- member variables

    HINSTANCE       instance_handle;
    HWND            window_handle;
    bool            is_running;
    bool            is_minimized;
    bool            is_paused;

    std::wstring    window_title;
    int             window_width;
    int             window_height;

    HICON           icon_handle;

    LARGE_INTEGER   time_frequency;
    LARGE_INTEGER   time_last_frame;
    LARGE_INTEGER   time_this_frame;
    float           time_delta;
  };
}
