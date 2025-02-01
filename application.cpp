// application.cpp

#include "application.h"

namespace bigred
{
  //------------------------------------------------- Windows Callback function

  LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
  {
    LRESULT result = 0;

    switch (message)
    {
    case WM_DESTROY:
    {
      Application::GetInstance().is_running = false;
      PostQuitMessage(0);
    } break;

    case WM_CLOSE:
    {
      Application::GetInstance().is_running = false;
      PostQuitMessage(0);
    } break;

    default:
    {
      return DefWindowProc(hwnd, message, wparam, lparam);
    } break;
    }

    return result;
  }
  
  //------------------------------------------------ Application::Application()

  Application::Application()
  {
    // windows variables
    instance_handle = nullptr;
    window_handle = nullptr;

    // game state variables
    is_running = false;
    is_minimized = false;
    is_paused = false;

    window_title = L"window title";
    window_width = 1280;
    window_height = 900;

    // timing services
    QueryPerformanceFrequency(&time_frequency);
    ZeroMemory(&time_last_frame, sizeof(LARGE_INTEGER));
    ZeroMemory(&time_this_frame, sizeof(LARGE_INTEGER));
    time_delta = 0.0f;
  }

  //------------------------------------------------------ Application::start()

  void Application::start(HINSTANCE instance)
  {
    // guard against bad instance handle
    if (instance == nullptr)
    {
#ifdef _DEBUG
      OutputDebugString(L"Bad instance handle.\n");
#endif
      is_running = false;
      return;
    }

    // grab the instance handle
    instance_handle = instance;

    // create the window class
    const wchar_t* window_class_name = L"big_red_class";

    WNDCLASS window_class;
    ZeroMemory(&window_class, sizeof(WNDCLASS));
    window_class.style = CS_VREDRAW | CS_HREDRAW;
    window_class.lpfnWndProc = WndProc;
    window_class.hInstance = instance_handle;
    window_class.lpszClassName = window_class_name;

    // guard against failure to create the window class
    if (!RegisterClass(&window_class))
    {
#ifdef _DEBUG
      OutputDebugString(L"Failed to register window class!!!\n");
#endif
      is_running = false;
      return;
    }

    // correct the xy dimensions for the presence of the titlebar &c.
    DWORD window_style = WS_OVERLAPPED | WS_VISIBLE | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
    RECT window_rect;
    ZeroMemory(&window_rect, sizeof(RECT));
    window_rect.left = 0;
    window_rect.top = 0;
    window_rect.right = window_width;
    window_rect.bottom = window_height;
    AdjustWindowRect(&window_rect, window_style, false);

    // get a window handle
    window_handle = CreateWindowEx(
      0,
      window_class_name,
      window_title.c_str(),
      window_style,
      0, // may be an error -- doesn't seem to spawn at 0 exactly
      0,
      window_rect.right - window_rect.left,
      window_rect.bottom - window_rect.top,
      0,
      0,
      instance_handle,
      0);

    if (window_handle == NULL)
    {
      // oh no!!!
#ifdef _DEBUG
      OutputDebugString(L"Failed to create window handle!!!\n");
#endif
      is_running = false;
      return;
    }
    else
    {
#ifdef _DEBUG
      OutputDebugString(L"Application initialized successfully.\n");
#endif
      is_running = true;
    }

    // process commnand line arguments

    // initialize the renderer

    // start the main loop

    MSG message;

    while (is_running)
    {
      if (PeekMessage(&message, window_handle, 0, 0, PM_REMOVE))
      {
        TranslateMessage(&message);
        DispatchMessage(&message);
      }
      else
      {
        QueryPerformanceCounter(&time_this_frame);
        time_delta = (float)(time_this_frame.QuadPart - time_last_frame.QuadPart) / (float)time_frequency.QuadPart;
        time_last_frame = time_this_frame;

        // update and render
        update(time_delta);

      }
    }
  }

  // ---------------------------------------------------- Application::update()

  void Application::update(float delta_time)
  {
    // process user input

   // render the screen
  }
} 