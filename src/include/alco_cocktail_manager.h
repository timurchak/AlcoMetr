#ifndef ALCO_COCKTAIL_MANAGER_H
#define ALCO_COCKTAIL_MANAGER_H

#include <QWidget>
#include <QListWidgetItem>
#include <alco_create_coctail_form.h>
#include <alco_item.h>
#include <alco_coctails_save_worker.h>

namespace Ui {
class AlcoCocktailManager;
}

class AlcoCocktailManager : public QWidget {
    Q_OBJECT

public:
    explicit AlcoCocktailManager(const AlcoMap& map, AlcoMap* cmap, QWidget* parent = nullptr);
    ~AlcoCocktailManager();

    AlcoMap* getBase();
    void setBase(AlcoMap* value);

private slots:
    void on_Btn_addCoctail_clicked();
    void addCoctail(AlcoCoctail coctail);
    void showCreateCoctail(const AlcoCoctail& coctail);
    void saveAll();

    void on_Coctail_list_doubleClicked(const QModelIndex &index);

private:
    Ui::AlcoCocktailManager* ui;
    AlcoMap alcoList;
    AlcoMap* alcoCurrentList;
    QList<AlcoCoctail> list;
    AlcoCoctailsSaveWorker* saver;
};

#endif // ALCO_COCKTAIL_MANAGER_H
