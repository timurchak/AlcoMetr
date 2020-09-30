#ifndef ALCOBASEWORKER_H
#define ALCOBASEWORKER_H

#include <QFile>
#include <QMap>
#include <QString>
#include <QStringList>
#include <QTextStream>

#include <alco_item.h>

class AlcoBaseWorker {
public:
    AlcoBaseWorker(const QString& name);
    void readBase();

    AlcoMap getMapAlco() const;

private:
    QFile* base;
    AlcoMap mapAlco;
};

#endif // ALCOBASEWORKER_H
