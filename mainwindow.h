#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QMainWindow>

#include<QFile>
#include<QFileDialog>
#include<QTextStream>
#include<QMessageBox>
#include <fstream>
#include <QTimer>

#include"configuration.h"
#include"wordprocessor.h"
#include"filemanager.h"



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; class SettingWindow; }
QT_END_NAMESPACE



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static Configuraion& getCurrentConfiguration();


private slots:
    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionRedFont_triggered();

    void on_actionWhiteFont_triggered();

    void on_actionBlackFont_triggered();

    void on_actionYellowFont_triggered();

    void on_actionGreenFont_triggered();

    void on_actionBlueFont_triggered();

    void on_comboBox_activated(int index);

    void on_fontComboBox_currentFontChanged(const QFont &f);

    void on_comboBox_Font_Size_currentIndexChanged(int index);

    void on_actionSettings_triggered();

private:
    Ui::MainWindow *ui;
    QString currentFile = "";
    static Configuraion currentConfiguration;
    WordProcessor wordProcessor;
    int timerId;
    void applyConfiguration(Configuraion);
    void loadSpecialWords(QString);
    void openFile(QString);
    void setTextEditBgColor(QString);
    void setTextEditBgImage(QString);
protected:
    void timerEvent(QTimerEvent *event);
};
#endif // MAINWINDOW_H
