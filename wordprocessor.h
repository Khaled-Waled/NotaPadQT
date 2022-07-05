#ifndef WORDPROCESSOR_H
#define WORDPROCESSOR_H

#include <QTextEdit>
#include <string>
#include <vector>



class WordProcessor
{
private:
    std::vector<std::string> blueList;
    std::vector<std::string> redList;
    std::vector<std::string> orangeList;
    std::vector<std::string> greenList;
    QTextEdit* workingElement;

public:
    const static int NUMBER_OF_COLOR_LISTS = 4;
    WordProcessor();
    void setWorkingElement(QTextEdit*);
    void colorFormatText();
    void colorSection(int,int,QString);
    void addWordToList(std::string, int);
    void testFillColorLists();
};

#endif // WORDPROCESSOR_H
