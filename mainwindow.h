#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include<QFile>
#include<QFileDialog>
#include<QTextStream>
#include<QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

//    void on_pushButton_clicked();

//    void on_redButton_clicked();

//    void on_whiteButton_clicked();

    void on_actionRedFont_triggered();

    void on_actionWhiteFont_triggered();

    void on_actionBlackFont_triggered();

    void on_actionYellowFont_triggered();

    void on_actionGreenFont_triggered();

private:
    Ui::MainWindow *ui;
    QString currentFile = "";
};
#endif // MAINWINDOW_H
