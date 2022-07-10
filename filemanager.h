#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QString>
#include <QFile>
#include <QTextStream>



class FileManager
{
public:
    FileManager();
    static QString getFileContent(QString);
    static bool writeToFile(QString,QString);
    static QString get_homedir();
};

#endif // FILEMANAGER_H
