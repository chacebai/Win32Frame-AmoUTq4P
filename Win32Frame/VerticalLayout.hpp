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
        UINT nHeightRatio; // ռ���ܸ߶ȵı���
        IFComponent* pComp;
    };
protected:
    std::vector<VerticalLayoutItem> m_items;

public:
    VerticalLayout() : m_items() {}

    void AddComponent(
        _In_ UINT nHeightRatio,  // ��������ڴ�ֱ�����еĸ߶ȱ���
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
            // ��������߶�
            INT itemHeight = (totalHeight * pItem->nHeightRatio) / 100;
            // ��ʾ��С��Χ
            if (width < pItem->pComp->GetMinWidth()) bShowTips = TRUE;
            if (itemHeight < pItem->pComp->GetMinHeight()) bShowTips = TRUE;
            // ��ֹ�ؼ��ѻ�
            INT limitWidth = max(width, pItem->pComp->GetMinWidth());
            INT limitHeight = max(itemHeight, pItem->pComp->GetMinHeight());
            // ���¿ؼ�����
            pItem->pComp->OnLayout(x, currentY, limitWidth, limitHeight);
            // ���Ƶ��Ա߿�
            DebugTools::GetInstance().AddBorder(x, currentY, limitWidth, limitHeight, 2);
            // ������һ���������ʼY����
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