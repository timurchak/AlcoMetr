#ifndef ALCO_CURRENT_BAR_H
#define ALCO_CURRENT_BAR_H

#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QTableWidget>
#include <QWidget>
#include <qdynamicgridlayout.h>

#include <alco_base_worker.h>
#include <alco_item.h>
#include <alco_save_worker.h>
#include <alco_tablewidget.h>
#include <parse_inshaker.h>

namespace Ui {
class AlcoCurrentBar;
}

class AlcoCurrentBar : public QWidget {
    Q_OBJECT

public:
    explicit AlcoCurrentBar(AlcoMap* map, QWidget* parent = nullptr);
    ~AlcoCurrentBar();
    AlcoMap* getCurrentMap() const;
    void save();

private slots:
    void on_Btn_Add_clicked();

    void on_W_typeAlc_currentIndexChanged(const QString& arg1);

    void on_Btn_Save_clicked();

    void readSaveFile();

    void reloadAlco();

    AlcoTable* addTable(const QString& name);

    void on_pushButton_clicked();

private:
    Ui::AlcoCurrentBar* ui;
    AlcoSaveWorker* saver;
    AlcoMap* alcoList;
    QDynamicGridLayout* lay;
    AlcoMap* currentMap;
    QMap<QString, AlcoTable*> tables;
    int countShowTable = 0;
};

#endif // ALCO_CURRENT_BAR_H
