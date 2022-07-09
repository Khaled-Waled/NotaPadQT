#include "mainwindow.h"
#include "./ui_mainwindow.h"

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

void MainWindow::openFile(QString directory)
{
    if(directory=="") return;
    currentFile = directory;
    QString text = FileManager::getFileContent(currentFile);
    if(text=="")
    {
        QMessageBox::warning(this, "No content" ,"Empty File, an error may have occured");
    }
    ui->textEdit->setText(text);
    setWindowTitle(currentFile);
}


void MainWindow::on_actionOpen_triggered()
{
    QString directory = QFileDialog::getOpenFileName(this, "Select the File");
    openFile(directory);
}

void MainWindow::on_actionSave_triggered()
{
    QString fileDir = QFileDialog::getSaveFileName(this, "Select Location");
    QString content = ui->textEdit->toPlainText();  //get content from screen
    if(!FileManager::writeToFile(currentFile, content))
    {
        QMessageBox::warning(this, "Save Failed", "Can't access "+ fileDir);
        return;
    }
    currentFile = fileDir;
    setWindowTitle(currentFile);
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
    if(directory == "") return;

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
    //Set up the pointer
    QTextEdit* textEdit = ui->textEdit;

    //Font Color
    if(config.default_font_color!="")
        textEdit->setTextColor(config.default_font_color);

    //Font Size
    ui->textEdit->setFontPointSize(config.default_font_size);

    //set up startup_behaviour
    QString directory;
    switch(config.startup_behaviour)
    {
    case 0:         //open new file
        textEdit->setText("");
        break;
    case 1:         //open Last File
        directory = QString::fromStdString(config.last_Opened_File);
        openFile(directory);
        break;
    case 2:         //show select file screen
        directory = QFileDialog::getOpenFileName(this, "Select the File");
        openFile(directory);
        break;
    default:
        textEdit->setText("");
    }

    //Special Words
    if(config.special_words_directory!="")
        loadSpecialWords(config.special_words_directory);
}

