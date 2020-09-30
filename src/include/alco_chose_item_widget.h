#ifndef ALCO_CHOSE_ITEM_WIDGET_H
#define ALCO_CHOSE_ITEM_WIDGET_H

#include <QWidget>
#include <QDialog>
#include <alco_item.h>

namespace Ui {
class AlcoChoseItemWidget;
}

class AlcoChoseItemWidget : public QDialog
{
    Q_OBJECT

public:
    explicit AlcoChoseItemWidget(const AlcoMap& map, QWidget *parent = nullptr);
    ~AlcoChoseItemWidget();

private slots:
    void on_Btn_Ok_clicked();

    void on_W_typeAlco_currentIndexChanged(const QString &arg1);

private:
    Ui::AlcoChoseItemWidget *ui;
    AlcoMap alcoList;
signals:
    void choise(const QString&, const QString&);
};

#endif // ALCO_CHOSE_ITEM_WIDGET_H
