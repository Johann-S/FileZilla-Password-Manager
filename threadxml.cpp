#include "threadxml.h"

ThreadXML::ThreadXML(QObject *parent) :
    QThread(parent)
{
}

void ThreadXML::run()
{
    QString pathfile = QDir::home().path()+"/AppData/Roaming/FileZilla/sitemanager.xml";

    TiXmlDocument doc(pathfile.toStdString().c_str());

    if(!doc.LoadFile())
    {
        emit isErrorXml(0);
        return;
    }

    TiXmlHandle hdl(&doc);

    // Go to the "Server" Node
    TiXmlElement *elem = hdl.FirstChildElement().FirstChildElement().FirstChildElement().Element();

    if(!elem){
        emit isErrorXml(1);
        return;
    }

    // Parse all "Server" Node
    while ( elem )
    {
        QString idCo = QString(elem->FirstChildElement("Name")->GetText())+"/"+QString(elem->FirstChildElement("Host")->GetText())+"/"+QString(elem->FirstChildElement("User")->GetText())+"/"+QString(elem->FirstChildElement("Pass")->GetText());

        emit GetidConnexions(idCo);
        elem = elem->NextSiblingElement();
    }

    emit XmlIsParsed();
    qDebug() << "Thread is Out";
    return;
}
