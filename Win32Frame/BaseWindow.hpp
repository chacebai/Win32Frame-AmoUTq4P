#ifndef __BASEWINDOW_H__
#define __BASEWINDOW_H__

#include "DebugTools.hpp"

#include <vector>
#include <Windows.h>

template<class DERIVED_TYPE>
class BaseWindow
{
private:
    const int INITIALX_96DPI = 50;
    const int INITIALY_96DPI = 50;
    const int INITIALWIDTH_96DPI = 100;
    const int INITIALHEIGHT_96DPI = 50;

protected:

    HWND m_hWnd;

    virtual LPCTSTR GetWindowClassName() const = 0;

public:

    static LRESULT CALLBACK WindowProc(
        _In_ HWND   hWnd,
        _In_ UINT   uMsg,
        _In_ WPARAM wParam,
        _In_ LPARAM lParam
    )
    {
        DERIVED_TYPE* pThis = NULL;

        if (uMsg == WM_NCCREATE)
        {
            CREATESTRUCT* pCreate = (CREATESTRUCT*) lParam;
            pThis = (DERIVED_TYPE*) pCreate->lpCreateParams;
            SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR) pThis);
            pThis->m_hWnd = hWnd;
        }
        else
        {
            pThis = (DERIVED_TYPE*) GetWindowLongPtr(hWnd, GWLP_USERDATA);
        }
        
        if (pThis)
        {
            return pThis->HandleMessage(uMsg, wParam, lParam);
        }
        else
        {
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
        }        
    }

    BaseWindow() :
        m_hWnd(NULL)
    {}

    virtual LRESULT HandleMessage(
        _In_ UINT   uMsg,
        _In_ WPARAM wParam,
        _In_ LPARAM lParam
    ) = 0;

    virtual void PreRegister() {}
    virtual ATOM Register()
    {
        WNDCLASSEX wndClass = { 0 };
        wndClass.cbSize = sizeof(WNDCLASSEX);
        wndClass.style = CS_HREDRAW | CS_VREDRAW;
        wndClass.lpfnWndProc = DERIVED_TYPE::WindowProc;
        wndClass.cbClsExtra = 0;
        wndClass.cbWndExtra = 0;
        wndClass.hInstance = GetModuleHandle(NULL);
        wndClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
        wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
        wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        wndClass.lpszMenuName = nullptr;
        wndClass.lpszClassName = GetWindowClassName();
        wndClass.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
        return RegisterClassEx(&wndClass);
    }
    virtual void PostRegister() {}

    virtual void PreCreateWindow() {}
    virtual BOOL Create(
        _In_ LPCTSTR pWndName
    )
    {
        Register();
        PreCreateWindow();
        m_hWnd = CreateWindowEx(
            0,
            GetWindowClassName(),
            pWndName,
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT,
            CW_USEDEFAULT, CW_USEDEFAULT,
            NULL,
            NULL,
            GetModuleHandle(NULL),
            this
        );
        PostCreateWindow(m_hWnd ? TRUE : FALSE);
        return m_hWnd ? TRUE : FALSE;
    }
    virtual void PostCreateWindow(BOOL bSuccess) {}

    void UpdateButtonLayoutForDpi(HWND hWnd) const
    {
        int iDpi = GetDpiForWindow(hWnd);
        int dpiScaledX = MulDiv(INITIALX_96DPI, iDpi, USER_DEFAULT_SCREEN_DPI);
        int dpiScaledY = MulDiv(INITIALY_96DPI, iDpi, USER_DEFAULT_SCREEN_DPI);
        int dpiScaledWidth = MulDiv(INITIALWIDTH_96DPI, iDpi, USER_DEFAULT_SCREEN_DPI);
        int dpiScaledHeight = MulDiv(INITIALHEIGHT_96DPI, iDpi, USER_DEFAULT_SCREEN_DPI);
        SetWindowPos(hWnd, hWnd, dpiScaledX, dpiScaledY, dpiScaledWidth, dpiScaledHeight, SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE);
    }


    virtual void Show(
        _In_ INT nCmdShow
    )
    {
        ShowWindow(m_hWnd, nCmdShow);
    }

};

#endif // __BASEWINDOW_H__