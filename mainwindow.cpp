#include <QDir>
#include <QFileInfoList>
#include <QDebug>
#include <QListWidgetItem>
#include <QDeclarativeView>
#include <QtDeclarative/QDeclarativeContext>
#include <QMessageBox>
#include <QThread>
#include <QTimer>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#define FCITXSKINSYSTEM_PATH "/usr/share/fcitx-qimpanel/skin/"

MainWindow::MainWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qmlRegisterType<CandidateWord>();//注册CandidateWord列表到qml
    qmlView = new QDeclarativeView;
    mSkinFcitx = new SkinFcitx;
    mMainModer = MainModel::self();
    timeFlag = 2;
    mSettings = new QSettings("fcitx-qimpanel", "main");
    mSettings->setIniCodec("UTF-8");
    mLayout = new QHBoxLayout(ui->widgetSkinPreview);
    localPath = qgetenv("HOME") + "/.config/fcitx-qimpanel/skin/";
    this->setWindowTitle(tr("Qimpanel Settings"));
    loadMainConf();
    ui->tabWidget->setCurrentIndex(0);
    ui->listWidgetAllSkin->setCurrentRow(0);
    mMainModer->resetData();
    changeMainWindowSize();   

    connect(ui->pushButtonCancel, SIGNAL(clicked()), this, SLOT(sltOnPushButtonCancel()));
    connect(ui->pushButtonApply, SIGNAL(clicked()), this, SLOT(sltOnPushButtonApply()));

    connect(ui->tabWidget, SIGNAL(currentChanged(QWidget *)), this, SLOT(sltOnCurrentChanged(QWidget *)));

    connect(ui->listWidgetAllSkin, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
            this, SLOT(sltOnAllSkinItemDoubleClicked(QListWidgetItem*)));
    connect(ui->listWidgetAllSkin, SIGNAL(itemClicked(QListWidgetItem*)),
            this, SLOT(sltOnAllSkinItemClicked(QListWidgetItem *)));
    connect(ui->comboBoxSkinType,SIGNAL(currentIndexChanged(int)),this,SLOT(setListWidgetAllSkinIndex(int)));

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerDone()));
}

MainWindow::~MainWindow()
{
    mSettings->sync();
    if(mSettings!=NULL)
        delete mSettings;
    delete timer;
    delete ui;
}

void MainWindow::changeMainWindowSize()
{
    int y = 0;
    int x = 0;

    if (ui->radioButtonVertical->isChecked()) {
        y = 120;

        this->setFixedSize(560+x, 360 + y);
        ui->tabWidget->setFixedHeight(311 + y);
        ui->tabWidget->setFixedWidth(561 + x);
        ui->widgetSkinPreview->setFixedWidth(381 + x);
        ui->widgetSkinPreview->setFixedHeight(121 + y + 40);

        ui->pushButtonCancel->setGeometry(360+x, 320 + y, 81, 31);
        ui->pushButtonApply->setGeometry(450+x, 320 + y, 81, 31);


    } else {

        this->setFixedSize(560+x, 360 + y);
        ui->tabWidget->setFixedHeight(311 + y);
        ui->tabWidget->setFixedWidth(561 + x);
        ui->widgetSkinPreview->setFixedWidth(381 + x);
        ui->widgetSkinPreview->setFixedHeight(121 + y + 40);

        ui->pushButtonCancel->setGeometry(360+x, 320 + y, 81, 31);
        ui->pushButtonApply->setGeometry(450+x, 320 + y, 81, 31);
    }
}

void MainWindow::sltOnCurrentChanged(QWidget *tab)
{
    if (tab == ui->tabSkinDesign)
    {
        changeMainWindowSize();
    }
}

void MainWindow::sltOnAllSkinItemDoubleClicked(QListWidgetItem *item)
{
    if(curtSkinType.indexOf("local")==-1)
    {
        QString localPath= "/usr/share/fcitx-qimpanel/skin/"+ curtSkinType.mid(0,curtSkinType.indexOf("(local)"));
        qDebug()<<localPath;
        QDir *temp = new QDir;
        if(true == temp->exists(localPath + "/skin.ini"))
        {
            QMessageBox::information(this,tr("tips"),tr("Sougo Skin does not support preview and edit!"));
        }
        else{
            EditingSkinDialog * editingSkinDialog = new EditingSkinDialog(ui->radioButtonHorizontal->isChecked(),item);
            editingSkinDialog->exec();
            refreshListWidgetAllSkin();
        }
    }
    else{
        QString localPath= qgetenv("HOME") + "/.config/fcitx-qimpanel/skin/"+ curtSkinType.mid(0,curtSkinType.indexOf("(local)"));
        qDebug()<<localPath;
        QDir *temp1 = new QDir;
        if(true == temp1->exists(localPath + "/skin.ini"))
        {
            QMessageBox::information(this,tr("tips"),tr("Sougo Skin does not support preview and edit!"));
        }
        else{
            EditingSkinDialog * editingSkinDialog1 = new EditingSkinDialog(ui->radioButtonHorizontal->isChecked(),item);
            editingSkinDialog1->exec();
            refreshListWidgetAllSkin();
        }
    }
}

void MainWindow::sltOnAllSkinItemClicked(QListWidgetItem *current)
{
    curtSkinType = current->text();
    if(curtSkinType.indexOf("local")==-1)
    {
        QString localPath= "/usr/share/fcitx-qimpanel/skin/"+ curtSkinType.mid(0,curtSkinType.indexOf("(local)"));
        qDebug()<<localPath;
        QDir *temp = new QDir;
        if(true == temp->exists(localPath + "/skin.ini"))
        {
            QMessageBox::information(this,tr("tips"),tr("Sougo Skin does not support preview and edit!"));
        }
        else{
            setSkinBase();
        }
    }
    else{
        QString localPath= qgetenv("HOME") + "/.config/fcitx-qimpanel/skin/"+ curtSkinType.mid(0,curtSkinType.indexOf("(local)"));
        qDebug()<<localPath;
        QDir *temp1 = new QDir;
        if(true == temp1->exists(localPath + "/skin.ini"))
        {
            QMessageBox::information(this,tr("tips"),tr("Sougo Skin does not support preview and edit!"));
        }
        else{
            setSkinBase();
        }
    }

    ui->comboBoxSkinType->setCurrentIndex(ui->listWidgetAllSkin->currentRow());//感觉如果加入其它皮肤会出bug

}

void MainWindow::searchAndSetSystemSkin()
{
    skinPath = FCITXSKINSYSTEM_PATH;
    int count = 0;
    QDir skinDir;
    QFileInfoList list;
    QFileInfoList::Iterator iter;
    skinDir = QDir(skinPath);
    systemSkin_list.clear();
    if (!skinDir.exists())
        return;

    skinDir.setFilter(QDir::Dirs);
    list = skinDir.entryInfoList();
    for (iter = list.begin(); iter != list.end(); ++ iter) {
        if (iter->isDir() && "." != iter->fileName() && ".." != iter->fileName()) {
            QFile fcitxSkinConfFile_conf(iter->absoluteFilePath() + "/fcitx_skin.conf");
            QFile fcitxSkinConfFile_ini(iter->absoluteFilePath() + "/skin.ini");
            if (!fcitxSkinConfFile_conf.exists()&&!fcitxSkinConfFile_ini.exists())
                continue;

            SkinTypeEntry entry;
            entry.name = iter->fileName();
            entry.absolutePath = iter->absoluteFilePath();
            //allSkinType.append(entry);

            if (curtSkinType == entry.name)
            {
                idx = count;
            }

//            ui->comboBoxSkinType->addItem(entry.name);
            systemSkin_list.append(entry.name);
//            ui->listWidgetAllSkin->addItem(entry.name);
            count ++;
        }
    }
//    ui->listWidgetAllSkin->setCurrentRow(idx);
//    ui->comboBoxSkinType->setCurrentIndex(idx);
}

void MainWindow::searchAndSetLocalSkin()
{
    int idx = 0;
    int count = 0;
    QDir skinDir;
    QFileInfoList list;
    QFileInfoList::Iterator iter;
    skinDir = QDir(localPath);
    localSkin_list.clear();
    if (!skinDir.exists())
    {
        qDebug()<<localPath;
        return;
    }
    skinDir.setFilter(QDir::Dirs);
    list = skinDir.entryInfoList();
    for (iter = list.begin(); iter != list.end(); ++ iter) {
        if (iter->isDir() && "." != iter->fileName() && ".." != iter->fileName()) {
            QFile fcitxSkinConfFile_conf(iter->absoluteFilePath() + "/fcitx_skin.conf");
            QFile fcitxSkinConfFile_ini(iter->absoluteFilePath() + "/skin.ini");
            if (!fcitxSkinConfFile_conf.exists()&&!fcitxSkinConfFile_ini.exists())
                continue;

            SkinTypeEntry entry;
            entry.name = iter->fileName();
            entry.absolutePath = iter->absoluteFilePath();

            if (curtSkinType == entry.name)
            {
                idx = count;
            }

            if(ui->listWidgetAllSkin)
            localSkin_list.append(entry.name+"(local)");
//            ui->listWidgetAllSkin->addItem(entry.name+"(local)");
            count ++;
        }
    }
//    ui->listWidgetAllSkin->setCurrentRow(idx);
}

void MainWindow::loadSkinPreview()
{
    qDebug()<<"MainWindow::loadSkinPreview";
    setSkinBase();
}

void MainWindow::loadMainConf()
{
    bool verticalList;
    //QString curtSkinType;

    mSettings->beginGroup("base");
    verticalList = mSettings->value("VerticalList", false).toBool();
    curtSkinType = mSettings->value("CurtSkinType", "ubuntukylin-dark1").toString();
    mSettings->endGroup();

    ui->radioButtonVertical->setChecked(verticalList);
    ui->radioButtonHorizontal->setChecked(!verticalList);
    searchAndSetLocalSkin();
    searchAndSetSystemSkin();
    showListWidgetAllSkin();
    loadSkinPreview();
}
void MainWindow::saveMainConf()
{
    qDebug()<<"MainWindow::saveMainConf";
    bool verticalList;

    mSettings->beginGroup("base");
    verticalList = ui->radioButtonVertical->isChecked();
    curtSkinType = ui->comboBoxSkinType->currentText();
    qDebug()<<"MainWindow::saveMainConf()"<<curtSkinType;
    if(curtSkinType.indexOf("(local)")!=-1)
    {
      curtSkinType = curtSkinType.mid(0,curtSkinType.indexOf("(local)"));
    }
    mSettings->setValue("VerticalList", verticalList);
    mSettings->setValue("CurtSkinType", curtSkinType);
    qDebug()<<"MainWindow::saveMainConf()"<<curtSkinType;
    mSettings->endGroup();
}

void MainWindow::setSkinBase()
{
    SkinFcitx* skin = new SkinFcitx;
    mLayout->removeWidget(qmlView);
    if(curtSkinType.indexOf("(local)")==-1)
    {
        skin->loadSkin(skinPath + curtSkinType + "/");
    }
    else
    {
        skin->loadSkin(localPath + curtSkinType.mid(0,curtSkinType.indexOf("(local)")) + "/");
    }

    if (mSkinFcitx != skin)
       delete mSkinFcitx;
    mSkinFcitx = skin;
    qmlView->rootContext()->setContextProperty("mainSkin", mSkinFcitx);//把qt程序暴露到qml
    qmlView->rootContext()->setContextProperty("mainModel", mMainModer);
    qmlView->setSource(QUrl("qrc:/new/prefix1/main.qml"));
    mLayout->addWidget(qmlView);
    mMainModer->emitSigMainWindowSizeChanged();
}


void MainWindow::sltOnPushButtonApply()
{
    saveMainConf();
    if(timeFlag == 2)
    {
        timeFlag --;
        QString cmd2 = "killall -HUP fcitx-qimpanel";
        QByteArray ba2 = cmd2.toLatin1();
        const char * transpd2 = ba2.data();
        if(0!= system(transpd2))
        {
            return ;
        }
        timer->start(1000); // 1秒单触发定时器
    }
}

void MainWindow::sltOnPushButtonCancel()
{
    this->close();
}

void MainWindow::on_radioButtonHorizontal_toggled(bool checked)
{
    mMainModer->setIsHorizontal(checked);
    setSkinBase();
    changeMainWindowSize();
}

void MainWindow::showListWidgetAllSkin()
{
    QList<QString>::Iterator iter_system;
    QList<QString>::Iterator iter_local;
    QString tmp_systemList;
    QString tmp_localList;
    bool flag = true;//
    for (iter_system = systemSkin_list.begin(); iter_system != systemSkin_list.end(); ++ iter_system) {
        tmp_systemList = *iter_system;
        for(iter_local = localSkin_list.begin(); iter_local != localSkin_list.end(); ++ iter_local){
            tmp_localList = *iter_local;
            if(tmp_localList.mid(0,tmp_localList.indexOf("(local)")) == tmp_systemList){
                ui->listWidgetAllSkin->addItem(tmp_localList);
                ui->comboBoxSkinType->addItem(tmp_localList.mid(0,tmp_localList.indexOf("(local)")));
                qDebug()<<tmp_localList;
                 flag = false;
                 continue;
            }
        }
        if(flag)
        {
            qDebug()<<tmp_systemList;
            ui->listWidgetAllSkin->addItem(tmp_systemList);
            ui->comboBoxSkinType->addItem(tmp_systemList);
        }
        flag = true;
    }
        ui->comboBoxSkinType->setCurrentIndex(idx);
        ui->listWidgetAllSkin->setCurrentRow(idx);
}

void MainWindow::refreshListWidgetAllSkin()
{
    disconnect(ui->listWidgetAllSkin, SIGNAL(itemDoubleClicked(QListWidgetItem*)),0, 0);
    disconnect(ui->listWidgetAllSkin, SIGNAL(itemClicked(QListWidgetItem*)),0,0);
    ui->listWidgetAllSkin->clear();
    connect(ui->listWidgetAllSkin, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
            this, SLOT(sltOnAllSkinItemDoubleClicked(QListWidgetItem*)));
    connect(ui->listWidgetAllSkin, SIGNAL(itemClicked(QListWidgetItem*)),
            this, SLOT(sltOnAllSkinItemClicked(QListWidgetItem *)));
    searchAndSetLocalSkin();
    searchAndSetSystemSkin();
    ui->comboBoxSkinType->clear();
    showListWidgetAllSkin();
    qDebug()<<"MainWindow::refreshListWidgetAllSkin()";
}

void MainWindow::setListWidgetAllSkinIndex(int index)
{
    ui->listWidgetAllSkin->setCurrentRow(index);
}

void MainWindow::timerDone()
{
    if(0 ==(timeFlag--))
    {
        timeFlag = 2;
        timer->stop();
    }
    qDebug()<<timeFlag;
}
