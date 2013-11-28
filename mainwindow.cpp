#include <QDir>
#include <QFileInfoList>
#include <QDebug>
#include <QListWidgetItem>
#include <QDeclarativeView>
#include <QtDeclarative/QDeclarativeContext>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#define FCITXSKIN_PATH "/usr/share/fcitx-qimpanel/skin/"

MainWindow::MainWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    qmlView = new QDeclarativeView;
    mSkinFcitx = new SkinFcitx;
    mMainModer = MainModel::self();
    mSettings = new QSettings("fcitx-qimpanel", "main");
    mLayout = new QHBoxLayout(ui->widgetSkinPreview);
    this->setWindowTitle(tr("Qimpanel Settings"));
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
}

void MainWindow::sltOnAllSkinCurrentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    curtSkinType = current->text();
    ui->comboBoxSkinType->setCurrentIndex(ui->listWidgetAllSkin->currentRow());
    setSkinBase();
}

void MainWindow::searchAndSetSkin(QString curtSkinType)
{
    skinPath = FCITXSKIN_PATH;
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
            allSkinType.append(entry);

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

void MainWindow::loadSkinPreview(QString skinType)
{
    qDebug()<<"MainWindow::loadSkinPreview";
    qmlRegisterType<CandidateWord>();//注册CandidateWord列表到qml

    qmlView->setContentsMargins(0, 0, 0, 0);
    qmlView->setResizeMode(QDeclarativeView::SizeViewToRootObject);
    qmlView->setResizeAnchor(QGraphicsView::AnchorViewCenter);
    qmlView->viewport()->setAutoFillBackground(false);
    qmlView->rootContext()->setContextProperty("mainCtrl", this);
    qmlView->rootContext()->setContextProperty("mainModel", mMainModer);
    qmlView->rootContext()->setContextProperty("mainSkin", mSkinFcitx);//把qt程序暴露到qml

    qmlView->setSource(QUrl("qrc:/new/prefix1/main.qml"));
    setSkinBase();
    mLayout->addWidget(qmlView);
}

void MainWindow::loadMainConf()
{
    bool verticalList;

    mSettings->beginGroup("base");
    verticalList = mSettings->value("VerticalList", false).toBool();
    curtSkinType = mSettings->value("CurtSkinType", "ubuntukylin-dark1").toString();

    mSettings->endGroup();


    ui->radioButtonVertical->setChecked(verticalList);
    ui->radioButtonHorizontal->setChecked(!verticalList);

    searchAndSetSkin(curtSkinType);
    mSkinFcitx->loadSkin(skinPath + curtSkinType + "/");
    loadSkinPreview(curtSkinType);
}

void MainWindow::saveMainConf()
{
    qDebug()<<"MainWindow::saveMainConf";
    bool verticalList;
    QString curtSkinType;

    mSettings->beginGroup("base");
    verticalList = ui->radioButtonVertical->isChecked();
    curtSkinType = ui->comboBoxSkinType->currentText();

    mSettings->setValue("VerticalList", verticalList);
    mSettings->setValue("CurtSkinType", curtSkinType);

}

void MainWindow::setSkinBase()
{
    SkinFcitx* skin = new SkinFcitx;
    mLayout->removeWidget(qmlView);
    skin->loadSkin(skinPath + curtSkinType + "/");
    if (mSkinFcitx != skin)
       delete mSkinFcitx;
    mSkinFcitx = skin;

    qmlView->rootContext()->setContextProperty("mainSkin", mSkinFcitx);//把qt程序暴露到qml
    qmlView->setSource(QUrl("qrc:/new/prefix1/main.qml"));
    mLayout->addWidget(qmlView);
    mMainModer->emitSigMainWindowSizeChanged();
}


void MainWindow::sltOnPushButtonApply()
{
    saveMainConf();
    QString cmd4 = "killall -HUP fcitx-qimpanel";
    QByteArray ba4 = cmd4.toLatin1();
    const char * transpd4 = ba4.data();
    system(transpd4);
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


