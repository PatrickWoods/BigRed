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

#include "pch.h"

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

  //----------------------------------------------------------------- constants

  constexpr unsigned int APP_FLAG_DEFAULT = 0;
  constexpr unsigned int APP_FLAG_NO_LOGG = 1;
  constexpr unsigned int APP_FLAG_NO_LOG = 1;

  class Application
  {
    friend LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

  public:

    inline static Application& GetInstance() { static Application app; return app; }

    inline static void Run(HINSTANCE instance) { GetInstance().start(instance); }

    inline static bool IsRunning() { return GetInstance().m_is_running; }
    inline static bool IsMinimized() { return GetInstance().m_is_minimized; }
    inline static bool IsPaused() { return GetInstance().m_is_paused; }
    inline static unsigned int GetApplicationFlags() { return GetInstance().m_application_flags; }

    inline static int GetWindowWidth() { return GetInstance().m_window_width; }
    inline static int GetWindowHeight() { return GetInstance().m_window_height; }

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
    *     - delta_time is the number of frames (taken from the hi-res counter)
    *     since the last call to update()
    */
    void update(float delta_time);

    //------------------------------------------------------- utility functions

    // decorated = 00:00:00; not decorated = 000000
    std::wstring get_time(bool is_decorated = true);

    // decorated = 00/00/00; not decorated = 000000
    std::wstring get_date(bool is_decorated = true);

    void process_command_line();

    //-------------------------------------------------------- member variables

    HINSTANCE       m_instance_handle;
    HWND            m_window_handle;
    bool            m_is_running;
    bool            m_is_minimized;
    bool            m_is_paused;

    std::wstring    m_window_title;
    int             m_window_width;
    int             m_window_height;

    HICON           m_icon_handle;

    unsigned int    m_application_flags;

    LARGE_INTEGER   m_time_frequency;
    LARGE_INTEGER   m_time_last_frame;
    LARGE_INTEGER   m_time_this_frame;
    float           m_time_delta;

  };
}
