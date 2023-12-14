#include "qdynamicgridlayout.h"

QDynamicGridLayout::QDynamicGridLayout(int maxColumn, QWidget* parent)
    : QGridLayout(parent)
    , maxColumn(maxColumn)
    , currentRow(0)
    , currentColumn(0)
{
}

bool QDynamicGridLayout::add(QWidget* w, int r, int c)
{
    if (r < 0 || c < 0) {
        addWidget(w, currentRow, currentColumn);
        editIndexes();
        return true;
    } else {
        if (itemAtPosition(r, c) == nullptr) {
            return false;
        }
        addWidget(w, r, c);
        return true;
    }
}

bool QDynamicGridLayout::add(QLayoutItem* item, int r, int c)
{
    if (r < 0 || c < 0) {
        addItem(item, currentRow, currentColumn);
        editIndexes();
        return true;
    } else {
        if (itemAtPosition(r, c) == nullptr) {
            return false;
        }
        addItem(item, r, c);
        return true;
    }
}

bool QDynamicGridLayout::add(QLayout* lay, int r, int c)
{
    if (r < 0 || c < 0) {
        addLayout(lay, currentRow, currentColumn);
        editIndexes();
        return true;
    } else {
        if (itemAtPosition(r, c) == nullptr) {
            return false;
        }
        addLayout(lay, r, c);
        return true;
    }
}

void QDynamicGridLayout::setColumn(int column) {
    maxColumn = column;
    int i = 0;
    QList<QLayoutItem*> list;
    while(itemAt(i) != nullptr) {
        list.push_back(itemAt(i));
        i++;
    }
    currentRow = 0;
    currentColumn = 0;
    auto it = list.begin();
    while(it != list.end()) {
        add(*it);
        ++it;
    }
}

void QDynamicGridLayout::editIndexes()
{
    currentColumn++;
    if (currentColumn == maxColumn) {
        currentRow++;
        currentColumn = 0;
    }
}
