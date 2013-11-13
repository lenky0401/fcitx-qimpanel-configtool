#include <QColorDialog>
#include <QDebug>
#include <QStringList>
#include <QPainter>
#include <QScrollArea>
#include <QHBoxLayout>

#include "editingskindialog.h"
#include "ui_editingskindialog.h"

EditingSkinDialog::EditingSkinDialog(QSettings *pSettings,SkinFcitx *skinFcitx,
                                     QListWidgetItem *item,
                                     QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditingSkinDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("skin/"+item->text()+"/fcitx_skin.conf");
    mSettings = pSettings;
    mSkinFcitx = skinFcitx;
    mItem = item;
    ui->lineEditSkinAuthor->setText(mSkinFcitx->skinAuthor());
    ui->lineEditSkinVersion->setText(mSkinFcitx->skinVersion());
    loadMainConf();

//    QVBoxLayout *layout = new QVBoxLayout;
//    QWidget *containWidget = new QWidget;
//    layout->addWidget(ui->labelSkinAuthor);
//    layout->addWidget(ui->labelSkinVersion);
//    layout->addWidget(ui->lineEditSkinAuthor);
//    layout->addWidget(ui->lineEditSkinVersion);
//    containWidget->setLayout(layout);
//    ui->scrollArea->setWidgetResizable(true);
//    ui->scrollArea->setWidget(containWidget);
}

EditingSkinDialog::~EditingSkinDialog()
{
    delete mSettings;
    delete mSkinFcitx;
    delete ui;
}

void EditingSkinDialog::loadMainConf()
{
    QSettings *settings = new QSettings("fcitx-qimpanel-skin-"+mItem->text(),"fcitx_skin");
    settings->setIniCodec("UTF-8");
    settings->setValue("1111111","22222");
}

void EditingSkinDialog::saveMainConf()
{

}

void EditingSkinDialog::on_pushButtonInputColor_released()
{
    QColorDialog::setCustomColor(0,QRgb(0x0000FF));
    QColor color =  QColorDialog::getColor(QColor(0,0,255));
    QString str;
    if(color.isValid()){
        str.sprintf("rgb(%d,%d,%d)",color.red(), color.green(), color.blue());
        qDebug()<<str;
        ui->pushButtonInputColor->setStyleSheet("QPushButton { background-color: " + str +";border: none;" +"}");
    }
}

void EditingSkinDialog::on_pushButton_ok_released()
{
    saveMainConf();
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
