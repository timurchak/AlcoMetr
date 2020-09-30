#ifndef PARSEINSHAKER_H
#define PARSEINSHAKER_H
#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QObject>
#include <QXmlStreamReader>
#include <QDebug>

class ParseInShaker : public QObject {
    Q_OBJECT
public:
    ParseInShaker(QObject* par = nullptr);

    QMap<QString, QStringList> parseHTML(const QString& path);
private:
    bool parseHTMLElement(const QString& elemnt, const QString& next, const QString& attr,
                          const QString& attrName, QXmlStreamReader* reader);
    QStringList parseHTMLGroup(QXmlStreamReader* reader);
    void searchGroup(QXmlStreamReader* reader, QMap<QString, QStringList> *map);
    void startRead();
    void finishRead(QNetworkReply* reply);
    void save(QMap<QString, QStringList>& map);

private:
    QNetworkAccessManager* manager;
    QNetworkRequest* request;
    QNetworkReply* reply;
};

#endif // PARSEINSHAKER_H
