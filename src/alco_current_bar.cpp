#include "src\include\alco_current_bar.h"
#include "ui_alco_current_bar.h"

AlcoCurrentBar::AlcoCurrentBar(const AlcoMap& map, QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::AlcoCurrentBar)
    , saver(new AlcoSaveWorker())
    , alcoList(map)
{
    ui->setupUi(this);
    auto it = alcoList.begin();
    while (it != alcoList.end()) {
        // std::sort(it.value().begin(), it.value().end(), variantLessThan);
        ui->W_typeAlc->addItem(it.key());
        ++it;
    }
    readSaveFile();
}

AlcoCurrentBar::~AlcoCurrentBar() { delete ui; }

void AlcoCurrentBar::on_Btn_Add_clicked()
{
    if (!tables.contains(ui->W_typeAlc->currentText())) {
        tables[ui->W_typeAlc->currentText()] = addTable(ui->W_typeAlc->currentText());
    }
    auto item = new AlcoItem({ ui->W_choseAlc->currentText(), "", 0, 0 }, ui->W_typeAlc->currentText());
    tables[ui->W_typeAlc->currentText()]->addItem(item);
}

void AlcoCurrentBar::on_W_typeAlc_currentIndexChanged(const QString& arg1)
{
    if (alcoList.contains(arg1)) {
        ui->W_choseAlc->clear();
        for (auto& item : alcoList[arg1]) {
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
    saver->reloadSave();
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
        for (auto const& item : it.value()) {
            table->addItem(item);
        }
        ++it;
    }
}

AlcoTable* AlcoCurrentBar::addTable(const QString& name)
{
    AlcoTable* table = new AlcoTable(name);
    if (countShowTable % 2 == 0) {
        ui->Lay_Left->insertWidget(ui->Lay_Left->count() - 1, table);
    } else {
        ui->Lay_Right->insertWidget(ui->Lay_Right->count() - 1, table);
    }
    countShowTable++;
    return table;
}

void AlcoCurrentBar::on_pushButton_clicked() { }

AlcoMap* AlcoCurrentBar::getCurrentMap() const { return saver->getMap(); }
