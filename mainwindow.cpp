#include "mainwindow.h"
#include "./ui_mainwindow.h"

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
    QString color ="";
    switch(index)
    {
    case 0:
        color = "red";
        break;

    case 1:
        color = "white";
        break;

    case 2:
        color = "black";
        break;

    default:
        color = "blue";
    }
    ui->textEdit->setTextColor(QColor(color));
}

