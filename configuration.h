#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QString>
#include <string>
#include <vector>
#include <filemanager.h>
#include <wordprocessor.h>
#define NUMBER_OF_ITEMS 6

struct Configuraion
{
    QString default_font_color;
    int default_font_size;
    int startup_behaviour;
    QString special_words_directory;
    QString background_directory;
    QString last_Opened_File;


    //default constructor
    Configuraion()
    {
        default_font_color = "-";
        default_font_size  = 14;
        startup_behaviour  = 0;
        special_words_directory = "-";
        last_Opened_File   = "-";
        background_directory = "-";
    }

    //parametrized constructor
    Configuraion(QString dfc, int dfs,  int strt, QString swd, QString lop, QString bd)
    {
        default_font_color = dfc;
        default_font_size  = dfs;
        startup_behaviour  = strt;
        special_words_directory = swd;
        last_Opened_File   = lop;
        background_directory = bd;
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
        this->background_directory = temp.background_directory;
    }

    static Configuraion loadConfiguraion(QString directory)
    {
        QString content = FileManager::getFileContent(directory);
        std::vector<QString> lines = WordProcessor::split(content, '\n');

        if(lines.size()< NUMBER_OF_ITEMS) //file is corrupted or not found
        {
            Configuraion defaultConfig = Configuraion();
            saveConfig(directory,defaultConfig); //fix and rewrite file
            return defaultConfig;
        }

        try     //Could use better error handling
        {
            QString dfc = lines[0];
            int dfs = stoi(lines[1].toStdString());
            int strt = stoi(lines[2].toStdString());
            QString swd = lines[3];
            QString lop = lines[4];
            QString bd = lines[5];

            return Configuraion(dfc,dfs,strt,swd,lop,bd);
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
        content += config.background_directory;                                             content+='\n';

        return FileManager::writeToFile(directory, content);
    }
    static bool saveConfig(Configuraion config)
    {
        QString directory = FileManager::get_config_path();
        return saveConfig(directory, config);
    }

    std::string toString()
    {
        return default_font_color.toStdString() + "\n"
        + std::to_string(default_font_size) + "\n"
        + std::to_string(startup_behaviour) + "\n"
        + special_words_directory.toStdString() + "\n"
        + background_directory.toStdString() + "\n"
        + last_Opened_File.toStdString() + "\n";
    }

    //comparison operator - checks if all field are equal
    bool operator==(Configuraion& secondWin)
    {
        return(this->default_font_color == secondWin.default_font_color &&
               this->default_font_size == secondWin.default_font_size && 
               this->startup_behaviour == secondWin.startup_behaviour &&
               this->special_words_directory == secondWin.special_words_directory &&
               this->background_directory == secondWin.background_directory &&
               this->last_Opened_File == secondWin.last_Opened_File);
    } 
};

#endif // CONFIGURATION_H

