#ifndef __IFCOMPONENT_H__
#define __IFCOMPONENT_H__

#include "DebugTools.hpp"

#include <Windows.h>

class IFComponent
{
protected:
    INT m_width = 0;
    INT m_height = 0;
    INT m_minWidth = 0;
    INT m_minHeight = 0;
    INT m_maxWidth = INT_MAX;
    INT m_maxHeight = INT_MAX;
public:

    virtual BOOL OnCreate(HWND hParentWnd) = 0;

    virtual void OnLayout(
        _In_ INT  x,
        _In_ INT  y,
        _In_ INT width,
        _In_ INT height) = 0;

    virtual void OnDestroy() = 0;

    void SetMinSize(INT minWidth, INT minHeight)
    {
        m_minWidth = minWidth;
        m_minHeight = minHeight;
    }
    void SetMaxSize(INT maxWidth, INT maxHeight)
    {
        m_maxWidth = maxWidth;
        m_maxHeight = maxHeight;
    }
    INT GetWidth() const { return m_width; }
    INT GetHeight() const { return m_height; }
    INT GetMinWidth() const { return m_minWidth; }
    INT GetMinHeight() const { return m_minHeight; }
    INT GetMaxWidth() const { return m_maxWidth; }
    INT GetMaxHeight() const { return m_maxHeight; }
    INT GetLimitWidth(const INT width) const { return max(m_minWidth, min(width, m_maxWidth)); }
    INT GetLimitHeight(const INT height) const { return max(m_minHeight, min(height, m_maxHeight)); }
};

#endif // __IFCOMPONENT_H__