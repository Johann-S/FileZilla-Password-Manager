#ifndef QMANAGER_H
#define QMANAGER_H

#include <QMainWindow>
#include <QDebug>
#include <QString>
#include <QDir>
#include <QFile>
#include <QStringListModel>
#include <QStandardItemModel>
#include <QMessageBox>
#include <QMovie>
#include <QFileDialog>
#include "threadxml.h"
#include "editdialog.h"
#include "suppthread.h"

namespace Ui {
class QManager;
}

class QManager : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit QManager(QWidget *parent = 0);
    ~QManager();
    
private slots:
    void idConnexions(QString);
    void xmlIsParsed();
    void on_listView_account_clicked(const QModelIndex &index);
    void on_pushButton_edit_clicked();
    void ErrorXml(int);
    void on_pushButton_supp_clicked();
    void nodeIsDelete(bool);

    void on_actionSauvegarder_triggered();

private:
    Ui::QManager *ui;
    ThreadXML* pThread;
    SuppThread* pThreadSupp;
    QList<QString> listId;
    int nbId;
    QString select;
    int row;
};

#endif // QMANAGER_H
