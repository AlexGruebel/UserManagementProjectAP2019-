#include "apisingleton.h"
#include <QtNetwork/QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>

static const QString url = "localhost";

ApiSingleton &ApiSingleton::getInstance()
{
    static ApiSingleton instance;
    return instance;
}

ApiSingleton::ApiSingleton()
{
    QNetworkAccessManager *restclient; //in class
    restclient = new QNetworkAccessManager(this); //constructor
//    QNetworkReply *reply = restclient->post(request,payload);
//    qDebug() << reply->readAll();
}

QJsonObject ApiSingleton::userList()
{
    //DEBUG
//    QList<QPair<int, QString> > list = { {0,"one"}, {1,"two"}, {2,"three"} };
//    return list;
    qDebug() << "Receive Userlist";
    QString data;

    QFile f("F:\\Projects\\UserManagementProjectAP2019-\\UserManagement\\json\\user.json");
    if (f.open(QFile::ReadOnly | QFile::Text))
    {
        QTextStream in(&f);
        data = in.readAll();
    }
    return stringToJsonObject(data);
}

QJsonObject ApiSingleton::userDetails(int id)
{
    qDebug() << "Receive Userdetails";
    QString data;

    QFile f("F:\\Projects\\UserManagementProjectAP2019-\\UserManagement\\json\\userdetails_only1.json");
    if (f.open(QFile::ReadOnly | QFile::Text))
    {
        QTextStream in(&f);
        data = in.readAll();
    }
    return stringToJsonObject(data);
}

QJsonObject ApiSingleton::stringToJsonObject(QString s)
{
    QJsonObject obj;

    QJsonDocument doc = QJsonDocument::fromJson(s.toUtf8());

    // check validity of the document
    if(!doc.isNull())
    {
        if(doc.isObject())
        {
            obj = doc.object();
        }
        else
        {
            qDebug() << "Document is not an object" << endl;
        }
    }
    else
    {
        qDebug() << "Invalid JSON...\n" << s << endl;
    }
    return obj;
}

void ApiSingleton::sendUserDetails(int id, QJsonDocument doc)
{
    QString strJson(doc.toJson(QJsonDocument::Indented));
    QFile f("F:\\Projects\\UserManagementProjectAP2019-\\UserManagement\\json\\json_output.json");
    if (f.open(QFile::WriteOnly | QFile::Text))
    {
        QTextStream out(&f);
        out << strJson;
    }
}






