
#include <QDir>
#include <QFileInfoList>
#include <QDebug>
#include <QListWidgetItem>
#include <QDeclarativeView>
#include <QHBoxLayout>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    this->setWindowTitle(tr("Qimpanel Settings"));

    loadMainConf();
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
    delete ui;
}

void MainWindow::changeMainWindowSize()
{
    int y = 100;

    if (ui->radioButtonVertical->isChecked()) {
        this->setFixedSize(560, 360 + y);
        ui->tabWidget->setFixedHeight(311 + y);

        ui->widgetSkinPreview->setFixedHeight(121 + y);

        ui->pushButtonCancel->setGeometry(360, 320 + y, 81, 31);
        ui->pushButtonApply->setGeometry(450, 320 + y, 81, 31);

    } else {
        this->setFixedSize(560, 360);
        ui->tabWidget->setFixedHeight(311);

        ui->widgetSkinPreview->setFixedHeight(121);

        ui->pushButtonCancel->setGeometry(360,320,81,31);
        ui->pushButtonApply->setGeometry(450,320,81,31);
    }
}

void MainWindow::sltOnCurrentChanged(QWidget *tab)
{
    if (tab == ui->tabSkinDesign)
        changeMainWindowSize();
}

void MainWindow::sltOnAllSkinItemDoubleClicked(QListWidgetItem *item)
{
    qDebug() << item->text();
}

void MainWindow::sltOnAllSkinCurrentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    if (previous)
        qDebug() << previous->text() << current->text();
    else
        qDebug() << current->text();
}

void MainWindow::searchAndSetSkin(QString curtSkinType)
{
    //Just Test First
    skinPath = "/usr/local/share/fcitx/skin/";

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
                idx = count;

            ui->comboBoxSkinType->addItem(entry.name);
            ui->listWidgetAllSkin->addItem(entry.name);

            count ++;
        }
    }

    ui->listWidgetAllSkin->setCurrentRow(0);
    ui->comboBoxSkinType->setCurrentIndex(idx);
}

void MainWindow::loadSkinPreview(QString skinType)
{
    QDeclarativeView *qmlView = new QDeclarativeView;
    qmlView->setSource(QUrl("qrc:/main.qml"));

    QHBoxLayout *layout = new QHBoxLayout(ui->widgetSkinPreview);
    layout->addWidget(qmlView);
}

void MainWindow::loadMainConf()
{
    bool verticalList;
    QString curtSkinType;
    QSettings *settings = new QSettings("fcitx-qimpanel", "main");

    settings->beginGroup("base");
    verticalList = settings->value("VerticalList", false).toBool();
    curtSkinType = settings->value("CurtSkinType", "default").toString();
    settings->endGroup();

    ui->radioButtonVertical->setChecked(verticalList);
    ui->radioButtonHorizontal->setChecked(!verticalList);
    searchAndSetSkin(curtSkinType);
    loadSkinPreview(curtSkinType);

    delete settings;
}

void MainWindow::saveMainConf()
{
    bool verticalList;
    QString curtSkinType;
    QSettings *settings = new QSettings("fcitx-qimpanel", "main");

    settings->beginGroup("base");
    verticalList = ui->radioButtonVertical->isChecked();
    curtSkinType = ui->comboBoxSkinType->currentText();
    settings->setValue("VerticalList", verticalList);
    settings->setValue("CurtSkinType", curtSkinType);

    delete settings;
}

void MainWindow::sltOnPushButtonApply()
{
    saveMainConf();
    this->close();
}

void MainWindow::sltOnPushButtonCancel()
{
    this->close();
}
