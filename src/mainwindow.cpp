#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , base(new AlcoBaseWorker(":/rsc/alco.list"))
    , allAlc(base->getMapAlco())
    , bar(new AlcoCurrentBar(allAlc))
    , manager(new AlcoCocktailManager(allAlc, bar->getCurrentMap()))
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
