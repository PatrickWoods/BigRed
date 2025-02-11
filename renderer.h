#pragma once
/******************************************************************************
*
*     renderer.h
*
*     patrick woods
*     patrick.woods@rogers.com
*
*     - defines a class that performs rendering duties
*
******************************************************************************/

#include "pch.h"

#include "application.h"

namespace bigred
{
  class Renderer
  {
    friend class Application;

  public:
    inline static Renderer& GetInstance() { static Renderer r; return r; }

    static bool Initialize(HWND wh);

    static void BeginDraw() { GetInstance().m_p_render_target->BeginDraw(); }
    static void EndDraw() { GetInstance().m_p_render_target->EndDraw(); }
    static void ClearScreen(float r, float g, float b);
    
  protected:
  private:
    Renderer();
    ~Renderer();
    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;

    bool                              m_is_initialized;

    HWND                              m_window_handle;

    // Direct2d Elements
    ID2D1Factory*                     m_p_factory;
    ID2D1HwndRenderTarget*            m_p_render_target;





  };
}