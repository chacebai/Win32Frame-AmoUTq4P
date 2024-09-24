#ifndef __TESTWINDOW_H__
#define __TESTWINDOW_H__

#include "BaseWindow.hpp"

class TestWindow : public BaseWindow<TestWindow>
{
protected:

    IFComponent* m_pComp;

    LPCTSTR GetWindowClassName() const
    {
        return TEXT("Test Window Class");
    }

public:

    TestWindow(
        _In_ IFComponent* pComp
    ) :
        BaseWindow(),
        m_pComp(pComp)
    {}

    virtual LRESULT HandleMessage(
        _In_ UINT   uMsg,
        _In_ WPARAM wParam,
        _In_ LPARAM lParam
    )
    {
        switch (uMsg)
        {
        case WM_CREATE:
            m_pComp->OnCreate(m_hWnd);
            return 0;
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(m_hWnd, &ps);
            //RECT rect = { 0 };
            //GetClientRect(m_hWnd, &rect);
            DebugTools::GetInstance().DrawLayoutBounds(hdc);
            EndPaint(m_hWnd, &ps);
            return 0;
        }

        case WM_DPICHANGED:
        {
            // Find the button and resize it
            HWND hWndButton = FindWindowEx(m_hWnd, NULL, NULL, NULL);
            if (hWndButton != NULL)
            {
                UpdateButtonLayoutForDpi(hWndButton);
            }
        }
        break;
        case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                // DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                MessageBox(m_hWnd, TEXT("Test"), TEXT("Test"), MB_OK);
                break;
            case IDM_EXIT:
                DestroyWindow(m_hWnd);
                break;
            default:
                return DefWindowProc(m_hWnd, uMsg, wParam, lParam);
            }
        }
        break;
        case WM_SIZE:
        {
            DebugTools::GetInstance().ClearBorder();
            INT width = max(0, LOWORD(lParam));
            INT height = max(0, HIWORD(lParam));
            m_pComp->OnLayout(0, 0, width, height);
            InvalidateRect(m_hWnd, NULL, TRUE);
        }
        break;
        case WM_CLOSE:
        {
            DestroyWindow(m_hWnd);
        }
        break;
        case WM_DESTROY:
            m_pComp->OnDestroy();
            PostQuitMessage(0);
            return 0;
        }

        return DefWindowProc(m_hWnd, uMsg, wParam, lParam);
    }

};

#endif // __TESTWINDOW_H__