#ifndef ALCOITEM_H
#define ALCOITEM_H

#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QObject>
#include <QSpinBox>
#include <QTextStream>
#include <string>
const QColor yellowColor(238, 255, 77);
const QColor redColor(182, 11, 6);
const QColor greenColor(71, 177, 71);
struct AlcoLine {
    /*QString toString(const QString& type) const
    {
        return
    QString("%1|%2|%3|%4|%5\n").arg(type).arg(name).arg(company).arg(volume).arg(volumeBottle);
    }*/
    QString name;
    QString company;
    int volume;
    int volumeBottle;
    bool st;
};

class AlcoItem : public QObject {
    Q_OBJECT
public:
    AlcoItem(AlcoLine line, const QString& type, QObject* par = nullptr);
    QString toString();
    QString toShortString();
    AlcoLine* getData();
    void reloadData();
    QString getTypeAlco() const;
    void setTypeAlco(const QString& value);
public slots:
    void companyChange(QString);
    void changeValue(int);
private slots:
    void clickEnable(bool st);

public:
    QLabel* name;
    QLineEdit* company;
    QSpinBox* volume;
    QSpinBox* volumeBottle;
    QLabel* per;
    QCheckBox* enable;

private:
    AlcoLine data;
    QString typeAlco;

private:
};
using AlcoList = QList<AlcoItem*>;
using AlcoMap = QMap<QString, AlcoList>;

struct AlcoCoctail {
    QString name;
    AlcoList items;
    QString about;
    QString typeCoctail;
    bool valid = false;
    friend bool operator==(const AlcoCoctail& lhs, const AlcoCoctail& rhs)
    {
        return lhs.name == rhs.name;
    }
    QStringList toString()
    {
        QStringList list;
        list << "Start Coctail: " + name + "\n";
        list << "about: " + about + "\n";
        list << "typeCoctail: " + typeCoctail + "\n";
        list << "count items: " + QString::number(items.count()) + "\n";
        for (auto const& item : std::as_const(items)) {
            list << item->toShortString();
        }
        return list;
    }
};
#endif // ALCOITEM_H
