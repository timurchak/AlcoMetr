#include "alco_create_coctail_form.h"
#include "ui_alco_create_coctail_form.h"

AlcoCreateCoctailForm::AlcoCreateCoctailForm(AlcoMap *map, AlcoCoctail* _coctail, QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::AlcoCreateCoctailForm)
    , alcoList(map)
    , coctail(_coctail)
{
    ui->setupUi(this);
    ui->table->setColumnCount(2);
    ui->table->setHorizontalHeaderLabels(QStringList() << "Название алкоголя"
                                                       << "Объем");

    QSignalBlocker block(ui->W_typeCoctail);
    ui->W_typeCoctail->addItems(QStringList() << "Лонг дринк"
                                              << "Хот дринк"
                                              << "Шорт дринк"
                                              << "Шот");
    block.unblock();

    ui->table->resizeColumnsToContents();
    if (coctail->valid) {
        for (auto& item : coctail->items) {
            addItem(item);
        }
        ui->W_name->setText(coctail->name);
        ui->textEdit->setText(coctail->about);
        ui->W_typeCoctail->setCurrentIndex(ui->W_typeCoctail->findText(coctail->typeCoctail));
    } else {
        ui->W_typeCoctail->setCurrentIndex(0);
    }
    coctail->typeCoctail = ui->W_typeCoctail->currentText();
}

AlcoCreateCoctailForm::~AlcoCreateCoctailForm() { delete ui; }

void AlcoCreateCoctailForm::addItem(const QString& type, const QString& name)
{
    AlcoItem* item = new AlcoItem({ name, "", 0, 0, true}, type);
    addItem(item);
    // sender()->deleteLater();
    coctail->items << item;
}

void AlcoCreateCoctailForm::addItem(AlcoItem* item)
{    
    int row = ui->table->rowCount();
    ui->table->setRowCount(row + 1);
    ui->table->setCellWidget(row, 0, item->name);
    ui->table->setCellWidget(row, 1, item->volume);
    ui->table->resizeColumnsToContents();
    ui->table->resizeRowsToContents();
}

void AlcoCreateCoctailForm::on_Btn_addItem_clicked()
{
    AlcoChoseItemWidget* w = new AlcoChoseItemWidget(alcoList);
    w->show();
    connect(w, &AlcoChoseItemWidget::choise, this,
        QOverload<const QString&, const QString&>::of(&AlcoCreateCoctailForm::addItem));
    // connect(w, &AlcoChoseItemWidget::finished, w, &AlcoChoseItemWidget::deleteLater);
}

void AlcoCreateCoctailForm::on_Btn_Save_clicked()
{
    for(auto& item : coctail->items) {
        item->changeValue(0);
    }
    emit changeCoctail(coctail);
    this->close();
}

void AlcoCreateCoctailForm::on_W_name_textChanged(const QString& arg1) { coctail->name = arg1; }

void AlcoCreateCoctailForm::on_textEdit_textChanged() { coctail->about = ui->textEdit->toPlainText(); }

void AlcoCreateCoctailForm::on_W_typeCoctail_currentTextChanged(const QString &arg1)
{
    coctail->typeCoctail = arg1;
}

