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
    ui->W_CoctailItems->setColumnCount(3);
    ui->W_CoctailItems->setHorizontalHeaderLabels(QStringList() << "Название алкоголя"
                                                                << "Объем"
                                                                << "Фирма");
    ui->W_CoctailItems->resizeColumnsToContents();
    ui->W_CoctailItems->resizeRowsToContents();
    ui->W_CoctailItems->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->W_CoctailItems, &QTableWidget::customContextMenuRequested, this,
        &MainWindow::showContextMenu);
    ui->label->setFont(QFont("Times New Roman"));
    auto it = listCoctails->begin();
    while (it != listCoctails->end()) {
        if (ui->W_typeCoctail->findText(it->typeCoctail) < 0) {
            ui->W_typeCoctail->addItem(it->typeCoctail);
        }
        ++it;
    }
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::showContextMenu(const QPoint& pos)
{
    QTableWidget* table = qobject_cast<QTableWidget*>(sender());
    if (table == nullptr) {
        return;
    }
    QPoint gpos = table->mapToGlobal(pos);
    QMenu menu;
    menu.addAction("Изменить ингридиент", this, &MainWindow::changeItem);
    menu.exec(gpos);
}

void MainWindow::changeItem()
{
    AlcoChoseItemWidget* w = new AlcoChoseItemWidget(allAlc);
    w->show();
    connect(w, &AlcoChoseItemWidget::choise, this, &MainWindow::chooseItem);
}

void MainWindow::chooseItem(const QString& type, const QString& name)
{
    QTableWidgetItem* itemTable = ui->W_CoctailItems->item(ui->W_CoctailItems->currentRow(), 0);
    for (auto& item : currentCoctail.items) {
        if (item->getData()->name == itemTable->text()) {
            item->getData()->name = name;
            item->setTypeAlco(type);
            break;
        }
    }
    showCoctail();
}

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

    auto it = listCoctails->begin();
    while (it != listCoctails->end()) {
        if (it->name == ui->W_coctailName->currentText()) {
            currentCoctail = *it;
            break;
        }
        ++it;
    }
    if (currentCoctail.name.isEmpty()) {
        return;
    }
    showCoctail();
}

void MainWindow::on_W_typeCoctail_currentIndexChanged(const QString& arg1)
{
    ui->W_coctailName->clear();
    auto it = listCoctails->begin();
    while (it != listCoctails->end()) {
        if (it->typeCoctail == arg1) {
            ui->W_coctailName->addItem(it->name);
        }
        ++it;
    }
}

void MainWindow::on_Btn_CreateCoctail_clicked()
{
    QString msg = "";
    for (auto& item : currentCoctail.items) {
        auto valid = searchItem(item);
        switch (valid) {
        case -1:
            msg += QString("%1 нет в вашем баре \n").arg(item->getData()->name);
            break;
        case 0:
            msg += QString("%1 (%2) не хватает объема в вашем баре \n")
                       .arg(item->getData()->name)
                       .arg(item->getData()->company);
            break;
        default:
            break;
        }
    }
    if (!msg.isEmpty()) {
        int ret = QMessageBox::warning(this, "Предупрждение",
            QString("%1Все равно сделать коктейль?").arg(msg), QMessageBox::Yes | QMessageBox::No);
        if(ret == QMessageBox::No) {
            return;
        }
    }

    for (auto& item : currentCoctail.items) {
        auto barMap = bar->getCurrentMap();
        auto it = barMap->begin();
        while(it != barMap->end()) {
            for (auto& itemList : *it) {
                if (itemList->getData()->name == item->getData()->name) {
                    if (itemList->getData()->volume >= item->getData()->volume) {
                        itemList->getData()->volume -= item->getData()->volume;
                    } else {
                        itemList->getData()->volume = 0;
                    }
                    itemList->reloadData();
                }
            }
            ++it;
        }
    }
    bar->save();
}

int MainWindow::searchItem(AlcoItem* item)
{
    auto barMap = bar->getCurrentMap();
    for (auto& list : *barMap) {
        for (auto& itemList : list) {
            if (itemList->getData()->name == item->getData()->name) {
                if (itemList->getData()->volume >= item->getData()->volume) {
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

void MainWindow::showCoctail()
{
    ui->W_CoctailItems->setRowCount(0);
    for (auto const& item : qAsConst(currentCoctail.items)) {
        int row = ui->W_CoctailItems->rowCount();
        ui->W_CoctailItems->setRowCount(row + 1);
        auto itemName = new QTableWidgetItem(item->getData()->name);
        auto itemVolume = new QTableWidgetItem(QString::number(item->getData()->volume));
        auto firm = new QComboBox;
        connect(firm, QOverload<const QString&>::of(&QComboBox::currentIndexChanged), this,
            &MainWindow::changeFirm);
        firm->setStyleSheet(firm->styleSheet() + "QComboBox { background-color: white; }");
        QStringList firmsCurrentBar;
        auto curMap = bar->getCurrentMap();
        auto it = curMap->begin();
        while (it != curMap->end()) {
            for (auto& aitem : it.value()) {
                if (aitem->getData()->name == item->getData()->name) {
                    firmsCurrentBar << aitem->getData()->company;
                }
            }
            ++it;
        }
        firm->addItems(firmsCurrentBar);
        if (!firmsCurrentBar.isEmpty()) {
            item->getData()->company = firmsCurrentBar.first();
        }
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
        ui->W_CoctailItems->setCellWidget(row, 2, firm);
        ui->W_CoctailItems->resizeColumnsToContents();
        ui->W_CoctailItems->resizeRowsToContents();
    }
    ui->W_About->setPlainText(currentCoctail.about);
}

void MainWindow::changeFirm(const QString& firm)
{
    QComboBox* box = qobject_cast<QComboBox*>(sender());
    for (int r = 0; r < ui->W_CoctailItems->rowCount(); r++) {
        auto boxItem = ui->W_CoctailItems->cellWidget(r, 2);
        if (box == boxItem) {
            currentCoctail.items[r]->getData()->company = firm;
        }
    }
}
