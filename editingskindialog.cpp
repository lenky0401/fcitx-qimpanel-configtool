#include <QColorDialog>
#include <QDebug>
#include <QStringList>
#include <QPainter>
#include <QScrollArea>
#include <QHBoxLayout>
#include <QFile>
#include <QMessageBox>
#include <QDir>
#include <QtNetwork/QHostInfo>

#include "editingskindialog.h"
#include "ui_editingskindialog.h"

EditingSkinDialog::EditingSkinDialog(QListWidgetItem *item,
                                     QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditingSkinDialog)
{
    ui->setupUi(this);
    mItem = item;
    this->setWindowTitle("skin/"+mItem->text()+"/fcitx_skin.conf");
    copySkinConf();
    mSettings = new QSettings("/tmp/"+mItem->text() + "/fcitx_skin.conf",QSettings::IniFormat);
    mSettings->setIniCodec("UTF-8");
    loadMainConf();
}

EditingSkinDialog::~EditingSkinDialog()
{
    delete mSettings;
    delete mSkinFcitx;
    delete ui;
}

void EditingSkinDialog::loadMainConf()
{
    mSettings->beginGroup("SkinInfo");
    QString skinAuthor = mSettings->value("Author").toString();
    QString skinVersion = mSettings->value("Version").toString();
    ui->lineEditSkinAuthor->setText(skinAuthor);
    ui->lineEditSkinAuthor->setEnabled(false);
    ui->lineEditSkinVersion->setText(skinVersion);
    ui->lineEditSkinVersion->setEnabled(false);
    mSettings->endGroup();

    mSettings->beginGroup("SkinFont");
    int fontSize = mSettings->value("FontSize").toInt();
    int candFontSize = mSettings->value("CandFontSize").toInt();
    QString inputColor = mSettings->value("InputColor").toString();
    QString indexColor = mSettings->value("IndexColor").toString();
    QString firstCandColor = mSettings->value("FirstCandColor").toString();
    QString otherColor = mSettings->value("OtherColor").toString();
    ui->spinBoxInputFontSize->setValue(fontSize);
    ui->spinBoxCandFontSize->setValue(candFontSize);
    ui->pushButtonInputColor->setStyleSheet("QPushButton { background-color:  " + colorToRGB(value2color(inputColor)) +";border: none;" +"}");
    ui->pushButtonIndexColor->setStyleSheet("QPushButton { background-color:  " + colorToRGB(value2color(indexColor)) +";border: none;" +"}");
    ui->pushButtonFirstCandColor->setStyleSheet("QPushButton { background-color:  " + colorToRGB(value2color(firstCandColor)) +";border: none;" +"}");
    ui->pushButtonOtherCandColor->setStyleSheet("QPushButton { background-color:  " + colorToRGB(value2color(otherColor)) +";border: none;" +"}");
    mSettings->endGroup();

    mSettings->beginGroup("SkinInputBar");
    QString backImg = mSettings->value("BackImg").toString();
    QString tipsImg = mSettings->value("TipsImg").toString();
    int marginLeft = mSettings->value("MarginLeft").toInt();
    int marginRight = mSettings->value("MarginRight").toInt();
    int marginTop = mSettings->value("MarginTop").toInt();
    int marginBottom = mSettings->value("MarginBottom").toInt();
    QString horizontalTileMode = mSettings->value("horizontalTileMode").toString();
    QString verticalTileMode = mSettings->value("vertacalTileMode").toString();
    int inputStringPosX = mSettings->value("InputStringPosX").toInt();
    int inputStringPosY = mSettings->value("InputStringPosY").toInt();
    int outputCandPosX = mSettings->value("OutputCandPosX").toInt();
    int outputCandPosY = mSettings->value("OutputCandPosY").toInt();
    QString backArrow = mSettings->value("BackArrow").toString();
    int backArrowX = mSettings->value("BackArrowX").toInt();
    int backArrowY = mSettings->value("BackArrowY").toInt();
    QString forwardArrow = mSettings->value("ForwardArrow").toString();
    int forwardArrowX = mSettings->value("ForwardArrowX").toInt();
    int forwardArrowY = mSettings->value("ForwardArrowY").toInt();
    int adjustWidth = mSettings->value("AdjustWidth").toInt();
    int adjustHeight = mSettings->value("AdjustHeight").toInt();

    ui->lineEdit_iBackImg->setText(backImg);
    ui->lineEdit_iTipsImg->setText(tipsImg);
    ui->spinBox_iLeftMargin->setValue(marginLeft);
    ui->spinBox_iRightMargin->setValue(marginRight);
    ui->spinBox_iTopMargin->setValue(marginTop);
    ui->spinBox_iBottomMargin->setValue(marginBottom);
    if(horizontalTileMode == "Stretch")
    {
        horizontalTileModeIndex = 0;
    }
    else if(horizontalTileMode == "Repeat")
    {
        horizontalTileModeIndex = 1;
    }
    else if(horizontalTileMode == "Round")
    {
        horizontalTileModeIndex = 2;
    }
    ui->comboBox_iHorizontalTileMode->setCurrentIndex(horizontalTileModeIndex);

    if(verticalTileMode == "Stretch")
    {
        verticalTileModeIndex = 0;
    }
    else if(verticalTileMode == "Repeat")
    {
        verticalTileModeIndex = 1;
    }
    else if(verticalTileMode == "Round")
    {
        verticalTileModeIndex = 2;
    }
    ui->comboBox_iVerticalTileMode->setCurrentIndex(verticalTileModeIndex);
    ui->spinBox_iInputStringPosX->setValue(inputStringPosX);
    ui->spinBox_iInputStringPosY->setValue(inputStringPosY);
    ui->spinBox_iOutputCandPosX->setValue(outputCandPosX);
    ui->spinBox_iOutputCandPosY->setValue(outputCandPosY);
    ui->lineEdit_iBackArrow->setText(backArrow);
    ui->spinBox_iBackArrowX->setValue(backArrowX);
    ui->spinBox_iBackArrowY->setValue(backArrowY);
    ui->lineEdit_iForwardArrow->setText(forwardArrow);
    ui->spinBox_iForwardArrowX->setValue(forwardArrowX);
    ui->spinBox_iForwardArrowY->setValue(forwardArrowY);
    ui->spinBox_iAdjustHeight->setValue(adjustHeight);
    ui->spinBox_iAdjustWidth->setValue(adjustWidth);


}

void EditingSkinDialog::saveMainConf()
{
    mSettings->beginGroup("SkinFont");
    int fontSize = ui->spinBoxInputFontSize->value();
    mSettings->setValue("FontSize",fontSize);

    mSettings->sync();
}

void EditingSkinDialog::on_pushButtonInputColor_released()
{
    QColorDialog::setCustomColor(0,QRgb(0x0000FF));
    QColor color =  QColorDialog::getColor(QColor(0,0,255));
    QString str;
    if(color.isValid()){
        str.sprintf("rgb(%d,%d,%d)",color.red(), color.green(), color.blue());
        qDebug()<<color;
        qDebug()<<str;
        ui->pushButtonInputColor->setStyleSheet("QPushButton { background-color: " + str +";border: none;" +"}");
    }
}

void EditingSkinDialog::on_pushButton_ok_released()
{
    saveMainConf();
    QString  message = "sudo mv /tmp/"+ mItem->text() + "/fcitx_skin.conf  /usr/share/fcitx/skin/"+ mItem->text();
    QMessageBox::warning(this,"提醒：如果要更改皮肤编辑信息还需在终端输入以下命令",message,QMessageBox::Yes);
    this->close();
}

void EditingSkinDialog::on_pushButton_cannel_released()
{

    this->close();
}


void EditingSkinDialog::on_pushButtonIndexColor_released()
{
    QColorDialog::setCustomColor(0,QRgb(0x0000FF));
    QColor color =  QColorDialog::getColor(QColor(0,0,255));
    QString str;
    if(color.isValid()){
        str.sprintf("rgb(%d,%d,%d)",color.red(), color.green(), color.blue());
        ui->pushButtonIndexColor->setStyleSheet("QPushButton { background-color: " + str +";border: none;" +"}");
    }
}

void EditingSkinDialog::on_pushButtonFirstCandColor_released()
{
    QColorDialog::setCustomColor(0,QRgb(0x0000FF));
    QColor color =  QColorDialog::getColor(QColor(0,0,255));
    QString str;
    if(color.isValid()){
        str.sprintf("rgb(%d,%d,%d)",color.red(), color.green(), color.blue());
        ui->pushButtonFirstCandColor->setStyleSheet("QPushButton { background-color: " + str +";border: none;" +"}");
    }
}

void EditingSkinDialog::on_pushButtonOtherCandColor_released()
{
    QColorDialog::setCustomColor(0,QRgb(0x0000FF));
    QColor color =  QColorDialog::getColor(QColor(0,0,255));
    QString str;
    if(color.isValid()){
        str.sprintf("rgb(%d,%d,%d)",color.red(), color.green(), color.blue());
        ui->pushButtonOtherCandColor->setStyleSheet("QPushButton { background-color: " + str +";border: none;" +"}");
    }
}

void EditingSkinDialog::on_pushButton_menuActiveColor_released()
{
    QColorDialog::setCustomColor(0,QRgb(0x0000FF));
    QColor color =  QColorDialog::getColor(QColor(0,0,255));
    QString str;
    if(color.isValid()){
        str.sprintf("rgb(%d,%d,%d)",color.red(), color.green(), color.blue());
        ui->pushButton_menuActiveColor->setStyleSheet("QPushButton { background-color: " + str +";border: none;" +"}");
    }
}

void EditingSkinDialog::on_pushButton_menuLineColor_released()
{
    QColorDialog::setCustomColor(0,QRgb(0x0000FF));
    QColor color =  QColorDialog::getColor(QColor(0,0,255));
    QString str;
    if(color.isValid()){
        str.sprintf("rgb(%d,%d,%d)",color.red(), color.green(), color.blue());
        ui->pushButton_menuLineColor->setStyleSheet("QPushButton { background-color: " + str +";border: none;" +"}");
    }
}


void EditingSkinDialog::copySkinConf()//复制皮肤配置到本地/tmp
{
    QDir *temp = new QDir;
    bool exist = temp->exists("/tmp/"+mItem->text());
    if(!exist)
        temp->mkdir("/tmp/"+mItem->text());
    QString str;
    QFile readSkinConf("/usr/share/fcitx/skin/"+mItem->text() + "/fcitx_skin.conf");
    QFile writeSkinconf("/tmp/"+mItem->text() +"/fcitx_skin.conf");
    if(!readSkinConf.open(QIODevice::ReadOnly | QIODevice::Text))
        {
           QMessageBox::warning(this,"read","can't open",QMessageBox::Yes);
        }

    if(!writeSkinconf.open(QIODevice::ReadWrite | QIODevice::Text))
    {
       QMessageBox::warning(this,"write","can't open",QMessageBox::Yes);
    }
    QTextStream readFcitxSkinConf(&readSkinConf);
    QTextStream writeFcitxSkinConf(&writeSkinconf);

    do{
        str=readFcitxSkinConf.readLine();//读取一行
        //qDebug()<<str;
        writeFcitxSkinConf<<str<<"\n";
    } while (!str.isNull());
    readSkinConf.close();
    writeSkinconf.close();
}

QString EditingSkinDialog::colorToRGB(QColor color)
{
    QString str;
    str.sprintf("rgb(%d,%d,%d)",color.red(), color.green(), color.blue());
    return str;
}

QColor EditingSkinDialog::value2color(const QString& value)
{
    QStringList list = value.split(' ');
    if(list.size() < 3) {
        return Qt::color0;
    }

    int r = list.at(0).toInt();
    int g = list.at(1).toInt();
    int b = list.at(2).toInt();
    return QColor(r, g, b);
}
