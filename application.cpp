// application.cpp

#include "pch.h"
#include "application.h"
#include "resource.h"
#include "logger.h"
#include "renderer.h"

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
      Application::GetInstance().m_is_running = false;
      PostQuitMessage(0);
    } break;

    case WM_CLOSE:
    {
      Application::GetInstance().m_is_running = false;
      PostQuitMessage(0);
    } break;

    case WM_PAINT:
    {
      // TODO: remove this test code
      Renderer::BeginDraw();
      Renderer::ClearScreen(0.25f, 0.1f, 0.8f);
      Renderer::EndDraw();
      // end TODO
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
    m_instance_handle = nullptr;
    m_window_handle = nullptr;

    // game state variables
    m_is_running = false;
    m_is_minimized = false;
    m_is_paused = false;

    m_window_title = L"window title";
    m_window_width = 1280;
    m_window_height = 900;

    m_icon_handle = nullptr;

    m_application_flags = 0;
    process_command_line();

    // timing services
    QueryPerformanceFrequency(&m_time_frequency);
    ZeroMemory(&m_time_last_frame, sizeof(LARGE_INTEGER));
    ZeroMemory(&m_time_this_frame, sizeof(LARGE_INTEGER));
    m_time_delta = 0.0f;

    // log the startup
    log_system.Post(L"Application startup.");
  }

  Application::~Application()
  {
    log_system.Post(L"Exiting application.");
  }

  //------------------------------------------------------ Application::start()

  void Application::start(HINSTANCE instance)
  {
#ifdef _DEBUG
    log_system.Post(L"Application::start() called.");
#endif

    // guard against bad instance handle
    if (instance == nullptr)
    {
#ifdef _DEBUG
      log_system.Post(L"Bad instance handle.");
#endif
      m_is_running = false;
      return;
    }

    // grab the instance handle
    m_instance_handle = instance;

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
    window_class.hInstance = m_instance_handle;
    window_class.lpszClassName = DEFAULT_WNDCLASSEX_NAME;
    window_class.lpszMenuName = nullptr;
    // load custom icon or, failing that, the default icon
    m_icon_handle = LoadIcon(m_instance_handle, MAKEINTRESOURCE(IDI_MAIN_ICON));
    if (m_icon_handle != nullptr)
    {
      window_class.hIcon = m_icon_handle;
      window_class.hIconSm = m_icon_handle;
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
      log_system.Post(L"Failed to register window class!!!");
#endif
      m_is_running = false;
      return;
    }

    // correct the xy dimensions for the presence of the titlebar &c.
    DWORD window_style = WS_OVERLAPPED | WS_VISIBLE | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
    RECT window_rect;
    ZeroMemory(&window_rect, sizeof(RECT));
    window_rect.left = 0;
    window_rect.top = 0;
    window_rect.right = m_window_width;
    window_rect.bottom = m_window_height;
    AdjustWindowRect(&window_rect, window_style, false);

    // get a window handle
    m_window_handle = CreateWindowEx(
      0,
      DEFAULT_WNDCLASSEX_NAME,
      m_window_title.c_str(),
      window_style,
      0,
      0,
      window_rect.right - window_rect.left,
      window_rect.bottom - window_rect.top,
      0,
      0,
      m_instance_handle,
      0);

    // guard against a failure to create the window
    if (m_window_handle == NULL)
    {
      // oh no!!! failure!
#ifdef _DEBUG
      log_system.Post(L"Failed to create window handle!!!");
#endif
      m_is_running = false;
      return;
    }
    else // success!
    {
#ifdef _DEBUG
      log_system.Post(L"Application initialized successfully.");
#endif
      m_is_running = true;
      ShowWindow(m_window_handle, SW_SHOW);
    }

    // process commnand line arguments

    // initialize the renderer
    Renderer::GetInstance().Initialize(m_window_handle);

    // start the main loop
    MSG message;

    while (m_is_running)
    {
      if (PeekMessage(&message, m_window_handle, 0, 0, PM_REMOVE))
      {
        TranslateMessage(&message);
        DispatchMessage(&message);
      }
      else
      {
        QueryPerformanceCounter(&m_time_this_frame);
        m_time_delta = (float)(m_time_this_frame.QuadPart - m_time_last_frame.QuadPart) / (float)m_time_frequency.QuadPart;
        m_time_last_frame = m_time_this_frame;

        // update and render
        update(m_time_delta);
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

  void Application::process_command_line()
  {
    int argc = 0;
    LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);
    for (int i = 1; i < argc; ++i)
    {
      std::wstring key = argv[i];
      if (key[0] == '-')
      {
        key.erase(0, 1);
        std::transform(key.begin(), key.end(), key.begin(), ::tolower);
        if ((wcscmp(key.c_str(), L"nolog") == 0) || (wcscmp(key.c_str(), L"nologg") == 0))
        {
          m_application_flags = m_application_flags | APP_FLAG_NO_LOG;
        }
      }
    }
  }
} 