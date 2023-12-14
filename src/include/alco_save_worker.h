#ifndef ALCOSAVEWORKER_H
#define ALCOSAVEWORKER_H

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QStandardPaths>
#include <QTextStream>
#include <alco_item.h>

class AlcoSaveWorker : public QObject {
    Q_OBJECT
public:
    AlcoSaveWorker(
        const QString& name = QStandardPaths::standardLocations(QStandardPaths::AppDataLocation).first()
            + QDir().separator() + "currentBar.save",
        QObject* par = nullptr);
    void reloadSave();
    void readSave();
    void setNameSave(const QString& value);
    bool contains(const QString& value);
    bool changeValue(const QString& type, const QString& name, int value);
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
