#ifndef PASSWARDDIALOG_H
#define PASSWARDDIALOG_H

#include <QDialog>

namespace Ui {
class PasswardDialog;
}

class PasswardDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit PasswardDialog(QString fileName,QWidget *parent = 0);
    ~PasswardDialog();
    
private slots:
    void on_pushButton_Ok_released();
    void on_pushButton_Cannel_released();
    void sleep_to_call_server();
private:
    Ui::PasswardDialog *ui;
    QString mFileName;
public:
    bool trans_password(QString fileName,QString pwd);
};

#endif // PASSWARDDIALOG_H
