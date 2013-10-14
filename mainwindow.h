#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QSettings>
#include <QString>
#include <QVector>
#include <QListWidgetItem>

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
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
    QString skinPath;
    QList<SkinTypeEntry> allSkinType;

private:
    void searchAndSetSkin(QString skinType);
    void loadMainConf();
    void saveMainConf();
    void loadSkinPreview(QString skin);

private slots:
    void sltOnPushButtonApply();
    void sltOnPushButtonCancel();
    void sltOnAllSkinItemDoubleClicked(QListWidgetItem *item);
    void sltOnAllSkinCurrentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
};

#endif // MAINWINDOW_H
