#ifndef EDITTHREADXML_H
#define EDITTHREADXML_H

#include <QThread>
#include <QString>
#include <QDir>
#include <QDebug>
#include <tinyxml.h>

class EditThreadXml : public QThread
{
    Q_OBJECT
public:
    explicit EditThreadXml(QObject *parent = 0);
    void run();
    void recupModifs(QString);
    
signals:
    void ErrorXml(int);
    void XmlIsChanged();
    
public slots:

private:
    QStringList account;
    
};

#endif // EDITTHREADXML_H
