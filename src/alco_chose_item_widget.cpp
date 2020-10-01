#include "alco_chose_item_widget.h"
#include "ui_alco_chose_item_widget.h"

AlcoChoseItemWidget::AlcoChoseItemWidget(const AlcoMap& map, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AlcoChoseItemWidget)
    , alcoList(map)
{
    ui->setupUi(this);
    auto it = alcoList.begin();
    while (it != alcoList.end()) {
        ui->W_typeAlco->addItem(it.key());
        ++it;
    }
}

AlcoChoseItemWidget::~AlcoChoseItemWidget()
{
    delete ui;
}

void AlcoChoseItemWidget::on_Btn_Ok_clicked()
{
    emit choise(ui->W_typeAlco->currentText(), ui->W_nameAlco->currentText());
    this->close();
}

void AlcoChoseItemWidget::on_W_typeAlco_currentIndexChanged(const QString &arg1)
{
    if (alcoList.contains(arg1)) {
        ui->W_nameAlco->clear();
        for (auto& item : alcoList[arg1]) {
            ui->W_nameAlco->addItem(item->getData()->name);
        }
    }
}
