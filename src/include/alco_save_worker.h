#ifndef ALCOSAVEWORKER_H
#define ALCOSAVEWORKER_H

#include <QFile>
#include <QTextCodec>
#include <QTextStream>

#include <alco_item.h>

class AlcoSaveWorker : public QObject {
    Q_OBJECT
public:
    AlcoSaveWorker(const QString& name = "alco.base", QObject* par = nullptr);
    void reloadSave();
    void readSave();
    void setNameSave(const QString& value);
    bool contains(const QString& value);
    bool changeValue(const QString& type, const QString &name, int value);
    void setMap(const AlcoMap& value);
    AlcoMap* getMap();

private:
    QString nameSave;
    QFile* save;
    AlcoMap map;
signals:
    void changed();
};

#endif // ALCOSAVEWORKER_H
