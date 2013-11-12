#ifndef EDITINGSKINDIALOG_H
#define EDITINGSKINDIALOG_H

#include <QDialog>
#include <QSettings>
#include <QListWidgetItem>
#include <skin/skinfcitx.h>

namespace Ui {
class EditingSkinDialog;
}

class EditingSkinDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit EditingSkinDialog(QSettings *pSettings,SkinFcitx *skinFcitx,QListWidgetItem *item
                               ,QWidget *parent = 0);
    ~EditingSkinDialog();
    
private slots:
    void on_pushButtonTipsColor_released();

    void on_pushButton_ok_released();

    void on_pushButton_cannel_released();

private:
    Ui::EditingSkinDialog *ui;
    QSettings *mSettings;
    SkinFcitx *mSkinFcitx;
    QListWidgetItem *mItem;

private:
    void loadMainConf();
    void saveMainConf();
};

#endif // EDITINGSKINDIALOG_H
