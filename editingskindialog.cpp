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
#include "passwarddialog.h"
#include "ui_editingskindialog.h"

#define FCITXSKINSYSTEM_PATH "/usr/share/fcitx-qimpanel/skin/"

EditingSkinDialog::EditingSkinDialog(bool pHorizontal,QListWidgetItem *item,
                    QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditingSkinDialog)
{
    ui->setupUi(this);
    localPath = qgetenv("HOME") + "/.config/fcitx-qimpanel/skin/";
    ui->EditingSkinTabWidget->setCurrentIndex(0);
    mItem = item;
    mHorizontal = pHorizontal;
    ui->lineEditSkinAuthor->setEnabled(false);
    ui->lineEditSkinVersion->setEnabled(false);

    this->setWindowTitle("skin/"+mItem->text()+"/fcitx_skin.conf");

    if(mItem->text().indexOf("(local)")==-1)
    {
        ui->EditingSkinTabWidget->setEnabled(false);
        mSettings = new QSettings(FCITXSKINSYSTEM_PATH + mItem->text() + "/fcitx_skin.conf",QSettings::IniFormat);
        mSettings->setIniCodec("UTF-8");
//        QMessageBox::information(this,tr("tips"),tr("If you want to create a local configuration of the skin and use, please click ok."));
    }
    else
    {
        mSettings = new QSettings(localPath + mItem->text().mid(0,mItem->text().indexOf("(local)")) + "/fcitx_skin.conf",QSettings::IniFormat);
        mSettings->setIniCodec("UTF-8");
    }
    loadMainConf();
}

EditingSkinDialog::~EditingSkinDialog()
{
    mSettings->sync();
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
    ui->lineEditSkinVersion->setText(skinVersion);

    mSettings->endGroup();

    mSettings->beginGroup("SkinFont");
    int fontSize = mSettings->value("FontSize").toInt();
    int candFontSize = mSettings->value("CandFontSize").toInt();
    QString inputColor = mSettings->value("InputColor").toString();
    QString indexColor = mSettings->value("IndexColor").toString();
    QString firstCandColor = mSettings->value("FirstCandColor").toString();
    QString otherColor = mSettings->value("OtherColor").toString();
    inputColorConf = inputColor;
    indexColorConf = indexColor;
    firstCandColorConf = firstCandColor;
    otherColorConf = otherColor;
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
    mSettings->endGroup();

    mSettings->beginGroup("SkinInputBarVertical");
    int adjustWidth_v = mSettings->value("AdjustWidth").toInt();
    int adjustHeight_v = mSettings->value("AdjustHeight").toInt();
    QString backImg_v = mSettings->value("BackImg").toString();
    int marginTop_v = mSettings->value("MarginTop").toInt();
    int marginBottom_v = mSettings->value("MarginBottom").toInt();
    mSettings->endGroup();

    ui->lineEdit_iTipsImg->setText(tipsImg);
    ui->spinBox_iLeftMargin->setValue(marginLeft);
    ui->spinBox_iRightMargin->setValue(marginRight);

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
    if(mHorizontal == true)
    {
        ui->spinBox_iAdjustHeight->setValue(adjustHeight);
        ui->spinBox_iAdjustWidth->setValue(adjustWidth);
        ui->lineEdit_iBackImg->setText(backImg);
        ui->spinBox_iTopMargin->setValue(marginTop);
        ui->spinBox_iBottomMargin->setValue(marginBottom);
    }
    else
    {
        ui->spinBox_iAdjustHeight->setValue(adjustHeight_v);
        ui->spinBox_iAdjustWidth->setValue(adjustWidth_v);
        ui->lineEdit_iBackImg->setText(backImg_v);
        ui->spinBox_iTopMargin->setValue(marginTop_v);
        ui->spinBox_iBottomMargin->setValue(marginBottom_v);
    }
}

void EditingSkinDialog::saveMainConf()
{
    QDir *temp = new QDir;
    if(false == temp->exists(localPath + mItem->text().mid(0,mItem->text().indexOf("(local)"))))
    {
        QString cmd = "cp -R /usr/share/fcitx-qimpanel/skin/" + mItem->text() +" "+ localPath ;
        qDebug()<<cmd;
        QByteArray ba = cmd.toLatin1();
        const char *transpd = ba.data();
        if(0!= system(transpd))
        {
            return ;
        }
    }
    mSettings = new QSettings(localPath + mItem->text().mid(0,mItem->text().indexOf("(local)")) + "/fcitx_skin.conf",QSettings::IniFormat);
    mSettings->setIniCodec("UTF-8");
    mSettings->beginGroup("SkinFont");
    int fontSize = ui->spinBoxInputFontSize->value();
    int candFontSize = ui->spinBoxCandFontSize->value();

    if(!fontSizeEnable)
    {
        fontSize = 13;
        candFontSize = 13;
    }
    mSettings->setValue("FontSize",fontSize);
    mSettings->setValue("CandFontSize",candFontSize);
    mSettings->setValue("InputColor",inputColorConf);
    mSettings->setValue("IndexColor",indexColorConf);
    mSettings->setValue("FirstCandColor",firstCandColorConf);
    mSettings->setValue("OtherColor",otherColorConf);
    mSettings->endGroup();

    mSettings->beginGroup("SkinInputBar");
    QString tipsImg = ui->lineEdit_iTipsImg->text();
    int marginLeft = ui->spinBox_iLeftMargin->value();
    int marginRight = ui->spinBox_iRightMargin->value();

    int inputStringPosX = ui->spinBox_iInputStringPosX->value();
    int inputStringPosY = ui->spinBox_iInputStringPosY->value();
    int outputCandPosX = ui->spinBox_iOutputCandPosX->value();
    int outputCandPosY = ui->spinBox_iOutputCandPosY->value();
    QString backArrow = ui->lineEdit_iBackArrow->text();
    int backArrowX = ui->spinBox_iBackArrowX->value();
    int backArrowY = ui->spinBox_iBackArrowY->value();
    QString forwardArrow = ui->lineEdit_iForwardArrow->text();
    int forwardArrowX = ui->spinBox_iForwardArrowX->value();
    int forwardArrowY = ui->spinBox_iForwardArrowY->value();

    int marginTop = ui->spinBox_iTopMargin->value();
    int marginBottom = ui->spinBox_iBottomMargin->value();
    QString backImg = ui->lineEdit_iBackImg->text();
    int adjustWidth = ui->spinBox_iAdjustWidth->value();
    int adjustHeight = ui->spinBox_iAdjustHeight->value();



    mSettings->setValue("TipsImg",tipsImg);
    mSettings->setValue("MarginLeft",marginLeft);
    mSettings->setValue("MarginRight",marginRight);

    mSettings->setValue("InputStringPosX",inputStringPosX);
    mSettings->setValue("InputStringPosY",inputStringPosY);
    mSettings->setValue("OutputCandPosX",outputCandPosX);
    mSettings->setValue("OutputCandPosY",outputCandPosY);
    mSettings->setValue("BackArrow",backArrow);
    mSettings->setValue("BackArrowX",backArrowX);
    mSettings->setValue("BackArrowY",backArrowY);
    mSettings->setValue("ForwardArrow",forwardArrow);
    mSettings->setValue("ForwardArrowX",forwardArrowX);
    mSettings->setValue("ForwardArrowY",forwardArrowY);
    if(mHorizontal == true)
    {
        mSettings->setValue("MarginTop",marginTop);
        mSettings->setValue("MarginBottom",marginBottom);
        mSettings->setValue("BackImg",backImg);
        mSettings->setValue("AdjustWidth",adjustWidth);
        mSettings->setValue("AdjustHeight",adjustHeight);
    }
    mSettings->endGroup();

    mSettings->beginGroup("SkinInputBarVertical");
    int marginTop_v = ui->spinBox_iTopMargin->value();
    int marginBottom_v = ui->spinBox_iBottomMargin->value();
    QString backImg_v = ui->lineEdit_iBackImg->text();
    int adjustWidth_v = ui->spinBox_iAdjustWidth->value();
    int adjustHeight_v = ui->spinBox_iAdjustHeight->value();
    if(mHorizontal == false)
    {
        mSettings->setValue("MarginTop",marginTop_v);
        mSettings->setValue("MarginBottom",marginBottom_v);
        mSettings->setValue("BackImg",backImg_v);
        mSettings->setValue("AdjustWidth",adjustWidth_v);
        mSettings->setValue("AdjustHeight",adjustHeight_v);
    }
    mSettings->endGroup();

    mSettings->sync();
}

void EditingSkinDialog::on_pushButton_ok_released()
{
    if(mItem->text().indexOf("(local)")==-1)
    {
        if (QMessageBox::Yes == QMessageBox::question (this,
                                  tr("Tips "),
                                  tr("Whether to use the default configuration of the skin?"),
                                  QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes))
        {
            QString cmd = "cp -R /usr/share/fcitx-qimpanel/skin/" + mItem->text() +" "+ localPath ;
            qDebug()<<cmd;
            QByteArray ba = cmd.toLatin1();
            const char *transpd = ba.data();
            if(0!= system(transpd))
            {
                return ;
            }
        }
    }
    else
    {
        saveMainConf();
    }

//    PasswardDialog * passward = new PasswardDialog(mItem->text());
//    passward->exec();
    this->accept();
}

void EditingSkinDialog::on_pushButton_cannel_released()
{

    this->close();
}

void EditingSkinDialog::on_pushButtonInputColor_released()
{
    QColorDialog::setCustomColor(0,QRgb(0x0000FF));
    QColor color =  QColorDialog::getColor(QColor(0,0,255));
    QString str;
    if(color.isValid()){
        str.sprintf("rgb(%d,%d,%d)",color.red(), color.green(), color.blue());
        inputColorConf.sprintf("%d %d %d",color.red(),color.green(),color.blue());
        qDebug()<<inputColorConf;
        ui->pushButtonInputColor->setStyleSheet("QPushButton { background-color: " + str +";border: none;" +"}");
    }
}
void EditingSkinDialog::on_pushButtonIndexColor_released()
{
    QColorDialog::setCustomColor(0,QRgb(0x0000FF));
    QColor color =  QColorDialog::getColor(QColor(0,0,255));
    QString str;
    if(color.isValid()){
        str.sprintf("rgb(%d,%d,%d)",color.red(), color.green(), color.blue());
        indexColorConf.sprintf("%d %d %d",color.red(),color.green(),color.blue());
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
        firstCandColorConf.sprintf("%d %d %d",color.red(),color.green(),color.blue());
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
        otherColorConf.sprintf("%d %d %d",color.red(),color.green(),color.blue());
        ui->pushButtonOtherCandColor->setStyleSheet("QPushButton { background-color: " + str +";border: none;" +"}");
    }
}

//void EditingSkinDialog::copySkinConf()//复制皮肤配置到本地.config/fcitx-qimpanel/skin
//{
//    QDir *temp = new QDir;
//    if((false == temp->exists(localPath+"skin/ubuntukylin-dark1")&&(mItem->text()=="ubuntukylin-dark1"))
//            ||(false == temp->exists(localPath+"skin/ubuntukylin-dark2")&&(mItem->text()=="ubuntukylin-dark2"))
//            ||(false == temp->exists(localPath+"skin/ubuntukylin-light1")&&(mItem->text()=="ubuntukylin-light1"))
//            ||(false == temp->exists(localPath+"skin/ubuntukylin-light2")&&(mItem->text()=="ubuntukylin-light2")))
//    {
//        qDebug()<<"5555";
//        QDir *temp1 = new QDir;
//        QDir *temp2 = new QDir;
//        bool exist1 = temp1->exists(localPath+"skin/");
//        if(!exist1)
//            temp1->mkdir(localPath+"skin/");
//        bool exist2 = temp2->exists(localPath+"skin/" + mItem->text());
//        if(!exist2)
//            temp2->mkdir(localPath+"skin/" + mItem->text());
//        QString str;
//        QFile readSkinConf(FCITXSKIN_PATH + mItem->text() + "/fcitx_skin.conf");
//        QFile writeSkinconf(localPath+"skin/" + mItem->text() +"/fcitx_skin.conf");
//        if(!readSkinConf.open(QIODevice::ReadOnly | QIODevice::Text))
//            {
//               QMessageBox::warning(this,"read","can't open",QMessageBox::Yes);
//            }

//        if(!writeSkinconf.open(QIODevice::ReadWrite | QIODevice::Text))
//        {
//           QMessageBox::warning(this,"write","can't open",QMessageBox::Yes);
//        }
//        QTextStream readFcitxSkinConf(&readSkinConf);
//        QTextStream writeFcitxSkinConf(&writeSkinconf);

//        do{
//            str=readFcitxSkinConf.readLine();//读取一行
//            writeFcitxSkinConf<<str<<"\n";
//        } while (!str.isNull());
//        readSkinConf.close();
//        writeSkinconf.close();
//    }
//}

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



