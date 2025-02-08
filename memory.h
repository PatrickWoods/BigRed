#pragma once
/******************************************************************************
*
*     memory.h
*
*     patrick woods
*     patrick.woods@rogers.com
*
*     - template classes for D3D object deleters
*
******************************************************************************/

namespace memory
{
  template <class T> void SafeDelete(T& t)
  {
    if (t)
    {
      delete t;
      t = nullptr;
    }
  }

  template <class T> void SafeRelease(T& t)
  {
    if (t)
    {
      t->Release();
      t = nullptr;
    }
  }

  template <class T> void SafeDeleteArray(T& t)
  {
    if (t)
    {
      delete[] t;
      t = nullptr;
    }
  }
}