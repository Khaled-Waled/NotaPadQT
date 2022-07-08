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
};

#endif // FILEMANAGER_H
