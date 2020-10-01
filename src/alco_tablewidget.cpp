#include "alco_tablewidget.h"

AlcoTable::AlcoTable(const QString& type, QWidget* par)
    : QWidget(par)
    , typeAlco(type)
    , table(new QTableWidget)
    , tittle(new QLabel)
    , btnDelte(new QPushButton)
    , layOthers(new QHBoxLayout)
    , layMain(new QVBoxLayout)
{
    btnDelte->setText("Удалить строку");
    connect(btnDelte, &QPushButton::clicked, this, &AlcoTable::deleteRow);
    layOthers->setContentsMargins(0, 0, 0, 0);
    layOthers->setSpacing(2);
    layMain->setContentsMargins(0, 0, 0, 0);
    layMain->setSpacing(2);
    tittle->setText(typeAlco);
    layOthers->addWidget(tittle);
    layOthers->addWidget(btnDelte);
    layMain->addLayout(layOthers);
    layMain->addWidget(table);
    table->setColumnCount(5);
    table->setHorizontalHeaderLabels(QStringList() << "Название алкоголя"
                                                   << "Фирма производитель"
                                                   << "Текущий объем"
                                                   << "Объем бутылки"
                                                   << "Доля остатка");
    table->resizeColumnsToContents();
    table->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    this->setLayout(layMain);
}

void AlcoTable::addItem(AlcoItem* item)
{
    int row = table->rowCount();
    table->setRowCount(row + 1);
    table->setCellWidget(row, 0, item->name);
    table->setCellWidget(row, 1, item->company);
    table->setCellWidget(row, 2, item->volume);
    table->setCellWidget(row, 3, item->volumeBottle);
    table->setCellWidget(row, 4, item->per);
    table->resizeColumnsToContents();
    table->resizeRowsToContents();
    //table->setMinimumHeight((row + 1) * 30 + 40);
    //table->setMaximumHeight((row + 1) * 30 + 40);
    data.push_back(item);

}

void AlcoTable::addItems(const QList<AlcoItem*>& list)
{
    for (auto const& item : qAsConst(list)) {
        addItem(item);
    }
}

QList<AlcoItem*> AlcoTable::getList() { return data; }

void AlcoTable::deleteRow()
{
    int row = table->currentRow();
    table->removeRow(row);
    data.removeAt(row);
}
