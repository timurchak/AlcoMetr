#include "mainwindow.h"
#include "./ui_mainwindow.h"
/*
 * TODO(timurchak): Добавить функционал выпить стопку
 * TODO(timurchak): Добавить фото
 */
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , base(new AlcoBaseWorker())
    , allAlc(base->getMapAlco())
    , bar(new AlcoCurrentBar(allAlc))
    , manager(new AlcoCoctailManager(allAlc, bar->getCurrentMap()))
    , editBase(new AlcoEditBase(base))
    , useCoctails(new AlcoUseCoctails(manager,allAlc,bar))
{
    ui->setupUi(this);    
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

/*void MainWindow::on_W_typeCoctail_currentIndexChanged(const QString& arg1)
{
    ui->W_coctailName->clear();
    auto it = listCoctails->begin();
    while (it != listCoctails->end()) {
        if (it->typeCoctail == arg1) {
            ui->W_coctailName->addItem(it->name);
        }
        ++it;
    }
}*/

void MainWindow::on_Btn_EditBase_clicked()
{
    if (editBase->isHidden()) {
        editBase->show();
    } else {
        editBase->raise();
        editBase->activateWindow();
    }
}

void MainWindow::on_Btn_useCoctail_clicked()
{
    if (useCoctails->isHidden()) {
        useCoctails->show();
    } else {
        useCoctails->raise();
        useCoctails->activateWindow();
    }
}
