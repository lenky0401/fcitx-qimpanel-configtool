#include <QString>
#include <QDebug>
#include <QApplication>
#include <QTextCodec>
#include <qtextstream.h>
#include <QTranslator>
#include "mainwindow.h"
#include <fcitx-utils/utils.h>
#define BUFF_SIZE (512)
char sharePath[BUFF_SIZE] = {0};

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    QTranslator translator;
   if (translator.load("/usr/share/fcitx-qimpanel/fcitx_skin_zh_CN.qm") == false)
//    if (translator.load(QString(getQimpanelSharePath("fcitx_skin_zh_CN.qm"))) == false)
        qDebug() << "load qm error.";
    QApplication app(argc, argv);
    app.installTranslator(&translator);
    app.setApplicationName("fcitx-qimpanel-configtool");
    MainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}
