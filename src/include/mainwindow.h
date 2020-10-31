#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <alco_base_worker.h>
#include <alco_item.h>
#include <alco_current_bar.h>
#include <alco_cocktail_manager.h>
#include <alco_edit_base.h>
#include <alco_use_coctails.h>

#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QTableWidget>
#include <QComboBox>
#include <QMessageBox>

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
    void on_Btn_useCoctail_clicked();

private slots:


    void on_Btn_OpenBar_clicked();

    void on_Btn_OpenCoctailManager_clicked(); 

    void on_Btn_EditBase_clicked();

private:
    Ui::MainWindow* ui;    
    AlcoBaseWorker* base;
    AlcoMap* allAlc;
    AlcoCurrentBar* bar;
    AlcoCoctailManager* manager;
    AlcoEditBase* editBase;
    AlcoUseCoctails* useCoctails;



};
#endif // MAINWINDOW_H
