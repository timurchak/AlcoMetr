#ifndef ALCOITEM_H
#define ALCOITEM_H

#include <QLabel>
#include <QLineEdit>
#include <QObject>
#include <QSpinBox>
#include <string>

struct AlcoLine {
    /*QString toString(const QString& type) const
    {
        return QString("%1|%2|%3|%4|%5\n").arg(type).arg(name).arg(company).arg(volume).arg(volumeBottle);
    }*/
    QString name;
    QString company;
    int volume;
    int volumeBottle;
};

class AlcoItem : public QObject {
    Q_OBJECT
public:
    AlcoItem(AlcoLine line, const QString& type, QObject* par = nullptr);
    QString toString();
    AlcoLine* getData();
    void reloadData();
public slots:
    void companyChange(QString);
    void changeValue(int);

public:
    QLabel* name;
    QLineEdit* company;
    QSpinBox* volume;
    QSpinBox* volumeBottle;
    QLabel* per;

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
    bool valid = false;
    friend bool operator==(const AlcoCoctail& lhs, const AlcoCoctail& rhs) { return lhs.name == rhs.name; }
};
#endif // ALCOITEM_H
