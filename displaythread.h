#ifndef DISPLAYTHREAD_H
#define DISPLAYTHREAD_H

#include <QThread>
#include <QDir>
#include <QDebug>
#include <tinyxml.h>

class DisplayThread : public QThread
{
    Q_OBJECT

public:
    explicit DisplayThread(QObject *parent = 0);
    void run();

signals:
    void ErrorXml(int);

};

#endif // DISPLAYTHREAD_H
