#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <QDir>
#include <QStandardPaths>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QDir().mkpath(QStandardPaths::standardLocations(QStandardPaths::AppDataLocation).first());
    MainWindow w;
    w.show();
    return a.exec();
}
