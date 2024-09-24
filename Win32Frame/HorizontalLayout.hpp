#ifndef __HORIZONTALLAYOUT_H__
#define __HORIZONTALLAYOUT_H__

#include "IFLayout.hpp"

#include <vector>

class HorizontalLayout : public IFLayout
{
private:
    struct HorizontalLayoutItem
    {
        UINT nWidthRatio; // ռ���ܿ�ȵı���
        IFComponent* pComp;
    };

protected:
    std::vector<HorizontalLayoutItem> m_items;

public:
    HorizontalLayout() : m_items() {}

    void AddComponent(
        _In_ UINT nWidthRatio,  // ���������ˮƽ�����еĿ�ȱ���
        _In_ IFComponent* pComp
    )
    {
        m_items.push_back({
            nWidthRatio,
            pComp
        });
    }

    BOOL OnCreate(_In_ HWND hParentWnd)
    {
        for (const HorizontalLayoutItem& item : m_items)
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
        INT totalWidth = width;
        INT currentX = x;
        BOOL bShowTips = FALSE;
        //for (const VerticalLayoutItem& item : m_items)
        for (auto pItem = m_items.begin(); pItem != m_items.end(); ++pItem)
        {
            // ��������߶�
            INT itemWidth = (totalWidth * pItem->nWidthRatio) / 100;
            // ��ʾ��С��Χ
            if (itemWidth < pItem->pComp->GetMinWidth()) bShowTips = TRUE;
            if (height < pItem->pComp->GetMinHeight()) bShowTips = TRUE;
            // ��ֹ�ؼ��ѻ�
            INT limitWidth = max(itemWidth, pItem->pComp->GetMinWidth());
            INT limitHeight = max(height, pItem->pComp->GetMinHeight());
            // ���Ƶ��Ա߿�
            DebugTools::GetInstance().AddBorder(currentX, y, limitWidth, limitHeight, 2);
            // ���¿ؼ�����
            pItem->pComp->OnLayout(currentX, y, itemWidth, limitHeight);
            // ������һ���������ʼY����
            currentX += itemWidth;
        }
        DebugTools::GetInstance().ShowTips(bShowTips);
    }

    void OnDestroy()
    {
        for (const HorizontalLayoutItem& item : m_items)
        {
            item.pComp->OnDestroy();
        }
    }
};

#endif // __HORIZONTALLAYOUT_H__