#include "editthreadxml.h"

EditThreadXml::EditThreadXml(QObject *parent) :
    QThread(parent)
{
}

void EditThreadXml::run()
{
    QString pathfile = QDir::home().path()+"/AppData/Roaming/FileZilla/sitemanager.xml";

    // convert QString to const char
    TiXmlDocument doc(pathfile.toStdString().c_str());

    if(!doc.LoadFile())
    {
        emit ErrorXml(0);
        return;
    }

    TiXmlHandle hdl(&doc);

    // Go to the "Server" Node
    TiXmlElement *elem = hdl.FirstChildElement().FirstChildElement().FirstChildElement().Element();

    if(!elem){
        emit ErrorXml(1);
        return;
    }

    // Parse all "Server" Node to edit parameters
    bool find = false;
    while ( elem )
    {
        if ( QString(elem->FirstChildElement("Name")->GetText()) == account[0] )
        {
            find = true;
            QString newval;

            if ( QString(elem->FirstChildElement("Host")->GetText()) != account[1] )
            {
                newval = account[1];
                elem->FirstChildElement("Host")->Clear();
                elem->FirstChildElement("Host")->LinkEndChild(new TiXmlText(newval.toStdString().c_str()));
            }

            if ( QString(elem->FirstChildElement("User")->GetText()) != account[2] )
            {
                newval = account[2];
                elem->FirstChildElement("User")->Clear();
                elem->FirstChildElement("User")->LinkEndChild(new TiXmlText(newval.toStdString().c_str()));
            }

            if ( QString(elem->FirstChildElement("Pass")->GetText()) != account[3] )
            {
                newval = account[3];
                elem->FirstChildElement("Pass")->Clear();
                elem->FirstChildElement("Pass")->LinkEndChild(new TiXmlText(newval.toStdString().c_str()));
            }
        }

        if ( QString(elem->FirstChildElement("Comments")->GetText()).isEmpty() )
            elem->FirstChildElement("Comments")->LinkEndChild(new TiXmlText(""));

        if ( QString(elem->FirstChildElement("LocalDir")->GetText()).isEmpty() )
            elem->FirstChildElement("LocalDir")->LinkEndChild(new TiXmlText(""));

        if ( QString(elem->FirstChildElement("RemoteDir")->GetText()).isEmpty() )
            elem->FirstChildElement("RemoteDir")->LinkEndChild(new TiXmlText(""));

        if ( find )
        {
            doc.SaveFile();
            break;
        }

        elem = elem->NextSiblingElement();
    }

    emit XmlIsChanged();
    qDebug() << "Edit Thread is Out"<< endl;
    return;
}

void EditThreadXml::recupModifs(QString info)
{
    account = info.split('/');
}
