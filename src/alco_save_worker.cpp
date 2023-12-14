#include "alco_save_worker.h"

AlcoSaveWorker::AlcoSaveWorker(const QString& name, QObject* par)
    : QObject(par)
    , nameSave(name)
    , save(new QFile(name))
{
    qDebug() << "Path to save current alco:" << nameSave;
}

void AlcoSaveWorker::reloadSave()
{
    if (save->open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream ts(save);
        ts.setEncoding(QStringConverter::Utf8);
        auto it = map.begin();
        while (it != map.end()) {
            for (auto const& item : std::as_const(it.value())) {
                ts << item->toString();
            }
            ++it;
        }
        save->close();
    }
}

void AlcoSaveWorker::readSave()
{
    if (save->open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream ts(save);
        ts.setEncoding(QStringConverter::Utf8);
        map.clear();
        while (!ts.atEnd()) {
            QString str = ts.readLine();
            auto split = str.split("|", Qt::SkipEmptyParts);
            if (split.size() > 4) {
                map[split[0]] << new AlcoItem(
                    { split[1], split[2], split[3].toInt(), split[4].toInt(),
                        split.size() > 5 ? split[5] == "T" : true },
                    split[0]);
            }
        }
        save->close();
    }
}

void AlcoSaveWorker::setNameSave(const QString& value)
{
    if (save->isOpen()) {
        save->close();
    }
    nameSave = value;
    save->setFileName(nameSave);
}

bool AlcoSaveWorker::contains(const QString& value) { return map.contains(value); }

bool AlcoSaveWorker::changeValue(const QString& type, const QString& name, int value)
{
    if (!contains(type)) {
        return false;
    }
    for (auto& item : map[type]) {
        if (item->getData()->name == name) {
            item->volume->setValue(value);
            item->changeValue(0);
            return true;
        }
    }
    return false;
}

void AlcoSaveWorker::setMap(const AlcoMap& value) { map = value; }

AlcoMap* AlcoSaveWorker::getMap() { return &map; }
