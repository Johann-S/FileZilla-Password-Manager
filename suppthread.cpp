#include "suppthread.h"

SuppThread::SuppThread(QObject *parent) :
    QThread(parent)
{
}

void SuppThread::getNode(QString nodeToDelete)
{
    this->node = nodeToDelete;
}

void SuppThread::run()
{
    QString pathfile = QDir::home().path()+"/AppData/Roaming/FileZilla/sitemanager.xml";

     // convert QString to const char
     TiXmlDocument doc(pathfile.toStdString().c_str());

     if(!doc.LoadFile())
     {
         emit isErrorXml(0);
         return;
     }

     TiXmlHandle hdl(&doc);

     // Go to the "Server" Node
     TiXmlElement *elem = hdl.FirstChildElement().FirstChildElement().FirstChildElement().Element();
     TiXmlElement *rootServer = hdl.FirstChildElement().FirstChildElement().Element();

     if(!elem){
         emit isErrorXml(1);
         return;
     }

     // Parse all "Server" Node to find the node witch will be delete
     bool find = false;
     bool isDelete = false;
     while ( elem )
     {
         if ( QString(elem->FirstChildElement("Name")->GetText()) == node )
            find = true;

         if ( QString(elem->FirstChildElement("Comments")->GetText()).isEmpty() )
             elem->FirstChildElement("Comments")->LinkEndChild(new TiXmlText(""));

         if ( QString(elem->FirstChildElement("LocalDir")->GetText()).isEmpty() )
             elem->FirstChildElement("LocalDir")->LinkEndChild(new TiXmlText(""));

         if ( QString(elem->FirstChildElement("RemoteDir")->GetText()).isEmpty() )
             elem->FirstChildElement("RemoteDir")->LinkEndChild(new TiXmlText(""));

         if ( find )
         {
             if ( rootServer->RemoveChild(elem) )
                 isDelete = true;

             emit NodeDelete(isDelete);
             doc.SaveFile();
             break;
         }

         elem = elem->NextSiblingElement();
     }

     qDebug()<<"Thread delete is Out"<<endl;

    return;
}
