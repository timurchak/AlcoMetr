#ifndef ALCO_CREATE_COCTAIL_FORM_H
#define ALCO_CREATE_COCTAIL_FORM_H

#include <QWidget>
#include <QComboBox>
#include <QDebug>
#include <QSignalBlocker>

#include <alco_item.h>
#include <alco_chose_item_widget.h>

namespace Ui {
class AlcoCreateCoctailForm;
}

class AlcoCreateCoctailForm : public QDialog
{
    Q_OBJECT

public:
    explicit AlcoCreateCoctailForm(AlcoMap* map, AlcoCoctail* _coctail, QWidget *parent = nullptr);
    ~AlcoCreateCoctailForm();
    void addItem(const QString& type, const QString& name);
    void addItem(AlcoItem* item);

private slots:
    void on_Btn_addItem_clicked();

    void on_Btn_Save_clicked();

    void on_W_name_textChanged(const QString &arg1);

    void on_textEdit_textChanged();

    void on_W_typeCoctail_currentIndexChanged(const QString &arg1);

private:
    Ui::AlcoCreateCoctailForm *ui;
    AlcoMap* alcoList;
    AlcoCoctail* coctail;
signals:
    void changeCoctail(AlcoCoctail*);
};

#endif // ALCO_CREATE_COCTAIL_FORM_H
