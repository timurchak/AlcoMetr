#ifndef ALCOCOCTAILSSAVEWORKER_H
#define ALCOCOCTAILSSAVEWORKER_H

#include <alco_item.h>
#include <QFile>
#include <QTextStream>


class AlcoCoctailsSaveWorker
{
public:
    AlcoCoctailsSaveWorker(const QString& name = "coctail.base");
    void setList(QList<AlcoCoctail> *value);
    void readSave();
    void saveList();

    QList<AlcoCoctail> *getList() const;

private:
    QString fileName;
    QFile* save;
    QList<AlcoCoctail>* list;
};

#endif // ALCOCOCTAILSSAVEWORKER_H
