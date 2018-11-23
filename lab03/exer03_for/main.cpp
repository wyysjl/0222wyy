#include "mainwidget.h"
#include <QApplication>
#include <QDateTime>

int main(int argc, char *argv[])
{

    qRegisterMetaType< QList<QDateTime> >("QList<QDateTime>");

    qDebug()<<QDateTime::currentDateTime();

    QApplication a(argc, argv);
    mainWidget w;
    w.show();

    return a.exec();
}
