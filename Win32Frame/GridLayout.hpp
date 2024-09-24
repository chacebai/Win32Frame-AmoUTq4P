#ifndef __GRIDLAYOUT_H__
#define __GRIDLAYOUT_H__

#include <vector>

#include "IFLayout.hpp"
#include "IFComponent.hpp"

class GridLayout : public IFLayout
{
private:
    struct GridLayoutItem
    {

        UINT nCol;
        UINT nRow;
        UINT nColsWidth;
        UINT nRowsWidth;

        IFComponent* pComp;
    };
protected:

    UINT m_nCols;
    UINT m_nRows;

    std::vector<GridLayoutItem> m_items;

public:
    GridLayout(
        _In_ UINT nCols,
        _In_ UINT nRows
    ) :
        m_nCols(nCols),
        m_nRows(nRows),
        m_items()
    {}

    void AddComponent(
        _In_ UINT       nCol,
        _In_ UINT       nRow,
        _In_ UINT       nColsWidth,
        _In_ UINT       nRowsWidth,        
        _In_ IFComponent* pComp
    )
    {
        m_items.push_back({
            nCol,
            nRow,
            nColsWidth,
            nRowsWidth,
            pComp
        });
    }

    BOOL OnCreate(
        _In_ HWND hParentWnd
    )
    {
        for (const GridLayoutItem item : m_items)
        {
            if (!item.pComp->OnCreate(hParentWnd))
            {
                return FALSE;
            }
        }
        return IFLayout::OnCreate(hParentWnd);
    }

    void OnLayout(
        _In_ INT  x,
        _In_ INT  y,
        _In_ INT width,
        _In_ INT height
    )
    {
        INT cellWidth = width / m_nCols;
        INT cellHeight = height / m_nRows;

        for (const GridLayoutItem item : m_items)
        {
            INT x0 = cellWidth * item.nCol;
            INT x1 = cellWidth * (item.nCol + item.nColsWidth);

            INT y0 = cellHeight * item.nRow;
            INT y1 = cellHeight * (item.nRow + item.nRowsWidth);

            item.pComp->OnLayout(x + x0, y + y0, x1 - x0, y1 - y0);
        }
    }

    void OnDestroy()
    {
        for (const GridLayoutItem item : m_items)
        {
            item.pComp->OnDestroy();
        }
    }

};

#endif // __GRIDLAYOUT_H__