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
        IFComponent* pLabel;   // 标签
        IFComponent* pField;   // 输入组件（或其他控件）
    };

protected:
    std::vector<FormLayoutItem> m_items;
    UINT m_labelWidth;   // 左边标签的宽度比例

public:
    FormLayout(_In_ UINT labelWidth = 30) : m_labelWidth(labelWidth) {}

    // 添加表单项，包括标签和对应的输入组件
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

        INT labelWidth = (width * m_labelWidth) / 100;  // 计算标签宽度
        INT fieldWidth = width - labelWidth;            // 计算输入框宽度

        for (const FormLayoutItem& item : m_items)
        {
            INT itemHeight = totalHeight / (INT)m_items.size();  // 每一行的高度

            // 布局标签
            item.pLabel->OnLayout(
                x,
                currentY,
                labelWidth,
                itemHeight
            );

            // 布局输入组件
            item.pField->OnLayout(
                x + labelWidth,
                currentY,
                fieldWidth,
                itemHeight
            );

            currentY += itemHeight;  // 更新下一行的Y坐标
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