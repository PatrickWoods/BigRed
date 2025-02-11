// renderer.cpp

#include "pch.h"
#include "renderer.h"
#include "memory.h"

namespace bigred
{
  bool Renderer::Initialize(HWND wh)
  {
    if (wh == NULL) return false;

    GetInstance().m_window_handle = wh;

    HRESULT hr;
    hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &GetInstance().m_p_factory);
    if (hr != S_OK)
    {
#ifdef _DEBUG
      Application::GetInstance().PostToLog(L"Renderer::Initialize() failed to create DX factory.");
#endif
      return false;
    }

    RECT rect;
    GetClientRect(GetInstance().m_window_handle, &rect);

    hr = GetInstance().m_p_factory->CreateHwndRenderTarget(
      D2D1::RenderTargetProperties(),
      D2D1::HwndRenderTargetProperties(GetInstance().m_window_handle, D2D1::SizeU(rect.right, rect.bottom)),
      &GetInstance().m_p_render_target);
    if (hr != S_OK)
    {
#ifdef _DEBUG
      Application::GetInstance().PostToLog(L"Renderer::Initialize() failed to create DX render target.");
#endif
      return false;
    }

#ifdef _DEBUG
    Application::GetInstance().PostToLog(L"Renderer::Initialize() completed successfully.");
#endif
    return GetInstance().m_is_initialized = true;
  }

  void Renderer::ClearScreen(float r, float g, float b)
  {
    GetInstance().m_p_render_target->Clear(D2D1::ColorF(r, g, b));
  }

  Renderer::~Renderer()
  {
    // destroy DX objects
    memory::SafeRelease(m_p_render_target);
    memory::SafeRelease(m_p_factory);
  }

  Renderer::Renderer()
  {
    m_is_initialized = false;
    m_p_factory = NULL;
    m_p_render_target = NULL;
    m_window_handle = NULL;
  }
}