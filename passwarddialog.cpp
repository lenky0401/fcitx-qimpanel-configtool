#include "passwarddialog.h"
#include "ui_passwarddialog.h"
#include <QMessageBox>
#include <QProcess>
#include <QTimer>
#include <QDebug>

#define FCITXSKIN_PATH "/usr/share/fcitx-qimpanel/skin/"

PasswardDialog::PasswardDialog(QString fileName, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PasswardDialog)
{
    ui->setupUi(this);
    mFileName = fileName;
    this->setWindowTitle(tr("Password authentication"));
    ui->labelMsg->setWordWrap(true);//label自动换行
    ui->labelMsg->setText(tr("Please enter your password, and give permissions to ensure successful configuration changes!"));
    ui->lineEditpassward->setEchoMode(QLineEdit::Password);
    ui->lineEditpassward->setFocus();
}

PasswardDialog::~PasswardDialog()
{
    delete ui;
}

bool PasswardDialog::trans_password(QString fileName,QString pwd) {
    QString cmd1 = "echo " + pwd + " | sudo -S touch /usr/bin/fcitx.txt";
    QByteArray ba1 = cmd1.toLatin1();
    const char *transpd = ba1.data();
    int bb = system(transpd);
    if (bb == 0) {
        QString cmd2 = "echo " + pwd + " | sudo -S rm /usr/bin/fcitx.txt";
        QByteArray ba2 = cmd2.toLatin1();
        const char *transpd2 = ba2.data();
        system(transpd2);

//        QProcess *process = new QProcess;
//        process->start("echo " + pwd + " | sudo -S mv /tmp/"+ fileName +
//                       "/fcitx_skin.conf /usr/share/fcitx-qimpanel/skin/" + fileName + "/");
        QString cmd3 = "echo " + pwd + " | sudo -S mv /tmp/"+ fileName +
                       "/fcitx_skin.conf /usr/share/fcitx-qimpanel/skin/" + fileName + "/";
        QByteArray ba3 = cmd3.toLatin1();
        const char * transpd3 = ba3.data();
        system(transpd3);

        QString cmd4 = "killall -HUP fcitx-qimpanel";
        QByteArray ba4 = cmd4.toLatin1();
        const char * transpd4 = ba4.data();
        system(transpd4);

        QString cmd5 = "fcitx-qimpanel";
        QByteArray ba5 = cmd5.toLatin1();
        const char * transpd5 = ba5.data();
        system(transpd5);
        return true;
    }
    return false;
}

void PasswardDialog::sleep_to_call_server() {
    this->accept();
}

void PasswardDialog::on_pushButton_Ok_released()
{
        if(trans_password(mFileName,ui->lineEditpassward->text())) {
            ui->labelMsg->setText(tr("succeed, please wait!"));
            QTimer *timer = new QTimer(this);
            timer->setInterval(1000);
            connect(timer,SIGNAL(timeout()),this,SLOT(sleep_to_call_server()));
            timer->start();
        }
        else{
            ui->lineEditpassward->clear();
            ui->lineEditpassward->setFocus();
            ui->labelMsg->setText(tr("passward error,try again!"));
        }
}

void PasswardDialog::on_pushButton_Cannel_released()
{
    this->close();
    QMessageBox::warning(NULL,
                         tr("Warning"),
                         tr("server doesn't run, Modifications will not be saved!"),
                         QMessageBox::Ok);
}
