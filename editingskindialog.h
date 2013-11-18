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
    explicit EditingSkinDialog(QListWidgetItem *item
                               ,QWidget *parent = 0);
    ~EditingSkinDialog();
    
private slots:
    void on_pushButtonInputColor_released();

    void on_pushButton_ok_released();

    void on_pushButton_cannel_released();

    void on_pushButtonIndexColor_released();

    void on_pushButtonFirstCandColor_released();

    void on_pushButtonOtherCandColor_released();

    void on_pushButton_menuActiveColor_released();

    void on_pushButton_menuLineColor_released();

private:
    Ui::EditingSkinDialog *ui;
    QSettings *mSettings;
    SkinFcitx *mSkinFcitx;
    QListWidgetItem *mItem;
    int horizontalTileModeIndex;
    int verticalTileModeIndex;

private:
    void loadMainConf();
    void saveMainConf();
    QString colorToRGB(QColor color);
    QColor value2color(const QString& value);
    void copySkinConf();
};

#endif // EDITINGSKINDIALOG_H
