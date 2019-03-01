#include "apisingleton.h"
#include <QtNetwork/QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
#include <memory>

ApiSingleton &ApiSingleton::getInstance()
{
    static ApiSingleton instance;
    return instance;
}

void ApiSingleton::login(QString user, QString pw, QString url)
{
    // "root:admin@123"
    m_url = "http://"+url+"/api";

    QNetworkRequest request;
    request.setUrl(QUrl(m_url+"/userdetail/isAdmin/"+user));
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

        if(reply->error() == QNetworkReply::ProtocolInvalidOperationError)
        {
            emit loginReceived(serverError);
        }
        else if(reply->error() == QNetworkReply::AuthenticationRequiredError)
        {
            emit loginReceived(authenticationError);
        }
        else if (reply->error() == QNetworkReply::NoError)
        {
            if(tmp.toLower() == "true")
            {
                emit loginReceived(loginAdmin);
            }
            else
            {
                emit loginReceived(loginUser);
            }
        }
        else
        {
            qDebug() << reply->error();
            emit loginReceived(generalError);
        }
    });
}


ApiSingleton::ApiSingleton()
{
    m_restClient = new QNetworkAccessManager(this); //constructor
}

void ApiSingleton::userList()
{
    QNetworkRequest request;
    request.setUrl(QUrl(m_url+"/user"));
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
    request.setUrl(QUrl(m_url+"/userdetail/"+QString::number(id)));
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
    request.setUrl(QUrl(m_url+"/userdetail/"+QString::number(id)));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QString concatenated = createPWString(m_user, m_pw); //username:password
    QByteArray data = concatenated.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;

    request.setRawHeader("Authorization", headerData.toLocal8Bit());
//    qDebug() << doc.toJson();
    QNetworkReply *reply=m_restClient->put(request, doc.toJson());

    connect(
        reply, &QNetworkReply::finished,
        [=]( )
    {
//        qDebug() << reply->readAll();
        //TODO updateUser to see if changes worked
//        emit userDetailsReceived(id, stringToJsonObject(reply->readAll()));
        reply->deleteLater();
    });
//    qDebug() << reply->readAll();
}

void ApiSingleton::addUser(QJsonDocument doc)
{
    QNetworkRequest request;
    request.setUrl(QUrl(m_url+"/userdetail"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QString concatenated = createPWString(m_user, m_pw); //username:password
    QByteArray data = concatenated.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;

    request.setRawHeader("Authorization", headerData.toLocal8Bit());
    QNetworkReply *reply=m_restClient->post(request, doc.toJson());
    connect(
        reply, &QNetworkReply::finished,
        [=]( )
    {
        qDebug() << reply->readAll();
        this->userList();
        reply->deleteLater();
    });
}

void ApiSingleton::deleteUser(int id)
{
    QNetworkRequest request;
    request.setUrl(QUrl(m_url+"/userdetail/"+QString::number(id)));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QString concatenated = createPWString(m_user, m_pw); //username:password
    QByteArray data = concatenated.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;

    request.setRawHeader("Authorization", headerData.toLocal8Bit());
    QNetworkReply *reply=m_restClient->deleteResource(request);
    connect(
        reply, &QNetworkReply::finished,
        [=]( )
    {
//        qDebug() << reply->readAll();
        this->userList();
        reply->deleteLater();
    });
//    qDebug() << reply->readAll();
}







