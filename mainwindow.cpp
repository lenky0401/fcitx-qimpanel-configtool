#include <QDir>
#include <QFileInfoList>
#include <QDebug>
#include <QListWidgetItem>
#include <QDeclarativeView>
#include <QtDeclarative/QDeclarativeContext>

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
    mSettings = new QSettings("fcitx-qimpanel", "main");
    mLayout = new QHBoxLayout(ui->widgetSkinPreview);
    localPath = qgetenv("HOME") + "/.config/fcitx-qimpanel/skin/";
    this->setWindowTitle(tr("Qimpanel Settings"));
    curtSkinType = "ubuntukylin-dark1";
    loadMainConf();
    ui->tabWidget->setCurrentIndex(0);
    mMainModer->resetData();
    changeMainWindowSize();   

    connect(ui->pushButtonCancel, SIGNAL(clicked()), this, SLOT(sltOnPushButtonCancel()));
    connect(ui->pushButtonApply, SIGNAL(clicked()), this, SLOT(sltOnPushButtonApply()));

    connect(ui->tabWidget, SIGNAL(currentChanged(QWidget *)), this, SLOT(sltOnCurrentChanged(QWidget *)));

    connect(ui->listWidgetAllSkin, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
            this, SLOT(sltOnAllSkinItemDoubleClicked(QListWidgetItem*)));
    connect(ui->listWidgetAllSkin, SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)),
            this, SLOT(sltOnAllSkinCurrentItemChanged(QListWidgetItem *, QListWidgetItem *)));

}

MainWindow::~MainWindow()
{
    mSettings->sync();
    if(mSettings!=NULL)
        delete mSettings;
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
        changeMainWindowSize();
}

void MainWindow::sltOnAllSkinItemDoubleClicked(QListWidgetItem *item)
{
//    qDebug()<<"MainWindow::"<<mSettings->value("CurtSkinType", "default").toString();
    EditingSkinDialog * editingSkinDialog = new EditingSkinDialog(ui->radioButtonHorizontal->isChecked(),item);
    editingSkinDialog->exec();
    disconnect(ui->listWidgetAllSkin, SIGNAL(itemDoubleClicked(QListWidgetItem*)),0, 0);
    disconnect(ui->listWidgetAllSkin, SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)),0,0);
    ui->listWidgetAllSkin->clear();
    searchAndSetSystemSkin();
    searchAndSetLocalSkin();

    connect(ui->listWidgetAllSkin, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
            this, SLOT(sltOnAllSkinItemDoubleClicked(QListWidgetItem*)));
    connect(ui->listWidgetAllSkin, SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)),
            this, SLOT(sltOnAllSkinCurrentItemChanged(QListWidgetItem *, QListWidgetItem *)));

}

void MainWindow::sltOnAllSkinCurrentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    curtSkinType = current->text();
    qDebug()<<curtSkinType;
    setSkinBase();
}

void MainWindow::searchAndSetSystemSkin()
{
    skinPath = FCITXSKINSYSTEM_PATH;
    int idx = 0;
    int count = 0;
    QDir skinDir;
    QFileInfoList list;
    QFileInfoList::Iterator iter;
    skinDir = QDir(skinPath);
    if (!skinDir.exists())
        return;

    skinDir.setFilter(QDir::Dirs);
    list = skinDir.entryInfoList();
    for (iter = list.begin(); iter != list.end(); ++ iter) {
        if (iter->isDir() && "." != iter->fileName() && ".." != iter->fileName()) {
            QFile fcitxSkinConfFile(iter->absoluteFilePath() + "/fcitx_skin.conf");
            if (!fcitxSkinConfFile.exists())
                continue;

            SkinTypeEntry entry;
            entry.name = iter->fileName();
            entry.absolutePath = iter->absoluteFilePath();
            //allSkinType.append(entry);

            if (curtSkinType == entry.name)
            {
                idx = count;
            }

            ui->comboBoxSkinType->addItem(entry.name);
            ui->listWidgetAllSkin->addItem(entry.name);

            count ++;
        }
    }
    ui->listWidgetAllSkin->setCurrentRow(idx);
    ui->comboBoxSkinType->setCurrentIndex(idx);
}

void MainWindow::searchAndSetLocalSkin()
{
    int idx = 0;
    int count = 0;
    QDir skinDir;
    QFileInfoList list;
    QFileInfoList::Iterator iter;
    skinDir = QDir(localPath);
    if (!skinDir.exists())
    {
        qDebug()<<localPath;
        return;
    }
    skinDir.setFilter(QDir::Dirs);
    list = skinDir.entryInfoList();
    for (iter = list.begin(); iter != list.end(); ++ iter) {
        if (iter->isDir() && "." != iter->fileName() && ".." != iter->fileName()) {
            QFile fcitxSkinConfFile(iter->absoluteFilePath() + "/fcitx_skin.conf");
            if (!fcitxSkinConfFile.exists())
                continue;

            SkinTypeEntry entry;
            entry.name = iter->fileName();
            entry.absolutePath = iter->absoluteFilePath();

            if (curtSkinType == entry.name)
            {
                idx = count;
            }
            ui->listWidgetAllSkin->addItem(entry.name+"(local)");
            count ++;
        }
    }
    ui->listWidgetAllSkin->setCurrentRow(idx);
}

void MainWindow::loadSkinPreview()
{
    qDebug()<<"MainWindow::loadSkinPreview";
    setSkinBase();
}

void MainWindow::loadMainConf()
{
    bool verticalList;
    QString curtSkinType;

    mSettings->beginGroup("base");
    verticalList = mSettings->value("VerticalList", false).toBool();
    curtSkinType = mSettings->value("CurtSkinType", "ubuntukylin-dark1").toString();
    mSettings->endGroup();


    ui->radioButtonVertical->setChecked(verticalList);
    ui->radioButtonHorizontal->setChecked(!verticalList);

    searchAndSetSystemSkin();
    searchAndSetLocalSkin();
    loadSkinPreview();
}
void MainWindow::saveMainConf()
{
    qDebug()<<"MainWindow::saveMainConf";
    bool verticalList;

    if(curtSkinType.indexOf("(local)")!=-1)
    {
      curtSkinType = curtSkinType.mid(0,curtSkinType.indexOf("(local)"));
    }

    mSettings->beginGroup("base");
    verticalList = ui->radioButtonVertical->isChecked();

    mSettings->setValue("VerticalList", verticalList);
    mSettings->setValue("CurtSkinType", curtSkinType);

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

    QString cmd2 = "killall -HUP fcitx-qimpanel";
    QByteArray ba2 = cmd2.toLatin1();
    const char * transpd2 = ba2.data();
    if(0!= system(transpd2))
    {
        return ;
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


