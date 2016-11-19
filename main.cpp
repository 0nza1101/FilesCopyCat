#include <iostream>
#include <QtCore>
#include <QCoreApplication>
#include <QSharedPointer>
#include <QDebug>

#include "copy.h"

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QSharedPointer<Copy> copy(new Copy(&a));
    QObject::connect(copy.data(), SIGNAL(finished()), &a, SLOT(quit()));
    QTimer::singleShot(0, copy.data(), SLOT(run()));

    return a.exec();
}
