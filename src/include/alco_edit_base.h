#ifndef ALCO_EDIT_BASE_H
#define ALCO_EDIT_BASE_H

#include <QListWidget>
#include <QMenu>
#include <QVBoxLayout>
#include <QWidget>

#include <alco_item.h>
#include <alco_base_worker.h>
#include <qdynamicgridlayout.h>

struct AlcoEditBaseItem {
    AlcoEditBaseItem()
        : lay(nullptr)
        , w(nullptr)
        , catName(nullptr)
    {}
    AlcoEditBaseItem(const QString& name, const AlcoList& list)
        : lay(new QVBoxLayout())
        , w(new QListWidget())
        , catName(new QLineEdit())
    {
        w->setContextMenuPolicy(Qt::CustomContextMenu);
        lay->addWidget(catName);
        lay->addWidget(w);
        catName->setText(name);
        for (const auto& item : qAsConst(list)) {
            QListWidgetItem* witem = new QListWidgetItem(item->getData()->name);
            witem->setFlags(witem->flags () | Qt::ItemIsEditable);
            w->addItem(witem);
        }
    }
    QVBoxLayout* lay;
    QListWidget* w;
    QLineEdit* catName;
};

namespace Ui {
class AlcoEditBase;
}

class AlcoEditBase : public QWidget {
    Q_OBJECT

public:
    explicit AlcoEditBase(AlcoBaseWorker* _baseWorker, QWidget* parent = nullptr);
    ~AlcoEditBase();
private slots:
    void on_Btn_AddCategory_clicked();

    void on_Btn_Save_clicked();

private:
    QVBoxLayout* addCategory(const QString& name, const AlcoList& list);
    void addRow();
    void showContextMenu(const QPoint& pos);
    void addItem();
    void removeItem();
    void removeCategory();
private:
    Ui::AlcoEditBase* ui;
    QDynamicGridLayout* lay;
    AlcoBaseWorker* baseWorker;
    AlcoMap* base;
    QList<AlcoEditBaseItem*> listCategory;
};

#endif // ALCO_EDIT_BASE_H
