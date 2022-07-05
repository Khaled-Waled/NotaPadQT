#include <QString>
#include <string>

#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#endif // CONFIGURATION_H

struct Configuraion
{
    int number_of_items = 4;
    QString default_font_color;
    int default_font_size;
    int startup_behaviour;
    std::string special_words_directory;


    //default constructor
    Configuraion()
    {
        default_font_color = "";
        default_font_size  = 14;
        startup_behaviour  = 0;
        special_words_directory = "";
    }

    //parametrized constructor
    Configuraion(QString dfc, int dfs,  int strt, std::string swd)
    {
        default_font_color = dfc;
        default_font_size  = dfs;
        startup_behaviour  = strt;
        special_words_directory = swd;
    }
};
