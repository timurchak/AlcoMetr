#include "alco_cocktail_manager.h"
#include "ui_alco_cocktail_manager.h"

AlcoCocktailManager::AlcoCocktailManager(const AlcoMap& map, AlcoMap* cmap, QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::AlcoCocktailManager)
    , alcoList(map)
    , alcoCurrentList(cmap)
    , list()
    , saver(new AlcoCoctailsSaveWorker())
{
    saver->setList(&list);
    saver->readSave();
    for (auto& coctail : list) {
        for (auto& item : coctail.items) {
            item->changeValue(0);
        }
    }
    ui->setupUi(this);

    reload();
}

AlcoCocktailManager::~AlcoCocktailManager() { delete ui; }

QList<AlcoCoctail>* AlcoCocktailManager::getCoctailsList()
{
    for (auto& coctail : list) {
        for (auto& item : coctail.items) {
            item->changeValue(0);
        }
    }
    return &list;
}

void AlcoCocktailManager::on_Btn_addCoctail_clicked() { showCreateCoctail(new AlcoCoctail({})); }

void AlcoCocktailManager::addCoctail(AlcoCoctail* _coctail)
{
    if (!_coctail->valid) {
        list << *_coctail;
    }
    reload();
    /*AlcoCoctail coctail = *_coctail;
    auto it = std::find(list.begin(), list.end(), coctail);
    if (it == list.end()) {
        ui->Coctail_list->addItem(coctail.name);
        list << coctail;
    } else {
        *it = coctail;
    }   */
    saver->saveList();
}

void AlcoCocktailManager::showCreateCoctail(AlcoCoctail* coctail)
{
    AlcoCreateCoctailForm* form = new AlcoCreateCoctailForm(alcoList, coctail);
    form->show();
    connect(form, &AlcoCreateCoctailForm::changeCoctail, this, &AlcoCocktailManager::addCoctail);
    // connect(form, &AlcoCreateCoctailForm::finished, this, &AlcoCreateCoctailForm::deleteLater);
}

void AlcoCocktailManager::saveAll() { saver->saveList(); }

void AlcoCocktailManager::reload()
{
    ui->Coctail_list->clear();
    for (auto item : list) {
        ui->Coctail_list->addItem(item.name);
    }
}

void AlcoCocktailManager::on_Coctail_list_doubleClicked(const QModelIndex& index)
{
    if (list.count() < index.row()) {
        return;
    }
    list[index.row()].valid = true;
    showCreateCoctail(&list[index.row()]);
}

void AlcoCocktailManager::on_pushButton_clicked()
{
    int index = ui->Coctail_list->currentRow();
    if (index >= 0) {
        delete ui->Coctail_list->takeItem(index);
        list.removeAt(index);
    }
    saver->saveList();
}
