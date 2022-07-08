#include "../filemanager.h"


FileManager::FileManager()
{

}

QString FileManager::getFileContent(QString directoy)
{
    QFile file(directoy);
    //Try to open file in read only state and get text
    if(!file.open(QIODevice::ReadOnly | QFile::Text))
        return ""; //if failed

    QTextStream inStream(&file);       //get text stream
    QString text = inStream.readAll(); //stream to string
    file.close();
    return text;
}

bool FileManager::writeToFile(QString directory, QString content)
{
    QFile file(directory);
    if(!file.open(QIODevice::WriteOnly | QFile::Text))
    {
        //if failed
        return false;
    }

    QTextStream outStream(&file);                //set text stream
    outStream<<content;                          //write to file
    file.close();
    return true;
}
