#include "wordprocessor.h"
WordProcessor::WordProcessor()
{

}
void WordProcessor::setWorkingElement(QTextEdit* textEdit)
{
    this->workingElement = textEdit;
}

void WordProcessor::colorFormatText()
{
    std::string text = workingElement->toPlainText().toStdString();
    std::string buffer = "";
    int totalLength = text.length();
    for(int i=0; i<totalLength-1; i++)
    {
        if(!isalpha(text[i]))
        {
            if(std::find(blueList.begin(), blueList.end(), buffer) != blueList.end())
            {
                int begin = i-buffer.length();
                int end   = i;
                colorSection(begin,end,"blue");
            }
            else if(std::find(redList.begin(), redList.end(), buffer) != redList.end())
            {
                int begin = i-buffer.length();
                int end   = i;
                colorSection(begin,end,"red");
            }
            else if(std::find(orangeList.begin(), orangeList.end(), buffer) != orangeList.end())
            {
                int begin = i-buffer.length();
                int end   = i;
                colorSection(begin,end,"orange");
            }
            else if(std::find(greenList.begin(), greenList.end(), buffer) != greenList.end())
            {
                int begin = i-buffer.length();
                int end   = i;
                colorSection(begin,end,"green");
            }
            buffer = "";
            continue;
        }
        buffer += text[i];

    }
}

void WordProcessor::colorSection(int begin, int end, QString color)
{
    QTextCharFormat fmt;
    fmt.setForeground(QColor(color));

    QTextCursor cursor(workingElement->document());
    cursor.setPosition(begin, QTextCursor::MoveAnchor);
    cursor.setPosition(end, QTextCursor::KeepAnchor);
    cursor.setCharFormat(fmt);
}

void WordProcessor::addWordToList(std::string word, int listIndex)
{
    if(listIndex==0)
        blueList.push_back(word);
    else if(listIndex==1)
        redList.push_back(word);
    else if(listIndex==2)
        orangeList.push_back(word);
    else if(listIndex==3)
        greenList.push_back(word);
}

void WordProcessor::testFillColorLists()
{
    //fill blue list
    blueList.push_back("int");
    blueList.push_back("double");
    blueList.push_back("float");

    //fill red list
    redList.push_back("return");

    //fill green list
    greenList.push_back("green");
}
