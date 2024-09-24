#ifndef __VERTICALLAYOUT_H__
#define __VERTICALLAYOUT_H__

#include "IFLayout.hpp"
#include "IFComponent.hpp"

#include <vector>

class VerticalLayout : public IFLayout
{
private:
    struct VerticalLayoutItem
    {
        UINT nHeightRatio; // 占据总高度的比例
        IFComponent* pComp;
    };
protected:
    std::vector<VerticalLayoutItem> m_items;

public:
    VerticalLayout() : m_items() {}

    void AddComponent(
        _In_ UINT nHeightRatio,  // 定义组件在垂直布局中的高度比例
        _In_ IFComponent* pComp
    )
    {
        m_items.push_back({
            nHeightRatio,
            pComp
        });
    }

    BOOL OnCreate(_In_ HWND hParentWnd)
    {
        m_hParentWnd = hParentWnd;
        for (const VerticalLayoutItem& item : m_items)
        {
            if (!item.pComp->OnCreate(hParentWnd))
            {
                return FALSE;
            }
        }
        return IFLayout::OnCreate(hParentWnd);
    }

    void OnLayout(
        _In_ INT x,
        _In_ INT y,
        _In_ INT width,
        _In_ INT height
    )
    {
        INT totalHeight = height;
        INT currentY = y;
        BOOL bShowTips = FALSE;
        //for (const VerticalLayoutItem& item : m_items)
        for (auto pItem = m_items.begin(); pItem != m_items.end(); ++pItem)
        {
            // 计算组件高度
            INT itemHeight = (totalHeight * pItem->nHeightRatio) / 100;
            // 提示最小范围
            if (width < pItem->pComp->GetMinWidth()) bShowTips = TRUE;
            if (itemHeight < pItem->pComp->GetMinHeight()) bShowTips = TRUE;
            // 防止控件堆积
            INT limitWidth = max(width, pItem->pComp->GetMinWidth());
            INT limitHeight = max(itemHeight, pItem->pComp->GetMinHeight());
            // 更新控件布局
            pItem->pComp->OnLayout(x, currentY, limitWidth, limitHeight);
            // 绘制调试边框
            DebugTools::GetInstance().AddBorder(x, currentY, limitWidth, limitHeight, 2);
            // 更新下一个组件的起始Y坐标
            currentY += limitHeight;
        }
        DebugTools::GetInstance().ShowTips(bShowTips);
    }

    void OnDestroy()
    {
        for (const VerticalLayoutItem& item : m_items)
        {
            item.pComp->OnDestroy();
        }
    }
};

#endif // __VERTICALLAYOUT_H__