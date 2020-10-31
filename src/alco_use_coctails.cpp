#include "alco_use_coctails.h"
#include "ui_alco_use_coctails.h"

AlcoUseCoctails::AlcoUseCoctails(
    AlcoCoctailManager* _manager, AlcoMap* _allAlc, AlcoCurrentBar* _bar, QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::AlcoUseCoctails)
    , manager(_manager)
    , listCoctails(manager->getCoctailsList())
    , allAlc(_allAlc)
    , currentCoctail()
    , bar(_bar)
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
        &AlcoUseCoctails::showContextMenu);

    auto it = listCoctails->begin();
    while (it != listCoctails->end()) {
        if (ui->W_typeCoctail->findText(it->typeCoctail) < 0) {
            ui->W_typeCoctail->addItem(it->typeCoctail);
        }
        ++it;
    }
}

AlcoUseCoctails::~AlcoUseCoctails() { delete ui; }

void AlcoUseCoctails::showContextMenu(const QPoint& pos)
{
    QTableWidget* table = qobject_cast<QTableWidget*>(sender());
    if (table == nullptr) {
        return;
    }
    QPoint gpos = table->mapToGlobal(pos);
    QMenu menu;
    menu.addAction("Изменить ингридиент", this, &AlcoUseCoctails::changeItem);
    menu.exec(gpos);
}

void AlcoUseCoctails::changeItem()
{
    AlcoChoseItemWidget* w = new AlcoChoseItemWidget(allAlc);
    w->show();
    connect(w, &AlcoChoseItemWidget::choise, this, &AlcoUseCoctails::chooseItem);
}

void AlcoUseCoctails::chooseItem(const QString& type, const QString& name)
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

void AlcoUseCoctails::showCoctail()
{
    ui->W_CoctailItems->setRowCount(0);
    for (auto const& item : qAsConst(currentCoctail.items)) {
        int row = ui->W_CoctailItems->rowCount();
        ui->W_CoctailItems->setRowCount(row + 1);
        auto itemName = new QTableWidgetItem(item->getData()->name);
        auto itemVolume = new QTableWidgetItem(QString::number(item->getData()->volume));
        auto firm = new QComboBox;
        connect(firm, QOverload<const QString&>::of(&QComboBox::currentIndexChanged), this,
            &AlcoUseCoctails::changeFirm);
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

int AlcoUseCoctails::searchItem(AlcoItem* item)
{
    auto barMap = bar->getCurrentMap();
    for (auto& list : *barMap) {
        for (auto& itemList : list) {
            if (itemList->getData()->name == item->getData()->name
                && (itemList->getData()->company == item->getData()->company || item->getData()->company.isEmpty())) {
                if (!itemList->getData()->st) {
                    return 1;
                }
                if (itemList->getData()->volume >= item->getData()->volume) {
                    return 1;
                } else {
                    if(itemList->getData()->volume == 0) {
                        return -1;
                    }
                    return 0;
                }
            }
        }
    }
    return -1;
}

void AlcoUseCoctails::changeFirm(const QString& firm)
{
    QComboBox* box = qobject_cast<QComboBox*>(sender());
    for (int r = 0; r < ui->W_CoctailItems->rowCount(); r++) {
        auto boxItem = ui->W_CoctailItems->cellWidget(r, 2);
        if (box == boxItem) {
            currentCoctail.items[r]->getData()->company = firm;
            QTableWidgetItem* item = nullptr;
            for (int i = 0; i < ui->W_CoctailItems->rowCount(); i++) {
                if (ui->W_CoctailItems->item(i, 0)->text()
                    == currentCoctail.items[r]->getData()->name) {
                    item = ui->W_CoctailItems->item(i, 1);
                }
            }
            if (!item) {
                return;
            }
            int valid = searchItem(currentCoctail.items[r]);
            switch (valid) {
            case -1:
                item->setBackground(Qt::red);
                break;
            case 0:
                item->setBackground(Qt::yellow);
                break;
            case 1:
                item->setBackground(Qt::green);
                break;
            default:
                break;
            }
        }
    }
}

void AlcoUseCoctails::on_Btn_CreateCoctail_clicked()
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
        if (ret == QMessageBox::No) {
            return;
        }
    }

    for (auto& item : currentCoctail.items) {
        auto barMap = bar->getCurrentMap();
        auto it = barMap->begin();
        while (it != barMap->end()) {
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

void AlcoUseCoctails::on_W_listCoctails_itemClicked(QListWidgetItem* item)
{
    ui->W_CoctailItems->setRowCount(0);

    auto it = listCoctails->begin();
    while (it != listCoctails->end()) {
        if (it->name == item->text()) {
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

void AlcoUseCoctails::on_W_typeCoctail_currentIndexChanged(int index)
{
    ui->W_listCoctails->clear();
    auto it = listCoctails->begin();
    while (it != listCoctails->end()) {
        if (it->typeCoctail == ui->W_typeCoctail->itemText(index)) {
            QListWidgetItem* item = new QListWidgetItem(it->name);
            QFont font("Times", 14);
            // int valid = 1;
            QVector<int> valid(it->items.count());
            int i = 0;
            for (auto const& item : qAsConst(it->items)) {
                valid[i] = searchItem(item);
                i++;
            }
            int bedVal = valid.count(-1);
            int goodVal = valid.count(0) + valid.count(1);
            if (bedVal > goodVal) {
                item->setBackground(Qt::red);
            } else {
                item->setBackground(Qt::green);
            }
            item->setFont(font);
            ui->W_listCoctails->addItem(item);
        }
        ++it;
    }
}
