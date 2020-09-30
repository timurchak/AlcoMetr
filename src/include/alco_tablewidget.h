#ifndef ALCOTABLEWIDGET_H
#define ALCOTABLEWIDGET_H

#include <QObject>
#include <QTableWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>


#include <alco_item.h>

class AlcoTable : public QWidget
{
    Q_OBJECT
public:
    AlcoTable(const QString& type, QWidget *par = nullptr);
    void addItem(AlcoItem *item);
    void addItems(const QList<AlcoItem*> &list);
    QList<AlcoItem *> getList();
    void deleteRow();
private:
    QString typeAlco;
    QTableWidget* table;
    QLabel* tittle;
    QPushButton* btnDelte;
    QHBoxLayout* layOthers;
    QVBoxLayout* layMain;
    QList<AlcoItem*> data;
};

#endif // ALCOTABLEWIDGET_H
