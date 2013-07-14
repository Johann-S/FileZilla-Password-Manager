#include "editdialog.h"
#include "ui_editdialog.h"

typedef enum Error {
    FileNotExist,
    FileCantBeLoad
};

EditDialog::EditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditDialog)
{
    ui->setupUi(this);

    pThread = new EditThreadXml();
    connect(pThread,SIGNAL(ErrorXml(int)),this,SLOT(isErrorXml(int)));
    connect(pThread,SIGNAL(XmlIsChanged()),this,SLOT(isChangeXml()));
}

EditDialog::~EditDialog()
{
    delete ui;
}

void EditDialog::recupInfo(QString info)
{
    QStringList seperateItem = info.split('/');
    name = seperateItem[0];
    this->setWindowTitle(name);
    host = seperateItem[1];
    ui->lineEdit_host->setText(host);
    user = seperateItem[2];
    ui->lineEdit_user->setText(user);
    pass = seperateItem[3];
    ui->lineEdit_pass->setText(pass);

    affipass = false;
    ui->pushButton_editPass->setText("Afficher");
}

void EditDialog::on_pushButton_editPass_clicked()
{
    if (!affipass)
    {
        ui->pushButton_editPass->setText("Masquer");
        ui->lineEdit_pass->setEchoMode(QLineEdit::Normal);
        affipass = true;
    }
    else
    {
        ui->pushButton_editPass->setText("Afficher");
        ui->lineEdit_pass->setEchoMode(QLineEdit::Password);
        affipass = false;
    }
}

void EditDialog::isErrorXml(int err)
{
    QString msg;
    if ( err == FileNotExist )
        msg = "The file doesn't exist !";

    QMessageBox::warning(this,"Error",msg);
}

void EditDialog::on_pushButton_annuler_clicked()
{
    if ( ( host != ui->lineEdit_host->text() || user != ui->lineEdit_user->text() ) || pass != ui->lineEdit_pass->text() )
    {
        int rep = QMessageBox::question(this,"Attention","Voulez-vous sauvegarder les changements ?",QMessageBox::Yes | QMessageBox::No);

        if ( rep == QMessageBox::Yes )
            this->on_pushButton_apply_clicked();
        else
            this->close();
    }

    this->close();
}

void EditDialog::on_pushButton_apply_clicked()
{
    QString info = name+"/"+ui->lineEdit_host->text()+"/"+ui->lineEdit_user->text()+"/"+ui->lineEdit_pass->text();
    pThread->recupModifs(info);
    pThread->start();
}

void EditDialog::isChangeXml()
{
    QMessageBox::information(this,"Information","Les modifications ont été effectués avec succès !");
    this->close();
}
