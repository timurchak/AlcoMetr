#include "alco_current_bar.h"
#include "ui_alco_current_bar.h"

AlcoCurrentBar::AlcoCurrentBar(AlcoMap* map, QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::AlcoCurrentBar)
    , saver(new AlcoSaveWorker())
    , alcoList(map)
    , lay(new QDynamicGridLayout(2))
{
    ui->setupUi(this);
    auto it = alcoList->begin();
    while (it != alcoList->end()) {
        // std::sort(it.value().begin(), it.value().end(), variantLessThan);
        ui->W_typeAlc->addItem(it.key());
        ++it;
    }
    ui->Lay_main->addLayout(lay);
    lay->setHorizontalSpacing(2);
    readSaveFile();
}

AlcoCurrentBar::~AlcoCurrentBar() { delete ui; }

void AlcoCurrentBar::on_Btn_Add_clicked()
{
    QString type = ui->W_typeAlc->currentText();
    auto item = new AlcoItem({ ui->W_choseAlc->currentText(), "", 0, 0 }, type);
    if (!currentMap->contains(type)) {
        currentMap->operator[](type) = AlcoList();
    }
    if (!tables.contains(type)) {
        tables[type] = addTable(type);
        tables[type]->setList(&currentMap->operator[](type));
    }

    currentMap->operator[](type) << item;
    tables[type]->addItem(item);
}

void AlcoCurrentBar::on_W_typeAlc_currentIndexChanged(const QString& arg1)
{
    if (alcoList->contains(arg1)) {
        ui->W_choseAlc->clear();
        for (auto& item : alcoList->value(arg1)) {
            ui->W_choseAlc->addItem(item->getData()->name);
        }
    }
}

void AlcoCurrentBar::on_Btn_Save_clicked()
{
    /*AlcoMap cur;
    auto it = tables.begin();
    while (it != tables.end()) {
        QList<AlcoLine> list;
        cur[it.key()] = it.value()->getList();
        ++it;
    }
    saver->setMap(cur);*/
    save();
}

void AlcoCurrentBar::readSaveFile() { reloadAlco(); }

void AlcoCurrentBar::reloadAlco()
{
    saver->readSave();
    currentMap = saver->getMap();
    auto it = currentMap->begin();
    while (it != currentMap->end()) {
        auto table = addTable(it.key());
        tables[it.key()] = table;
        table->setList(&it.value());
        ++it;
    }
}

AlcoTable* AlcoCurrentBar::addTable(const QString& name)
{
    AlcoTable* table = new AlcoTable(name);

    lay->add(table);

    return table;
}

void AlcoCurrentBar::on_pushButton_clicked() { }

AlcoMap* AlcoCurrentBar::getCurrentMap() const { return saver->getMap(); }

void AlcoCurrentBar::save()
{
    saver->reloadSave();
}
