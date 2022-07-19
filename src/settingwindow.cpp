#include "settingwindow.h"
#include "ui_settingwindow.h"


SettingWindow::SettingWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingWindow)
{
    ui->setupUi(this);

    ui->checkBox_highlight->setChecked(false);
    ui->label_4->setDisabled(true);
    ui->lineEdit_specia_words_dir->setDisabled(true);
    ui->pushButton_select_sw_dir->setDisabled(true);
}


SettingWindow::~SettingWindow()
{
    delete ui;
}

void SettingWindow::on_checkBox_highlight_stateChanged(int arg1)
{
    bool state = ! ui->checkBox_highlight->isChecked();
    ui->label_4->setDisabled(state);
    ui->lineEdit_specia_words_dir->setDisabled(state);
    ui->pushButton_select_sw_dir->setDisabled(state);
}


void SettingWindow::on_cancelButton_clicked()
{
    close();
}


void SettingWindow::on_okButton_clicked()
{
    QString configPath = FileManager::get_config_path();
    gather_config_attributes();


    close();
}

void SettingWindow::gather_config_attributes()
{
    //TODO: gather values from ui and store in tempConfig
}


void SettingWindow::on_resetButton_clicked()
{
    //TODO: reset settings to default: use default constructor of Configuration class
}

