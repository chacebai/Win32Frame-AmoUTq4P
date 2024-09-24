#ifndef __FORMLAYOUT_H__
#define __FORMLAYOUT_H__

#include "IFLayout.hpp"
#include "IFComponent.hpp"

#include <vector>

class FormLayout : public IFLayout
{
private:
    struct FormLayoutItem
    {
        IFComponent* pLabel;   // ��ǩ
        IFComponent* pField;   // ����������������ؼ���
    };

protected:
    std::vector<FormLayoutItem> m_items;
    UINT m_labelWidth;   // ��߱�ǩ�Ŀ�ȱ���

public:
    FormLayout(_In_ UINT labelWidth = 30) : m_labelWidth(labelWidth) {}

    // ��ӱ��������ǩ�Ͷ�Ӧ���������
    void AddRow(_In_ IFComponent* pLabel, _In_ IFComponent* pField)
    {
        m_items.push_back({
            pLabel,
            pField
            });
    }

    BOOL OnCreate(_In_ HWND hParentWnd)
    {
        for (const FormLayoutItem& item : m_items)
        {
            if (!item.pLabel->OnCreate(hParentWnd) || !item.pField->OnCreate(hParentWnd))
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

        INT labelWidth = (width * m_labelWidth) / 100;  // �����ǩ���
        INT fieldWidth = width - labelWidth;            // �����������

        for (const FormLayoutItem& item : m_items)
        {
            INT itemHeight = totalHeight / (INT)m_items.size();  // ÿһ�еĸ߶�

            // ���ֱ�ǩ
            item.pLabel->OnLayout(
                x,
                currentY,
                labelWidth,
                itemHeight
            );

            // �����������
            item.pField->OnLayout(
                x + labelWidth,
                currentY,
                fieldWidth,
                itemHeight
            );

            currentY += itemHeight;  // ������һ�е�Y����
        }
    }

    void OnDestroy()
    {
        for (const FormLayoutItem& item : m_items)
        {
            item.pLabel->OnDestroy();
            item.pField->OnDestroy();
        }
    }
};

#endif // __FORMLAYOUT_H__