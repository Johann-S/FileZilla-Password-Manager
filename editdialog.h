#ifndef EDITDIALOG_H
#define EDITDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include "editthreadxml.h"

namespace Ui {
class EditDialog;
}

class EditDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit EditDialog(QWidget *parent = 0);
    ~EditDialog();
    void recupInfo(QString);
    
private slots:
    void on_pushButton_editPass_clicked();
    void on_pushButton_annuler_clicked();
    void isErrorXml(int);
    void on_pushButton_apply_clicked();
    void isChangeXml();

private:
    Ui::EditDialog *ui;
    QString name;
    QString host;
    QString user;
    QString pass;
    bool affipass;
    EditThreadXml *pThread;
};

#endif // EDITDIALOG_H
