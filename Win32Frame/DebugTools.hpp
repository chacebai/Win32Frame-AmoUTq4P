#ifndef __DEBUGTOOLS_H__
#define __DEBUGTOOLS_H__

#include <vector>
#include <Windows.h>

class DebugTools
{
private:
    BOOL m_showWindow;
    std::vector<RECT> m_debugRectangles;

public:
    static DebugTools& GetInstance()
    {
        static DebugTools instance(800, 600);
        return instance;
    }
    void Show()
    {
        if (m_showWindow) return;
        m_showWindow = TRUE;
        ShowWindow(m_hWnd, SW_SHOW);
        UpdateWindow(m_hWnd);
    }
    void Hide()
    {
        if (!m_showWindow) return;
        m_showWindow = FALSE;
        ShowWindow(m_hWnd, SW_HIDE);
    }
    void SetText(LPCTSTR displayText, int cLength)
    {
        m_displayText = displayText;
        m_displayTextLength = cLength;
        InvalidateRect(m_hWnd, NULL, TRUE);
    }
    void ShowTips(BOOL display)
    {
        LPCTSTR displayText = TEXT("主窗口中布局容器已满，没有足够的空间来放置更多的控件\r\nThe layout container in the main window is full and there is not enough space to place more controls.");
        if (display) {
            DebugTools::GetInstance().SetText(displayText, (int)strlen(displayText));
            DebugTools::GetInstance().Show();
        }
        else {
            DebugTools::GetInstance().Hide();
        }
    }
    void AddBorder(
        _In_ INT x,
        _In_ INT y,
        _In_ INT width,
        _In_ INT height,
        _In_ int widthBorder)
    {
        m_debugRectangles.push_back(RECT{ x,y,x + width,y + height });
    }
    void ClearBorder()
    {
        m_debugRectangles.clear();
    }
    void DrawLayoutBounds(_In_ HDC hdc)
    {
        // 绘制边框颜色 (红色边框)
        HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0)); // 2px 红色边框
        HGDIOBJ hOldPen = SelectObject(hdc, hPen);
        // 设置画刷为 NULL，以避免填充矩形
        HGDIOBJ hOldBrush = SelectObject(hdc, GetStockObject(HOLLOW_BRUSH));

        // 绘制矩形
        for (const auto& rect : m_debugRectangles)
        {
            Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
        }

        // 恢复旧的画笔和画刷
        SelectObject(hdc, hOldPen);
        SelectObject(hdc, hOldBrush);

        // 清理GDI对象
        DeleteObject(hPen);
    }

private:
    DebugTools() = delete;
    DebugTools(const DebugTools&) = delete;
    DebugTools& operator=(const DebugTools&) = delete;
    DebugTools(int nWidth, int nHeight)
    {
        hInstance = GetModuleHandle(NULL);

        WNDCLASS wc = {};
        wc.lpszClassName = TEXT("DebugToolsClass");
        wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.lpfnWndProc = WindowProc;
        wc.hInstance = hInstance;
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        RegisterClass(&wc);

        // 计算屏幕中心
        RECT screenRect = { 0 };
        SystemParametersInfo(SPI_GETWORKAREA, 0, &screenRect, 0);
        int centerX = screenRect.left + (screenRect.right - screenRect.left - nWidth) / 2;
        int centerY = screenRect.top + (screenRect.bottom - screenRect.top - nHeight) / 2;

        m_hWnd = CreateWindowEx(
            WS_EX_LAYERED,
            wc.lpszClassName,
            TEXT(""),
            WS_OVERLAPPEDWINDOW,
            centerX, centerY, nWidth, nHeight,
            NULL,
            NULL,
            hInstance,
            this);
        SetLayeredWindowAttributes(m_hWnd, RGB(0, 0, 0), 225, LWA_ALPHA);
        m_showWindow = FALSE;
    };
    ~DebugTools() { /*DestroyWindow(m_hWnd);*/ }
    static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        DebugTools* pThis;

        if (uMsg == WM_NCCREATE)
        {
            pThis = static_cast<DebugTools*>(reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams);
            SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));
        }
        else
        {
            pThis = reinterpret_cast<DebugTools*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
        }

        switch (uMsg)
        {
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            // 设置文本颜色
            SetTextColor(hdc, RGB(0, 0, 0));
            // 设置背景颜色
            SetBkColor(hdc, RGB(255, 255, 255));
            RECT rect;
            GetClientRect(hWnd, &rect);
            // 绘制文本
            DrawText(hdc, pThis->m_displayText, pThis->m_displayTextLength, &rect, DT_WORDBREAK | DT_NOCLIP);
            EndPaint(hWnd, &ps);
            break;
        }
        case WM_LBUTTONDOWN:
            PostMessage(hWnd, WM_NCLBUTTONDOWN, HTCAPTION, lParam);
            break;
        case WM_CLOSE:
        case WM_DESTROY:
            // PostQuitMessage(0); // 退出程序循环
            pThis->Hide();
            return TRUE;
        }

        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }

    HWND m_hWnd;
    HINSTANCE hInstance;
    LPCTSTR m_displayText = NULL;
    int m_displayTextLength = 0;
};

#endif // __DEBUGTOOLS_H__