#ifndef THREADXML_H
#define THREADXML_H

#include <QThread>
#include <QDebug>
#include <QString>
#include <QDir>
#include <tinyxml.h>

using namespace std;

class ThreadXML : public QThread
{
    Q_OBJECT
public:
    explicit ThreadXML(QObject *parent = 0);
    void run();
    
signals:
    void GetidConnexions(QString);
    void XmlIsParsed();
    void isErrorXml(int);
    
public slots:
    
};

#endif // THREADXML_H
