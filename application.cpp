// application.cpp

#include "application.h"
#include "resource.h"
#include <ctime>
#include <sstream>
#include <iomanip>

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

    icon_handle = nullptr;

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
    WNDCLASSEX window_class;
    ZeroMemory(&window_class, sizeof(WNDCLASSEX));
    const wchar_t* DEFAULT_WNDCLASSEX_NAME = L"big_red_class";

    // populate the window class
    window_class.style = CS_VREDRAW | CS_HREDRAW;
    window_class.cbSize = sizeof(WNDCLASSEX);
    window_class.cbClsExtra = 0;
    window_class.cbWndExtra = 0;
    window_class.lpfnWndProc = WndProc;
    window_class.hInstance = instance_handle;
    window_class.lpszClassName = DEFAULT_WNDCLASSEX_NAME;
    window_class.lpszMenuName = nullptr;
    // load custom icon or, failing that, the default icon
    icon_handle = LoadIcon(instance_handle, MAKEINTRESOURCE(IDI_MAIN_ICON));
    if (icon_handle != nullptr)
    {
      window_class.hIcon = icon_handle;
      window_class.hIconSm = icon_handle;
    }
    else
    {
      window_class.hIcon = LoadIcon(0, IDI_APPLICATION);
      window_class.hIconSm = LoadIcon(0, IDI_APPLICATION);
    }
    window_class.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
    window_class.hCursor = LoadCursor(0, IDC_ARROW);

    // guard against failure to create the window class
    if (!RegisterClassEx(&window_class))
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
      DEFAULT_WNDCLASSEX_NAME,
      window_title.c_str(),
      window_style,
      0,
      0,
      window_rect.right - window_rect.left,
      window_rect.bottom - window_rect.top,
      0,
      0,
      instance_handle,
      0);

    // guard against a failure to create the window
    if (window_handle == NULL)
    {
      // oh no!!! failure!
#ifdef _DEBUG
      OutputDebugString(L"Failed to create window handle!!!\n");
#endif
      is_running = false;
      return;
    }
    else // success!
    {
#ifdef _DEBUG
      OutputDebugString(L"Application initialized successfully.\n");
#endif
      is_running = true;
      ShowWindow(window_handle, SW_SHOW);
    }

    //std::wstring output_string = L"Window Creation [" + get_date() + L" " + get_time() + L"]\n";
    //OutputDebugString(output_string.c_str());

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

  //--------------------------------------------------- Application::get_time()

  std::wstring Application::get_time(bool is_decorated)
  {
    time_t now = time(0);
    tm ltm;
    localtime_s(&ltm, &now);
    std::wstringstream wss;
    wss << std::put_time(&ltm, L"%T");

    std::wstring time_string = wss.str();

    if (!is_decorated)
    {
      std::wstring remove_char = L":";
      for (wchar_t c : remove_char)
      {
        time_string.erase(std::remove(time_string.begin(), time_string.end(), c), time_string.end());
      }
    }

    return time_string;
  }

  //--------------------------------------------------- Application::get_date()

  std::wstring Application::get_date(bool is_decorated)
  {
    time_t now = time(0);
    tm ltm;
    localtime_s(&ltm, &now);
    std::wstringstream wss;
    wss << std::put_time(&ltm, L"%d/%m/%y");
    std::wstring time_string = wss.str();

    if (!is_decorated)
    {
      std::wstring remove_char = L"/";
      for (wchar_t c : remove_char)
      {
        time_string.erase(std::remove(time_string.begin(), time_string.end(), c), time_string.end());
      }
    }

    return time_string;
  }
} 