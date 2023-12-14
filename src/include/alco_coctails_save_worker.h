#ifndef ALCOCOCTAILSSAVEWORKER_H
#define ALCOCOCTAILSSAVEWORKER_H

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QStandardPaths>
#include <QTextStream>

#include <alco_item.h>

class AlcoCoctailsSaveWorker {
public:
    AlcoCoctailsSaveWorker(
        const QString& name = QStandardPaths::standardLocations(QStandardPaths::AppDataLocation).first()
            + QDir().separator() + "coctails.save");
    void setList(QList<AlcoCoctail>* value);
    void readSave();
    void saveList();

    QList<AlcoCoctail>* getList() const;

private:
    QString fileName;
    QFile* save;
    QList<AlcoCoctail>* list;
};

#endif // ALCOCOCTAILSSAVEWORKER_H
