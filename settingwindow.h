#ifndef SETTINGWINDOW_H
#define SETTINGWINDOW_H

#include "configuration.h"
#include "mainwindow.h"
#include <QDialog>

namespace Ui {
class SettingWindow;
}

class SettingWindow : public QDialog
{
    Q_OBJECT

public:
    Configuraion tempConfig;

    explicit SettingWindow(QWidget *parent = nullptr);
    ~SettingWindow();

private slots:
    void on_checkBox_highlight_stateChanged(int arg1);

    void on_cancelButton_clicked();

    void on_okButton_clicked();

    void on_resetButton_clicked();

private:
    Ui::SettingWindow *ui;
    void gather_config_attributes();
    void dump_config_attributes(Configuraion);

};

#endif // SETTINGWINDOW_H
