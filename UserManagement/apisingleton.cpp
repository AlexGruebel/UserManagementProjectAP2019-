#include "apisingleton.h"
#include <QtNetwork/QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
#include <memory>

static const QString URL = "http://localhost:8080/api";

ApiSingleton &ApiSingleton::getInstance()
{
    static ApiSingleton instance;
    return instance;
}

ApiSingleton::ApiSingleton()
{
    m_restClient = new QNetworkAccessManager(this); //constructor

//    connect(
//        m_restClient, &QNetworkAccessManager::finished,
//        [=]( QNetworkReply* reply )
//    {
//        qDebug() << reply->readAll();
//    });
}

void ApiSingleton::userList()
{
    QNetworkRequest request;
    request.setUrl(QUrl(URL+"/user"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QString concatenated = "root:admin@123"; //username:password
    QByteArray data = concatenated.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;

    request.setRawHeader("Authorization", headerData.toLocal8Bit());
    QNetworkReply *reply=m_restClient->get(request);

    connect(
        reply, &QNetworkReply::finished,
        [=]( )
    {
//        qDebug() << reply->readAll();
        emit userListReceived(stringToJsonObject(reply->readAll()));
        reply->deleteLater();
    });


//    //DEBUG
////    QList<QPair<int, QString> > list = { {0,"one"}, {1,"two"}, {2,"three"} };
////    return list;
//    qDebug() << "Receive Userlist";
//    QString data;

//    QFile f("C:\\Users\\Adrian-Laptop\\Documents\\Projects\\UserManagementProjectAP2019-\\UserManagement\\json\\user.json");
//    if (f.open(QFile::ReadOnly | QFile::Text))
//    {
//        QTextStream in(&f);
//        data = in.readAll();
//    }
//    return stringToJsonObject(data);
}

QJsonObject ApiSingleton::userDetails(int id)
{
    qDebug() << "Receive Userdetails";
    QString data;

    QFile f("C:\\Users\\Adrian-Laptop\\Documents\\Projects\\UserManagementProjectAP2019-\\UserManagement\\json\\userdetails_only1.json");
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
    QFile f("C:\\Users\\Adrian-Laptop\\Documents\\Projects\\UserManagementProjectAP2019-\\UserManagement\\json\\json_output.json");
    if (f.open(QFile::WriteOnly | QFile::Text))
    {
        QTextStream out(&f);
        out << strJson;
    }
}






