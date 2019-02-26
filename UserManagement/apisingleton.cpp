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

void ApiSingleton::login(QString user, QString pw)
{
    // "root:admin@123"
    QNetworkRequest request;
    request.setUrl(QUrl(URL+"/userdetail/isAdmin/"+user));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QString concatenated = createPWString(user, pw); //username:password
    QByteArray data = concatenated.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;

    request.setRawHeader("Authorization", headerData.toLocal8Bit());
    QNetworkReply *reply=m_restClient->get(request);

    m_user = user;
    m_pw = pw;

    connect(
        reply, &QNetworkReply::finished,
        [=]( )
    {
        QString tmp= reply->readAll();
        if(tmp.toLower() == "false")
        {
            emit loginReceived(1);
        }
        else if(tmp.toLower() == "true")
        {
            emit loginReceived(2);
        }
        else
        {
            emit loginReceived(0);
        }
    });
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

    QString concatenated = createPWString(m_user, m_pw); //username:password
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
}

void ApiSingleton::userDetails(int id)
{
    QNetworkRequest request;
    request.setUrl(QUrl(URL+"/userdetail/"+QString::number(id)));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QString concatenated = createPWString(m_user, m_pw); //username:password
    QByteArray data = concatenated.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;

    request.setRawHeader("Authorization", headerData.toLocal8Bit());
    QNetworkReply *reply=m_restClient->get(request);

    connect(
        reply, &QNetworkReply::finished,
        [=]( )
    {
//        qDebug() << reply->readAll();
        emit userDetailsReceived(id, stringToJsonObject(reply->readAll()));
        reply->deleteLater();
    });

//    qDebug() << "Receive Userdetails";
//    QString data;

//    QFile f("C:\\Users\\Adrian-Laptop\\Documents\\Projects\\UserManagementProjectAP2019-\\UserManagement\\json\\userdetails_only1.json");
//    if (f.open(QFile::ReadOnly | QFile::Text))
//    {
//        QTextStream in(&f);
//        data = in.readAll();
//    }
//    return stringToJsonObject(data);
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

QString ApiSingleton::createPWString(QString user, QString pw)
{
    return user+":"+pw;
}

void ApiSingleton::sendUserDetails(int id, QJsonDocument doc)
{
    QNetworkRequest request;
    request.setUrl(QUrl(URL+"/userdetail/"+QString::number(id)));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QString concatenated = createPWString(m_user, m_pw); //username:password
    QByteArray data = concatenated.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;

    request.setRawHeader("Authorization", headerData.toLocal8Bit());
    qDebug() << doc.toJson();
    QNetworkReply *reply=m_restClient->put(request, doc.toJson());
    qDebug() << reply->readAll();
}







