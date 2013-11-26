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

//char* getQimpanelSharePath(const char * const fileName)
//{
//    char *p;
//    if (readlink("/proc/self/exe", sharePath, BUFF_SIZE) < 0) {
//        perror("readlink");
//        exit(EXIT_FAILURE);
//    }
//    qDebug()<<sharePath;
//    if ((p = strrchr(sharePath, '/')) == NULL) {
//        perror("strrchr");
//        exit(EXIT_FAILURE);
//    }
//    *p = '0';
//    qDebug()<<sharePath;
//    if ((p = strrchr(sharePath, '/')) == NULL) {
//        perror("strrchr");
//        exit(EXIT_FAILURE);
//    }
//    qDebug()<<sharePath;
//    strcpy(p + 1, "usr/share/fcitx-qimpanel/");
//    strcpy(p + 1 + strlen("usr/share/fcitx-qimpanel/"), fileName);
//    qDebug()<<sharePath;
//    return sharePath;
//}

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
