#include "alco_edit_base.h"
#include "ui_alco_edit_base.h"

AlcoEditBase::AlcoEditBase(AlcoBaseWorker* _baseWorker, QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::AlcoEditBase)
    , lay(new QDynamicGridLayout(4))
    , baseWorker(_baseWorker)
    , base(baseWorker->getMapAlco())
{
    ui->setupUi(this);
    auto it = base->begin();
    while (it != base->end()) {
        auto layn = addCategory(it.key(), it.value());
        lay->add(layn);
        ++it;
    }
    ui->lay_scroll->addLayout(lay);
}

AlcoEditBase::~AlcoEditBase() { delete ui; }

QVBoxLayout* AlcoEditBase::addCategory(const QString& name, const AlcoList& list)
{
    AlcoEditBaseItem* item = new AlcoEditBaseItem(name, list);
    connect(
        item->w, &QListWidget::customContextMenuRequested, this, &AlcoEditBase::showContextMenu);

    listCategory << item;

    return item->lay;
}

void AlcoEditBase::showContextMenu(const QPoint& pos)
{
    QListWidget* list = qobject_cast<QListWidget*>(sender());
    if (list == nullptr) {
        return;
    }
    QPoint gpos = list->mapToGlobal(pos);
    QMenu menu;
    menu.addAction("Удалить элемент", this, &AlcoEditBase::removeItem);
    menu.addAction("Добавить элемент", this, &AlcoEditBase::addItem);
    menu.addAction("Удалить категорию", this, &AlcoEditBase::removeCategory);
    menu.exec(gpos);
}

void AlcoEditBase::addItem()
{
    QListWidget* list = qobject_cast<QListWidget*>(focusWidget());
    if (list == nullptr) {
        return;
    }
    QListWidgetItem* witem = new QListWidgetItem("NoName");
    witem->setFlags(witem->flags() | Qt::ItemIsEditable);
    list->addItem(witem);
}

void AlcoEditBase::removeItem()
{
    QListWidget* list = qobject_cast<QListWidget*>(focusWidget());
    if (list == nullptr) {
        return;
    }
    for (int i = 0; i < list->selectedItems().size(); ++i) {
        // Get curent item on selected row
        QListWidgetItem* item = list->selectedItems()[i];
        // And remove it
        delete item;
    }
}

void AlcoEditBase::removeCategory()
{    
    QListWidget* list = qobject_cast<QListWidget*>(focusWidget());
    if (list == nullptr) {
        return;
    }
    AlcoEditBaseItem* searched;
    for (auto& item : listCategory) {
        if (item->w == list) {
            searched = item;
        }
    }
    int ret = QMessageBox::warning(this, "Предупрждение о удаление категории",
        "Вы действительно хотите удалить всю категорию " + searched->catName->text(),
        QMessageBox::Yes | QMessageBox::No);
    if(ret == QMessageBox::No) {
        return;
    }
    listCategory.removeOne(searched);
    searched->w->deleteLater();
    searched->catName->deleteLater();
    searched->lay->deleteLater();
    delete searched;
}

void AlcoEditBase::on_Btn_AddCategory_clicked() { lay->add(addCategory("", {})); }

void AlcoEditBase::on_Btn_Save_clicked()
{

    base->clear();
    for (auto& item : listCategory) {
        QString type = item->catName->text();
        base->operator[](type) = AlcoList();
        for (int i = 0; i < item->w->count(); i++) {
            base->operator[](type) << new AlcoItem({ item->w->item(i)->text(), "", 0, 0 }, type);
        }
    }
    baseWorker->saveBase();
}
