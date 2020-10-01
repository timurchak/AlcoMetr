#include "alco_create_coctail_form.h"
#include "ui_alco_create_coctail_form.h"

AlcoCreateCoctailForm::AlcoCreateCoctailForm(const AlcoMap& map, AlcoCoctail _coctail, QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::AlcoCreateCoctailForm)
    , alcoList(map)
    , coctail(_coctail)
{
    ui->setupUi(this);
    ui->table->setColumnCount(2);
    ui->table->setHorizontalHeaderLabels(QStringList() << "Название алкоголя"
                                                       << "Объем");

    ui->table->resizeColumnsToContents();
    if(coctail.valid) {
        for(auto& item : coctail.items) {
            addItem(item);

        }
         ui->W_name->setText(coctail.name);
         ui->textEdit->setText(coctail.about);
    }
}

AlcoCreateCoctailForm::~AlcoCreateCoctailForm() { delete ui; }

void AlcoCreateCoctailForm::addItem(const QString& type, const QString& name)
{
    AlcoItem* item = new AlcoItem({ name, "", 0, 0 }, type);
    addItem(item);
    //sender()->deleteLater();
    coctail.items << item;
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

void AlcoCreateCoctailForm::on_Btn_Save_clicked() {
    emit changeCoctail(coctail);
    //this->close();
}

void AlcoCreateCoctailForm::on_W_name_textChanged(const QString &arg1)
{
    coctail.name = arg1;
}

void AlcoCreateCoctailForm::on_textEdit_textChanged()
{
    coctail.about = ui->textEdit->toPlainText();
}