#include "parse_inshaker.h"

ParseInShaker::ParseInShaker(QObject* par)
    : QObject(par)
    , manager(new QNetworkAccessManager(this))
    , request(new QNetworkRequest(QUrl("https://ru.inshaker.com/goods")))
{
    connect(manager, &QNetworkAccessManager::finished, this, &ParseInShaker::finishRead);
    // manager->get(*request);
}

QMap<QString, QStringList> ParseInShaker::parseHTML(const QString& path)
{
    QFile file(path);
    QStringList items;
    QMap<QString, QStringList> map;
    if (file.open(QIODevice::ReadOnly)) {
        QXmlStreamReader reader(&file);
        while (!reader.atEnd()) {
            reader.readNext();
            if (reader.isStartElement()) {
                if (reader.name() == "body") {
                    qDebug() << reader.name() << "search body, start:";
                    if (parseHTMLElement("body", "div", "id", "main", &reader)) {
                        qDebug() << reader.name() << "search div id main, start:";
                        if (parseHTMLElement("div", "div", "class", "grouped-goods common-box", &reader)) {
                            qDebug() << reader.name() << "search div class grouped-goods common-box, start:";
                            if (parseHTMLElement(
                                    "div", "div", "class", "search-results goods common-content", &reader)) {
                                qDebug() << reader.name()
                                         << "search div class search-results goods common-content, start:";
                                while (!reader.atEnd()) {
                                    searchGroup(&reader, &map);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    qDebug() << "finish parse";
    map.remove("Выпечка");
    map.remove("Добавки");
    map.remove("Домашние настойки");
    map.remove("Домашние сиропы");
    map.remove("Инструменты бармена");
    map.remove("Лед");
    map.remove("Морепродукты");
    map.remove("Настои и растворы");
    map.remove("Овощи");
    map.remove("Орехи и сухофрукты");
    map.remove("Посуда");
    map.remove("Приборы");
    map.remove("Растения");
    map.remove("Сегодня в тренде");
    map.remove("Чай и кофе");
    map.remove("Эффектная подача");
    save(map);
    return map;
}

bool ParseInShaker::parseHTMLElement(const QString& elemnt, const QString& next, const QString& attr,
    const QString& attrName, QXmlStreamReader* reader)
{
    while (!reader->atEnd()) {
        reader->readNext();
        if (reader->isEndElement()) {
            if (reader->name() == elemnt) {
                return false;
            }
        }
        if (reader->isStartElement()) {
            if (reader->name() == next) {
                if (reader->attributes().value(attr) == attrName) {
                    return true;
                }
            }
        }
    }
    return false;
}

QStringList ParseInShaker::parseHTMLGroup(QXmlStreamReader* reader)
{
    QStringList list;

    while (!reader->atEnd()) {
        reader->readNext();
        if (reader->isEndElement()) {
            if (reader->name() == "ul") {
                return list;
            }
        }
        if (reader->isStartElement()) {
            if (reader->name() == "li") {
                while (!reader->atEnd()) {
                    reader->readNext();
                    if (reader->name() == "div" && reader->attributes().value("class") == "name") {
                        list << reader->readElementText();
                        break;
                    }
                }
            }
        }
    }
    return list;
}

void ParseInShaker::searchGroup(QXmlStreamReader* reader, QMap<QString, QStringList>* map)
{
    QString groupName = "";
    if (parseHTMLElement("div", "dl", "class", "group", reader)) {
        qDebug() << reader->name() << "search dl class group, start:";
        if (parseHTMLElement("dl", "dt", "class", "head js-all-items", reader)) {
            groupName = reader->readElementText();
            qDebug() << reader->name() << "search dt class head js-all-items, text:" << groupName;
            if (parseHTMLElement("dl", "dt", "class", "body", reader)) {
                qDebug() << reader->name() << "search dt class body, start:";
                if (parseHTMLElement("dt", "ul", "class", "list", reader)) {
                    qDebug() << reader->name() << "search ul class list, start:";
                    map->operator[](groupName) = parseHTMLGroup(reader);
                    return;
                }
            }
        }
    }
}

void ParseInShaker::startRead()
{
    // auto str = reply->read;
    // qDebug() << str;
}

void ParseInShaker::finishRead(QNetworkReply* reply)
{
    qDebug() << "finish " << reply;
    QStringList list;
    if (reply->error() == QNetworkReply::NoError) {
        qDebug() << "no error  size = " << reply->size();
        qint64 lastSize = 0;
        while (lastSize <= reply->size()) {
            QByteArray str = reply->read(2000);
            lastSize += 2000;
            list << str;
        }
        qDebug() << "exit";

    } else {
        qDebug() << "Error " << reply->errorString() << " " << reply;
    }
}

void ParseInShaker::save(QMap<QString, QStringList>& map)
{
    QFile file("alco.list");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream ts(&file);
        ts.setCodec("Windows-1251");
        auto it = map.begin();
        while (it != map.end()) {
            ts << "==" + it.key() + "==" << Qt::endl;
            for(auto const& item : it.value()) {
                ts << item << Qt::endl;
            }
            ++it;
        }
        file.close();
    }
}
