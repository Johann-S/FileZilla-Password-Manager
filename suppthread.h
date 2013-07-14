#ifndef SUPPTHREAD_H
#define SUPPTHREAD_H

#include <QThread>
#include <QDir>
#include <QDebug>
#include <tinyxml.h>

class SuppThread : public QThread
{
    Q_OBJECT
public:
    explicit SuppThread(QObject *parent = 0);
    void getNode(QString);
    void run();
    
signals:
    void isErrorXml(int);
    void NodeDelete(bool);
    
public slots:

private:
    QString node;
    
};

#endif // SUPPTHREAD_H
