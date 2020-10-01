#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <alco_base_worker.h>
#include <alco_item.h>
#include <alco_current_bar.h>
#include <alco_cocktail_manager.h>

#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QTableWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:


    void on_Btn_OpenBar_clicked();

    void on_Btn_OpenCoctailManager_clicked();

private:
    Ui::MainWindow* ui;    
    AlcoBaseWorker* base;
    AlcoMap allAlc;
    AlcoCurrentBar* bar;
    AlcoCocktailManager* manager;

};
#endif // MAINWINDOW_H