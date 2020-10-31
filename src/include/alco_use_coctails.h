#ifndef ALCO_USE_COCTAILS_H
#define ALCO_USE_COCTAILS_H

#include <QListWidgetItem>
#include <QMenu>
#include <QMessageBox>
#include <QWidget>

#include <alco_chose_item_widget.h>
#include <alco_cocktail_manager.h>
#include <alco_current_bar.h>
#include <alco_item.h>

namespace Ui {
class AlcoUseCoctails;
}

class AlcoUseCoctails : public QWidget {
    Q_OBJECT

public:
    explicit AlcoUseCoctails(AlcoCoctailManager* _manager = nullptr, AlcoMap* _allAlc = nullptr,
        AlcoCurrentBar* _bar = nullptr, QWidget* parent = nullptr);

    ~AlcoUseCoctails();

    void showContextMenu(const QPoint& pos);

    void changeItem();

    void chooseItem(const QString& type, const QString& name);

    void showCoctail();

    int searchItem(AlcoItem* item);

    void changeFirm(const QString& firm);

private slots:
    void on_W_typeCoctail_currentIndexChanged(int index);

private slots:
    void on_W_listCoctails_itemClicked(QListWidgetItem* item);

private slots:

    void on_Btn_CreateCoctail_clicked();

private:
    Ui::AlcoUseCoctails* ui;
    AlcoCoctailManager* manager;
    QList<AlcoCoctail>* listCoctails;
    AlcoMap* allAlc;
    AlcoCoctail currentCoctail;
    AlcoCurrentBar* bar;
};

#endif // ALCO_USE_COCTAILS_H
