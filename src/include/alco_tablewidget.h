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
    void setList(AlcoList* list);
    AlcoList *getList();
    void deleteRow();
    void reload();
private:

private:
    QString typeAlco;
    QTableWidget* table;
    QLabel* tittle;
    QPushButton* btnDelte;
    QHBoxLayout* layOthers;
    QVBoxLayout* layMain;
    AlcoList* data;
};

#endif // ALCOTABLEWIDGET_H
