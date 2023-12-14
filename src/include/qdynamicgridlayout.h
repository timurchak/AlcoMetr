#ifndef QDYNAMICGRIDLAYOUT_H
#define QDYNAMICGRIDLAYOUT_H

#include <QObject>
#include <QGridLayout>

class QDynamicGridLayout : public QGridLayout
{
    Q_OBJECT
public:
    QDynamicGridLayout(int maxColumn = 4, QWidget* parent = nullptr);
    bool add(QWidget* w, int r = -1, int c = -1);
    bool add(QLayoutItem* item, int r = -1, int c = -1);
    bool add(QLayout* lay, int r = -1, int c = -1);
    void setColumn(int column);
private:
    void editIndexes();
private:
    int maxColumn;
    int currentRow;
    int currentColumn;
};

#endif // QDYNAMICGRIDLAYOUT_H
