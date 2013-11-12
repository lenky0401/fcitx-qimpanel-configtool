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
    qDebug()<<"111111111111111111111111111111";
    this->setWindowTitle("skin/"+item->text()+"/fcitx_skin_edit.conf");
    mSettings = pSettings;
    mSkinFcitx = skinFcitx;
    mItem = item;
    ui->lineEditSkinAuthor->setText(mSkinFcitx->skinAuthor());
    ui->lineEditSkinVersion->setText(mSkinFcitx->skinVersion());
    loadMainConf();
//    QHBoxLayout *layout = new QHBoxLayout;
//    layout->setContentsMargins(0, 24, 0, 0);
//    QScrollArea *scrollArea = new QScrollArea;
//    scrollArea->setWidgetResizable(true);
//    scrollArea->setWidget(ui->EditingSkinTabWidget);
//    layout->addWidget(scrollArea);
//    setLayout(layout);
}

EditingSkinDialog::~EditingSkinDialog()
{
    delete mSettings;
    delete mSkinFcitx;
    delete ui;
}

void EditingSkinDialog::loadMainConf()
{
    QSettings *settings = new QSettings("fcitx-qimpanel-skin-"+mItem->text(),"fcitx_skin_edit");
    settings->setIniCodec("UTF-8");
    settings->setValue("1111111","22222");
}

void EditingSkinDialog::saveMainConf()
{

}

void EditingSkinDialog::on_pushButtonTipsColor_released()
{
    QColorDialog::setCustomColor(0,QRgb(0x0000FF));
    QColor color =  QColorDialog::getColor(QColor(0,0,255));
    QString str;
    if(color.isValid()){
        str.sprintf("rgb(%d,%d,%d)",color.red(), color.green(), color.blue());
        qDebug()<<str;
        ui->pushButtonTipsColor->setStyleSheet("QPushButton { background-color: " + str +";border: none;" +"}");
    }
}

void EditingSkinDialog::on_pushButton_ok_released()
{
    saveMainConf();
}

void EditingSkinDialog::on_pushButton_cannel_released()
{
    this->close();
}
