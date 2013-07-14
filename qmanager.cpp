#include "qmanager.h"
#include "ui_qmanager.h"

typedef enum Error {
    FileNotExist,
    NodeDoesNotExist
};

QManager::QManager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QManager)
{
    ui->setupUi(this);

    nbId = 0;

    // Thread to parse all the file
    pThread = new ThreadXML();
    connect(pThread,SIGNAL(GetidConnexions(QString)),this,SLOT(idConnexions(QString)));
    connect(pThread,SIGNAL(XmlIsParsed()),this,SLOT(xmlIsParsed()));
    connect(pThread,SIGNAL(isErrorXml(int)),this,SLOT(ErrorXml(int)));
    pThread->start();

    // Thread to delete element in the list
    pThreadSupp = new SuppThread();
    connect(pThreadSupp,SIGNAL(isErrorXml(int)),this,SLOT(ErrorXml(int)));
    connect(pThreadSupp,SIGNAL(NodeDelete(bool)),this,SLOT(nodeIsDelete(bool)));

    // UI
    ui->pushButton_edit->setEnabled(false);
    ui->pushButton_supp->setEnabled(false);
    ui->pushButton_display->setEnabled(false);
    QMovie* mov = new QMovie(":/resources/load.gif");
    ui->label_gifload->setMovie(mov);
    mov->start();
}

QManager::~QManager()
{
    delete ui;
    delete pThread;
    delete pThreadSupp;
}

void QManager::idConnexions(QString id)
{
    listId<<id;
    nbId++;
}

void QManager::xmlIsParsed()
{
    ui->label_gifload->hide();
    QStringList listeCo;
    for (int i = 0; i < listId.size(); ++i)
    {
        QString item = listId.at(i);
        QStringList seperateItem = item.split('/');
        listeCo<<seperateItem[0];
    }
    QStringListModel *modele = new QStringListModel(listeCo);
    ui->listView_account->setModel(modele);
}

void QManager::on_listView_account_clicked(const QModelIndex &index)
{
    row = index.row();
    select = listId.at(index.row());
    ui->pushButton_edit->setEnabled(true);
    ui->pushButton_supp->setEnabled(true);
    ui->pushButton_display->setEnabled(true);
}

void QManager::on_pushButton_edit_clicked()
{
    EditDialog dial;
    dial.recupInfo(select);
    dial.exec();

   // pThread->start();
}

void QManager::ErrorXml(int type)
{
    QString msg;
    if ( type == FileNotExist )
        msg = "The file doesn't exist !";

    if ( type == NodeDoesNotExist )
        msg = "The node doesn't exist !";

    QMessageBox::warning(this,"Error",msg);
}

void QManager::on_pushButton_supp_clicked()
{
    QString account = select.split('/').at(0);
    pThreadSupp->getNode(account);
    pThreadSupp->start();
}

void QManager::nodeIsDelete(bool del)
{
    if ( del )
        ui->listView_account->model()->removeRow(row);
    else
        QMessageBox::warning(this,"Warning","The node can't be delete !");
}

void QManager::on_actionSauvegarder_triggered()
{
    QString pathSaveFile = QFileDialog::getSaveFileName(this, "Sauvegarder votre fichier", QString(), ".xml");

    // Get data
    QString pathfile = QDir::home().path()+"/AppData/Roaming/FileZilla/sitemanager.xml";
    QFile mainFile(pathfile);

    if ( mainFile.open(QIODevice::ReadOnly) )
    {
        QByteArray data = mainFile.readAll();
        mainFile.close();

        QFile fileToWrite(pathSaveFile);
        if ( fileToWrite.open(QIODevice::WriteOnly))
        {
            if ( fileToWrite.write(data) != -1 ) {
                QMessageBox::information(this,"Information","Le fichier à été sauvegardé !");
            }
            fileToWrite.close();
        }
    }
}
