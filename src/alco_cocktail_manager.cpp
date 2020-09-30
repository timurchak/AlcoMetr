#include "alco_cocktail_manager.h"
#include "ui_alco_cocktail_manager.h"

AlcoCocktailManager::AlcoCocktailManager(const AlcoMap& map, AlcoMap* cmap, QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::AlcoCocktailManager)
    , alcoList(map)
    , alcoCurrentList(cmap)
{
    ui->setupUi(this);
}

AlcoCocktailManager::~AlcoCocktailManager() { delete ui; }

AlcoMap* AlcoCocktailManager::getBase() { return alcoCurrentList; }

void AlcoCocktailManager::setBase(AlcoMap* value) { alcoCurrentList = value; }

void AlcoCocktailManager::on_Btn_addCoctail_clicked()
{
    showCreateCoctail({});
}

void AlcoCocktailManager::addCoctail(AlcoCoctail coctail)
{
    auto it = std::find(list.begin(), list.end(), coctail);
    if (it == list.end()) {
        ui->Coctail_list->addItem(coctail.name);
        list << coctail;
    } else {
        *it = coctail;
    }    
}

void AlcoCocktailManager::showCreateCoctail(const AlcoCoctail &coctail)
{
    AlcoCreateCoctailForm* form = new AlcoCreateCoctailForm(alcoList, coctail);
    form->show();
    connect(form, &AlcoCreateCoctailForm::changeCoctail, this, &AlcoCocktailManager::addCoctail);
   // connect(form, &AlcoCreateCoctailForm::finished, this, &AlcoCreateCoctailForm::deleteLater);
}

void AlcoCocktailManager::on_Coctail_list_doubleClicked(const QModelIndex &index)
{
    if(list.count() < index.row()) {
        return;
    }
    list[index.row()].valid = true;
    showCreateCoctail(list[index.row()]);
}
