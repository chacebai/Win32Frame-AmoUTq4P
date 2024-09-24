#ifndef __IFCONTROL_H__
#define __IFCONTROL_H__

#include "IFComponent.hpp"

#include <Windows.h>

class IFControl : public IFComponent
{
protected:
    LONG m_units;
    BOOL m_verticalCenter = TRUE;
    BOOL m_horizontalCenter = TRUE;
    HWND m_hParentWnd = NULL;

public:
    virtual BOOL OnCreate(HWND hParentWnd)
    {
        m_hParentWnd = hParentWnd;
        return m_hParentWnd != NULL;
    }
    void SetHorizontalCenter(bool enable)
    {
        m_horizontalCenter = enable;
    }
    void SetVerticalCenter(bool enable)
    {
        m_verticalCenter = enable;
    }
    virtual void OnLayout(
        _In_ INT  x,
        _In_ INT  y,
        _In_ INT width,
        _In_ INT height) = 0;

    virtual void OnDestroy() = 0;
};

#endif // __IFCONTROL_H__