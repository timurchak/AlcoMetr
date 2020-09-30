#include "include/alco_base_worker.h"
bool variantLessThan(AlcoItem* v1, AlcoItem* v2) { return v1->name->text() < v2->name->text(); }

AlcoBaseWorker::AlcoBaseWorker(const QString &name)
    : base(new QFile(name))
{
    readBase();
}

void AlcoBaseWorker::readBase()
{
    if(base->open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream ts(base);
        ts.setCodec("Windows-1251");
        QString lastKey = "";
        while(!ts.atEnd()) {
            auto line = ts.readLine();
            if(line.contains("==")) {
                lastKey = line.remove("==");
                mapAlco[lastKey] = QList<AlcoItem*>();
                continue;
            }
            if(lastKey.isEmpty()) {
                continue;
            }
            mapAlco[lastKey] << new AlcoItem({line, "",0,0}, lastKey);
        }
        base->close();
    }
    auto it = mapAlco.begin();
    while (it != mapAlco.end()) {
        std::sort(it.value().begin(), it.value().end(), variantLessThan);
        ++it;
    }
}

AlcoMap AlcoBaseWorker::getMapAlco() const
{
    return mapAlco;
}
