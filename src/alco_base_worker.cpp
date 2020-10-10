#include "include/alco_base_worker.h"
bool variantLessThan(AlcoItem* v1, AlcoItem* v2) { return v1->name->text() < v2->name->text(); }

AlcoBaseWorker::AlcoBaseWorker(const QString& _name)
    : name(_name)
    , base(new QFile(name))
    , mapAlco(new AlcoMap)
{

    if (!base->exists()) {
        readBase(":/rsc/alco.list");
        saveBase();
    }
    readBase();
}

void AlcoBaseWorker::readBase(const QString& name)
{
    QFile f(name);
    if (f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream ts(&f);
        ts.setCodec("Windows-1251");
        QString lastKey = "";
        while (!ts.atEnd()) {
            auto line = ts.readLine();
            if (line.contains("==")) {
                lastKey = line.remove("==");
                mapAlco->insert(lastKey,AlcoList());
                continue;
            }
            if (lastKey.isEmpty()) {
                continue;
            }
            mapAlco->operator[](lastKey) << new AlcoItem({ line, "", 0, 0 }, lastKey);
        }

        f.close();
    }
    auto it = mapAlco->begin();
    while (it != mapAlco->end()) {
        std::sort(it.value().begin(), it.value().end(), variantLessThan);
        ++it;
    }
}

void AlcoBaseWorker::readBase()
{
    if (base->open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream ts(base);
        ts.setCodec("Windows-1251");
        QString lastKey = "";
        while (!ts.atEnd()) {
            auto line = ts.readLine();
            if (line.contains("==")) {
                lastKey = line.remove("==");
                mapAlco->insert(lastKey,AlcoList());
                continue;
            }
            if (lastKey.isEmpty()) {
                continue;
            }
            mapAlco->operator[](lastKey) << new AlcoItem({ line, "", 0, 0 }, lastKey);
        }

        base->close();
    }
    auto it = mapAlco->begin();
    while (it != mapAlco->end()) {
        std::sort(it.value().begin(), it.value().end(), variantLessThan);
        ++it;
    }
}

void AlcoBaseWorker::saveBase()
{
    QFile f(name);
    if(f.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream ts(&f);
        ts.setCodec("Windows-1251");
        auto it = mapAlco->cbegin();
        while(it != mapAlco->cend()) {
            ts << "==" << it.key() << "==" << Qt::endl;
            for(const auto& item : qAsConst(it.value())) {
                ts << item->getData()->name << Qt::endl;
            }
            ++it;
        }
    }
}

AlcoMap* AlcoBaseWorker::getMapAlco() { return mapAlco; }
