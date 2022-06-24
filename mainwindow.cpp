#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //make the text editor take full screen
    this->setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow()
{
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

