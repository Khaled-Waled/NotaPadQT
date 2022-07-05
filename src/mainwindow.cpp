#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <fstream>

#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //this->setCentralWidget(ui->textEdit); //make the textEdit take full screen (not the intended behaviour)
    this->wordProcessor = WordProcessor();
    this->wordProcessor.setWorkingElement(ui->textEdit);
    timerId = startTimer(1000);
}

MainWindow::~MainWindow()
{
    killTimer(timerId);
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{
    currentFile.clear();
    ui->textEdit->setText("");
    setWindowTitle("NotaPadQT");
}


void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Select the File");
    QFile file(fileName);
    //Try to open file in read only state and get text
    if(!file.open(QIODevice::ReadOnly | QFile::Text))
    {
        //if failed
        QMessageBox::warning(this, "Open Failed", "Can't open "+ fileName+"\n"+file.errorString());
        return;
    }

    currentFile = fileName;
    QTextStream inStream(&file);       //get text stream
    QString text = inStream.readAll(); //stream to string
    ui->textEdit->setText(text);       //pass file content to screen
    setWindowTitle(fileName);
    file.close();
}

void MainWindow::on_actionSave_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Select Location");
    QFile file(fileName);
    //Try to write file
    if(!file.open(QIODevice::WriteOnly | QFile::Text))
    {
        //if failed
        QMessageBox::warning(this, "Save Failed", "Can't access "+ fileName+"\n"+file.errorString());
        return;
    }

    currentFile = fileName;
    QTextStream outStream(&file);                //set text stream
    QString text = ui->textEdit->toPlainText();  //get content from screen
    outStream<<text;                             //write to file
    setWindowTitle(fileName);
    file.close();
}

void MainWindow::on_actionRedFont_triggered()
{
    QTextEdit* textEdit = ui->textEdit;
    textEdit->setTextColor(QColor("red"));
}

void MainWindow::on_actionWhiteFont_triggered()
{
    QTextEdit* textEdit = ui->textEdit;
    textEdit->setTextColor(QColor("white"));
}

void MainWindow::on_actionBlackFont_triggered()
{
    QTextEdit* textEdit = ui->textEdit;
    textEdit->setTextColor(QColor("black"));
}

void MainWindow::on_actionYellowFont_triggered()
{
    QTextEdit* textEdit = ui->textEdit;
    textEdit->setTextColor(QColor("yellow"));
}

void MainWindow::on_actionGreenFont_triggered()
{
    QTextEdit* textEdit = ui->textEdit;
    textEdit->setTextColor(QColor("green"));
}

void MainWindow::on_actionBlueFont_triggered()
{
    QTextEdit* textEdit = ui->textEdit;
    textEdit->setTextColor(QColor("blue"));
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    wordProcessor.colorFormatText();
}


void MainWindow::on_comboBox_activated(int index)
{
    QString color = ui->comboBox->currentText();
    ui->textEdit->setTextColor(QColor(color));
}


void MainWindow::on_fontComboBox_currentFontChanged(const QFont &font)
{
    QTextEdit* textEdit = ui->textEdit;
    textEdit->setFontFamily(font.family());
}


void MainWindow::on_comboBox_Font_Size_currentIndexChanged(int index)
{
    QString text = ui->comboBox_Font_Size->currentText();
    int fontSize = stoi(text.toStdString());
    ui->textEdit->setFontPointSize(fontSize);
}

void MainWindow::loadSpecialWords(std::string directory)
{
    std::ifstream file(directory);
    std::string line;

    char delimiter = '$';
    std::string buffer = "";

    int num = 0;
    const int maxNum = WordProcessor::NUMBER_OF_COLOR_LISTS;
    while (num < maxNum && file >> line)
    {
        for(auto c : line)
        {
            if(c!=delimiter)
                buffer+=c;
            else
            {
                wordProcessor.addWordToList(buffer, num);
                buffer="";
            }
        }
        if (buffer != "" && buffer != " "|| buffer!=std::string(1,delimiter))
        {
            wordProcessor.addWordToList(buffer, num);
            buffer="";
        }
        num++;
    }


}

void MainWindow::applyConfiguration(Configuraion config)
{
    QTextEdit* textEdit = ui->textEdit;
    textEdit->setTextColor(config.default_font_color);
    ui->textEdit->setFontPointSize(config.default_font_size);

    //TODO: startup_behaviour
    switch(config.startup_behaviour)
    {
    case 0:
        break;
    default:
        break;
    }

    loadSpecialWords(config.special_words_directory);
}

