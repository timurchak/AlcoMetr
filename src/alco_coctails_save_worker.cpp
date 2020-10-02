#include "alco_coctails_save_worker.h"

AlcoCoctailsSaveWorker::AlcoCoctailsSaveWorker(const QString& name)
    : fileName(name)
    , save(new QFile(fileName))
{
}

void AlcoCoctailsSaveWorker::setList(QList<AlcoCoctail>* value) { list = value; }

void AlcoCoctailsSaveWorker::readSave()
{
    if (save->open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream ts(save);
        ts.setCodec("Windows-1251");
        list->clear();
        while (!ts.atEnd()) {
            auto splitStart = ts.readLine().split(" ", Qt::SkipEmptyParts);
            if (splitStart.size() < 3) {
                save->close();
                return;
            }
            if (splitStart[0] == "Start") {
                QString name = splitStart[2];
                QString about = "";
                QString typeCoctail = "";
                int count = 0;
                auto splitAbout = ts.readLine().split(" ", Qt::SkipEmptyParts);

                if (splitAbout[0] == "about:") {
                    if (splitAbout.size() < 2) {
                        about = "None";
                    } else {
                        about = splitAbout[1];
                    }
                } else {
                    save->close();
                    return;
                }
                auto splitType = ts.readLine().split(" ", Qt::SkipEmptyParts);
                if (splitType.size() < 2) {
                    save->close();
                    return;
                }
                if (splitType[0] == "typeCoctail:") {
                    typeCoctail = splitType[1];
                } else {
                    save->close();
                    return;
                }
                auto splitCount = ts.readLine().split(" ", Qt::SkipEmptyParts);
                if (splitCount.size() < 3) {
                    save->close();
                    return;
                }
                if (splitCount[0] == "count") {
                    count = splitCount[2].toInt();
                }
                AlcoCoctail coctail;
                coctail.name = name;
                coctail.about = about;
                coctail.typeCoctail = typeCoctail;
                for (int i = 0; i < count; i++) {
                    auto split = ts.readLine().split("|", Qt::SkipEmptyParts);
                    if (split.count() < 3) {
                        continue;
                    }
                    coctail.items << new AlcoItem({ split[1], "", split[2].toInt(), 0 }, split[0]);
                }
                list->push_back(coctail);
            }
        }
        save->close();
    }
}

void AlcoCoctailsSaveWorker::saveList()
{
    if (save->open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream ts(save);
        ts.setCodec("Windows-1251");
        auto it = list->begin();
        while (it != list->end()) {
            auto strList = it->toString();
            for (auto const& item : qAsConst(strList)) {
                ts << item;
            }
            ++it;
        }
        save->close();
    }
}

QList<AlcoCoctail>* AlcoCoctailsSaveWorker::getList() const { return list; }
