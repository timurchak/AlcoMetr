#ifndef ALCOBASEWORKER_H
#define ALCOBASEWORKER_H

#include <QFile>
#include <QMap>
#include <QString>
#include <QStringList>
#include <QTextStream>
#include <QStandardPaths>
#include <QDir>

#include <alco_item.h>

class AlcoBaseWorker {
public:
    AlcoBaseWorker(const QString& _name = QStandardPaths::standardLocations(QStandardPaths::AppDataLocation).first()
                                         + QDir().separator() + "alco.list");
    void readBase(const QString &name);

    void readBase();

    void saveBase();

    AlcoMap *getMapAlco();

private:
    QString name;
    QFile* base;
    AlcoMap* mapAlco;
};

#endif // ALCOBASEWORKER_H
