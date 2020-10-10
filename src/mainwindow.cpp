#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , base(new AlcoBaseWorker())
    , allAlc(base->getMapAlco())
    , bar(new AlcoCurrentBar(allAlc))
    , manager(new AlcoCocktailManager(allAlc, bar->getCurrentMap()))
    , editBase(new AlcoEditBase(base))
    , listCoctails(manager->getCoctailsList())
{
    ui->setupUi(this);
    ui->W_CoctailItems->setColumnCount(2);
    ui->W_CoctailItems->setHorizontalHeaderLabels(QStringList() << "Название алкоголя"
                                                       << "Объем");
    ui->W_CoctailItems->resizeColumnsToContents();
    ui->W_CoctailItems->resizeRowsToContents();
    ui->label->setFont(QFont("Times New Roman"));
    auto it = listCoctails->begin();
    while(it != listCoctails->end()) {
        if(ui->W_typeCoctail->findText(it->typeCoctail) < 0) {
            ui->W_typeCoctail->addItem(it->typeCoctail);
        }
        ++it;
    }
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_Btn_OpenBar_clicked()
{
    if (bar->isHidden()) {
        bar->show();
    } else {
        bar->raise();
        bar->activateWindow();
    }
}

void MainWindow::on_Btn_OpenCoctailManager_clicked()
{
    if (manager->isHidden()) {
        manager->show();
    } else {
        manager->raise();
        manager->activateWindow();
    }
}

void MainWindow::on_Btn_Chose_clicked()
{
    ui->W_CoctailItems->setRowCount(0);
    AlcoCoctail coctail;
    auto it = listCoctails->begin();
    while(it != listCoctails->end()) {
        if(it->name == ui->W_coctailName->currentText()) {
            coctail = *it;
            break;
        }
        ++it;
    }
    if(coctail.name.isEmpty()) {
        return;
    }
    for(auto const& item : qAsConst(coctail.items)) {
        int row = ui->W_CoctailItems->rowCount();
        ui->W_CoctailItems->setRowCount(row + 1);
        auto itemName = new QTableWidgetItem(item->getData()->name);
        auto itemVolume = new QTableWidgetItem(QString::number(item->getData()->volume));
        int valid = searchItem(item);
        switch (valid) {
        case -1:
            itemVolume->setBackground(Qt::red);
            break;
        case 0:
            itemVolume->setBackground(Qt::yellow);
            break;
        case 1:
            itemVolume->setBackground(Qt::green);
            break;
        default:
            break;
        }
        ui->W_CoctailItems->setItem(row, 0, itemName);
        ui->W_CoctailItems->setItem(row, 1, itemVolume);
        ui->W_CoctailItems->resizeColumnsToContents();
        ui->W_CoctailItems->resizeRowsToContents();
    }
    ui->W_About->setPlainText(coctail.about);
}

void MainWindow::on_W_typeCoctail_currentIndexChanged(const QString &arg1)
{
    ui->W_coctailName->clear();
    auto it = listCoctails->begin();
    while(it != listCoctails->end()) {
        if(it->typeCoctail == arg1) {
            ui->W_coctailName->addItem(it->name);
        }
        ++it;
    }
}

void MainWindow::on_Btn_CreateCoctail_clicked()
{

}

int MainWindow::searchItem(AlcoItem* item)
{
    auto barMap = bar->getCurrentMap();
    for(auto& list : *barMap) {
        for(auto& itemList : list) {
            if(itemList->getData()->name == item->getData()->name) {
                if(itemList->getData()->volume >= item->getData()->volume) {
                    return 1;
                } else {
                    return 0;
                }
            }
        }
    }
    return -1;
}

void MainWindow::on_Btn_EditBase_clicked()
{
    if (editBase->isHidden()) {
        editBase->show();
    } else {
        editBase->raise();
        editBase->activateWindow();
    }
}
