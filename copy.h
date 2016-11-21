#ifndef COPY_H
#define COPY_H

#include <QObject>
#include <QCoreApplication>
#include <QDebug>
#include <QSharedPointer>
#include <QTime>
#include <QDir>
#include <QFileInfo>
#include <QFile>
#include <QStringList>
#include <QElapsedTimer>
#include <QDirIterator>
#include <QDebug>


void errorHandler(QtMsgType type, const char *msg);

class Copy : public QObject
{
    Q_OBJECT
private:

public:
    explicit Copy(QObject *parent = 0);
    void scanDir(QString dir);
    bool copyFileToRoot(QString sourceFilePath, QString fileName);
    bool copy_dir_recursive(QString from_dir, QString to_dir, bool replace_on_conflit);
    bool copyDirToRoot(QString sourceDir);
    void quit();
    //~Copy(); //Destructor

signals:
    void finished();

public slots:
    void run();


};

#endif // COPY_H
