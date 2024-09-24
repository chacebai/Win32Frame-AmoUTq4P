#ifndef __TABCONTROL_H__
#define __TABCONTROL_H__

#include "IFControl.hpp"

class TabControl : public IFControl
{
protected:

    LPCTSTR m_pLabel;
    HWND   m_hWnd;
    HFONT  m_hFont;

public:

    TabControl(
        LPCTSTR pLabel
    ) :
        m_pLabel(pLabel),
        m_hWnd(NULL),
        m_hFont(NULL)
    {
        m_units = GetDialogBaseUnits();
        m_width = MulDiv(LOWORD(m_units), 50, 4);
        m_height = MulDiv(HIWORD(m_units), 10, 8);
    }

    BOOL OnCreate(
        HWND hParentWnd
    )
    {
        m_hWnd = CreateWindow(
            TEXT("SysTabControl32"),
            m_pLabel,
            WS_CHILD | WS_VISIBLE,
            CW_USEDEFAULT, CW_USEDEFAULT,
            CW_USEDEFAULT, CW_USEDEFAULT,
            hParentWnd,
            NULL,
            (HINSTANCE)GetWindowLongPtr(hParentWnd, GWLP_HINSTANCE),
            NULL
        );
        if (!m_hWnd)
        {
            return FALSE;
        }

        NONCLIENTMETRICS metrics = { 0 };
        metrics.cbSize = sizeof(NONCLIENTMETRICS);
        SystemParametersInfo(
            SPI_GETNONCLIENTMETRICS,
            metrics.cbSize,
            &metrics,
            0
        );
        metrics.lfCaptionFont.lfHeight = MulDiv(HIWORD(m_units), 10, 8);

        m_hFont = CreateFontIndirect(&metrics.lfCaptionFont);
        SendMessage(m_hWnd, WM_SETFONT, (WPARAM)m_hFont, MAKELPARAM(FALSE, 0));

        ShowWindow(m_hWnd, SW_SHOWDEFAULT);

        return TRUE;
    }

    BOOL CreateTabPage(LPCTSTR pageName) const
    {
        TCITEM tie = { 0 };
        // Add tabs for each day of the week.
        tie.mask = TCIF_TEXT | TCIF_IMAGE;
        tie.iImage = -1;
        tie.pszText = (LPTSTR)pageName;

        int index = TabCtrl_GetItemCount(m_hWnd);
        if (TabCtrl_InsertItem(m_hWnd, index, &tie) == -1)
        {
            DestroyWindow(m_hWnd);
            return FALSE;
        }
        return TRUE;
    }
    void OnLayout(
        _In_ INT  x,
        _In_ INT  y,
        _In_ INT width,
        _In_ INT height
    )
    {
        // 应用最大最小宽高限制
        INT limitX = x;
        INT limitY = y;
        INT limitWidth = max(m_minWidth, min(width, m_maxWidth));
        INT limitHeight = max(m_minHeight, min(height, m_maxHeight));
        // 水平居中处理
        if (m_horizontalCenter)
        {
            limitX = max(x, x + ((INT)(width - limitWidth)) / 2);
        }
        // 垂直居中处理
        if (m_verticalCenter)
        {
            limitY = max(y, y + ((INT)(height - limitHeight)) / 2);
        }
        HDWP hDWP = BeginDeferWindowPos(1);
        if (hDWP)
        {
            DeferWindowPos(
                hDWP,
                m_hWnd,
                NULL,
                limitX, limitY,
                limitWidth, limitHeight,
                SWP_NOZORDER
            );
            EndDeferWindowPos(hDWP);
        }
    }

    void OnDestroy()
    {
        if (m_hFont)
        {
            DeleteObject(m_hFont);
        }
    }

};

#endif // __TABCONTROL_H__