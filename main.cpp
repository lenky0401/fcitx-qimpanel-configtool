#include <QString>
#include <QDebug>
#include <QApplication>
#include <QTextCodec>
#include <qtextstream.h>
#include <QTranslator>
#include "mainwindow.h"
#include <QDir>
#include <fcitx-utils/utils.h>

#define FCITXSKIN_PATH "/usr/share/fcitx-qimpanel/skin/ "
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
    QString localPath = qgetenv("HOME") + "/.config/fcitx-qimpanel/";
    QDir *temp = new QDir;
    if(false == temp->exists(localPath + "skin"))
    {
        QString cmd = "mkdir " + localPath +"skin";
        qDebug()<<cmd;
        QByteArray ba = cmd.toLatin1();
        const char *transpd = ba.data();
        if(0!= system(transpd))
        {
            return 0;
        }
    }

    MainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}
