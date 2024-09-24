#ifndef __PADDINGLAYOUT_H__
#define __PADDINGLAYOUT_H__

#include "IFLayout.hpp"
#include "IFComponent.hpp"

class PaddingLayout : public IFLayout
{
protected:
    INT m_left;
    INT m_top;
    INT m_right;
    INT m_bottom;

    IFComponent* m_pComp;

public:
    PaddingLayout(
        UINT left,
        UINT top,
        UINT right,
        UINT bottom
    ) :
        m_left(left),
        m_top(top),
        m_right(right),
        m_bottom(bottom),
        m_pComp(nullptr)
    {}

    void SetComponent(
        _In_ IFComponent* pComp
    )
    {
        m_pComp = pComp;
    }

    BOOL OnCreate(
        _In_ HWND hParentWnd
    )
    {
        m_pComp->OnCreate(hParentWnd);
        return IFLayout::OnCreate(hParentWnd);
    }

    void OnLayout(
        _In_ INT  x,
        _In_ INT  y,
        _In_ INT width,
        _In_ INT height
    )
    {
        INT limitWidth = max(0, width - m_left - m_right);
        INT limitHeight = max(0, height - m_top - m_bottom);
        m_pComp->OnLayout(x + m_left, y + m_top, limitWidth, limitHeight);
        DebugTools::GetInstance().AddBorder(x, y, width, height, 2);
    }


    void OnDestroy()
    {
        return m_pComp->OnDestroy();
    }

};

#endif // __PADDINGLAYOUT_H__