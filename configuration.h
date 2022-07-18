#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QString>
#include <string>
#include <vector>
#include <filemanager.h>
#include <wordprocessor.h>
#define NUMBER_OF_ITEMS 5

struct Configuraion
{
    QString default_font_color;
    int default_font_size;
    int startup_behaviour;
    QString special_words_directory;
    QString last_Opened_File;


    //default constructor
    Configuraion()
    {
        default_font_color = "";
        default_font_size  = 14;
        startup_behaviour  = 0;
        special_words_directory = "";
        last_Opened_File   = "";
    }

    //parametrized constructor
    Configuraion(QString dfc, int dfs,  int strt, QString swd, QString lop)
    {
        default_font_color = dfc;
        default_font_size  = dfs;
        startup_behaviour  = strt;
        special_words_directory = swd;
        last_Opened_File   = lop;
    }

    //Directory constructor
    Configuraion(QString directory)
    {
        Configuraion temp  = loadConfiguraion(directory);

        this->default_font_color = temp.default_font_color;
        this->default_font_size  = temp.default_font_size;
        this->startup_behaviour  = temp.startup_behaviour;
        this->special_words_directory = temp.special_words_directory;
        this->last_Opened_File   = temp.last_Opened_File;
    }

    static Configuraion loadConfiguraion(QString directory)
    {
        QString content = FileManager::getFileContent(directory);
        std::vector<QString> lines = WordProcessor::split(content, '\n');
        if(lines.size()< NUMBER_OF_ITEMS) return Configuraion();

        try     //Could use better error handling
        {
            QString dfc = lines[0];
            int dfs = stoi(lines[1].toStdString());
            int strt = stoi(lines[2].toStdString());
            QString swd = lines[3];
            QString lop = lines[4];

            return Configuraion(dfc,dfs,strt,swd,lop);
        }
        catch(...)
        {
            return Configuraion();
        }
    }

    static bool saveConfig(QString directory, Configuraion config)
    {
        QString content="";

        content += config.default_font_color;                                               content+='\n';
        content += QString::fromStdString(std::to_string(config.default_font_size));        content+='\n';
        content += QString::fromStdString(std::to_string(config.startup_behaviour));        content+='\n';
        content += config.special_words_directory;                                          content+='\n';
        content += config.last_Opened_File;                                                 content+='\n';

        return FileManager::writeToFile(directory, content);
    }
};

#endif // CONFIGURATION_H

