#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QSettings>
#include <QString>
#include <QVector>
#include <QListWidgetItem>
#include <QHBoxLayout>
#include "skin/skinbase.h"
#include "skin/skinfcitx.h"
#include "main_model.h"
#include "candidate_word.h"
#include "editingskindialog.h"

namespace Ui {
class MainWindow;
}

struct SkinTypeEntry {
    QString name;
    QString absolutePath;
};

class MainWindow : public QDialog
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    QSettings *mSettings;
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
    QString skinPath;
    QList<SkinTypeEntry> allSkinType;

    SkinFcitx *mSkinFcitx;
    MainModel *mMainModer;
    QDeclarativeView *qmlView;
    QHBoxLayout *mLayout;
    QString curtSkinType;
    QString localPath;
    QStringList systemSkin_list;
    QStringList localSkin_list;
private:
    void searchAndSetSystemSkin( );
    void searchAndSetLocalSkin( );
    void loadMainConf();
    void saveMainConf();
    void loadSkinPreview();
    void changeMainWindowSize();
    void setSkinBase();
    void showListWidgetAllSkin();
    void setListWidgetAllSkin();
    void refreshListWidgetAllSkin();

private slots:
    void sltOnPushButtonApply();
    void sltOnPushButtonCancel();
    void sltOnAllSkinItemDoubleClicked(QListWidgetItem *item);
    void sltOnAllSkinCurrentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
    void sltOnCurrentChanged(QWidget *tab);  
    void on_radioButtonHorizontal_toggled(bool checked);
    void setListWidgetAllSkinIndex(int index);
};

#endif // MAINWINDOW_H
