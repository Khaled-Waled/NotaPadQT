#include "settingwindow.h"
#include "ui_settingwindow.h"


SettingWindow::SettingWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingWindow)
{
    ui->setupUi(this);

    tempConfig = MainWindow::getCurrentConfiguration();
    dump_config_attributes(tempConfig);
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

void SettingWindow::on_checkBox_textEditBackground_stateChanged()
{
    //Updates user interface and configuration 
    if(ui->checkBox_textEditBackground->isChecked())
    {
        tempConfig.background_directory = ui->lineEdit_textEditBackground->text();
        ui->lable_textEditBackground->setDisabled(false);
        ui->lineEdit_textEditBackground->setDisabled(false);
        ui->pushButton_textEditBackground->setDisabled(false);
    }
    else
    {
        tempConfig.background_directory = "-";
        ui->lable_textEditBackground->setDisabled(true);
        ui->lineEdit_textEditBackground->setDisabled(true);
        ui->pushButton_textEditBackground->setDisabled(true);
    }
}


void SettingWindow::on_cancelButton_clicked()
{
    close();
}


void SettingWindow::on_okButton_clicked()
{
    QString configPath = FileManager::get_config_path();
    gather_config_attributes();
    Configuraion::saveConfig(tempConfig);
    MainWindow::getCurrentConfiguration() = tempConfig;
    close();
}

//gather values from UI and store in tempConfig
void SettingWindow::gather_config_attributes()
{
    QString color = ui->comboBox_font_color->currentText();

    QString fSizeText = ui->comboBox_font_size->currentText();
    int fSize = stoi(fSizeText.toStdString());

    int sBehaviour = ui->comboBox_start_behahvior->currentIndex();

    QString sWordsDir = "-";
    if(ui->checkBox_highlight->isChecked())
        sWordsDir = ui->lineEdit_specia_words_dir->text();

    QString lastOpened = MainWindow::getCurrentConfiguration().last_Opened_File;
    
    tempConfig = Configuraion(color,fSize, sBehaviour,sWordsDir,lastOpened, tempConfig.background_directory);
}

//Get Configuraion attributes and selecte them in the UI
void SettingWindow::dump_config_attributes(Configuraion configuration)
{
    int index = ui->comboBox_font_color->findText(configuration.default_font_color);
    if (index == -1)
        index=0;
    ui->comboBox_font_color->setCurrentIndex(index);

    index = ui->comboBox_font_size->findText(QString::number(configuration.default_font_size));
    if (index == -1)
        index=0;
    ui->comboBox_font_size->setCurrentIndex(index);

    index = ui->comboBox_start_behahvior->findText(QString::number(configuration.startup_behaviour));
    if (index == -1)
        index=0;
    ui->comboBox_start_behahvior->setCurrentIndex(index);

    if(configuration.special_words_directory[0]!='-')
    {
        ui->checkBox_highlight->setChecked(true);
        ui->lineEdit_specia_words_dir->setText(configuration.special_words_directory);
    }
    else
    {
        ui->checkBox_highlight->setChecked(false);
        ui->lineEdit_specia_words_dir->setDisabled(true);
        ui->pushButton_select_sw_dir->setDisabled(true);
    }

    //Is background directory specified?
    if(configuration.background_directory[0]!='-')
    {
        ui->checkBox_textEditBackground->setChecked(true);
        ui->checkBox_textEditBackground->setDisabled(false);
        ui->lineEdit_textEditBackground->setText(configuration.background_directory);
    }
    else
    {
        ui->checkBox_textEditBackground->setChecked(false);
        ui->lineEdit_textEditBackground->setDisabled(true);
        ui->pushButton_textEditBackground->setDisabled(true);
    }
}
//reset settings to default: use default constructor of Configuration class
void SettingWindow::on_resetButton_clicked()
{
    tempConfig = Configuraion();
    dump_config_attributes(tempConfig);
}

void SettingWindow::on_pushButton_textEditBackground_clicked()
{
    QString homeDir = FileManager::get_homedir(),
            caption = QString("Load background"),
            filter = QString("All files (*.*);;JPEG (*.jpg *.jpeg);;TIFF (*.tif);;BMP (*.bmp)");
    LoadBackgroundDialog myLoadBackgroundDialog(this, caption, homeDir, filter);
    tempConfig.background_directory = myLoadBackgroundDialog.getOpenFileName();
    ui->lineEdit_textEditBackground->setText(tempConfig.background_directory);
}

