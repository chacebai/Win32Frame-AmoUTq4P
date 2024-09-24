#ifndef __IFLAYOUT_H__
#define __IFLAYOUT_H__

#include "BaseWindow.hpp"
#include "IFComponent.hpp"

#include <vector>
#include <Windows.h>

class IFLayout : public IFComponent
{
protected:
    INT m_x = 0;
    INT m_y = 0;
    INT m_width = 0;
    INT m_height = 0;
    HWND m_hParentWnd = NULL;

public:
    virtual BOOL OnCreate(HWND hParentWnd)
    {
        m_hParentWnd = hParentWnd;
        return m_hParentWnd != NULL;
    }

    virtual void OnLayout(
        _In_ INT  x,
        _In_ INT  y,
        _In_ INT width,
        _In_ INT height) = 0;

    virtual void OnDestroy() = 0;

    INT GetX() const { return m_x; }
    INT GetY() const { return m_y; }
    INT GetWidth() const { return m_width; }
    INT GetHeight() const { return m_height; }
};

#endif // __IFLAYOUT_H__