#include "apisingleton.h"
#include <QtNetwork/QNetworkAccessManager>

static const QString url = "localhost";

ApiSingleton &ApiSingleton::getInstance()
{
    static ApiSingleton instance;
    return instance;
}

QList<QPair<int, QString> > ApiSingleton::userList()
{
    //DEBUG
    QList<QPair<int, QString> > list = { {0,"one"}, {1,"two"}, {2,"three"} };
    return list;
}

ApiSingleton::ApiSingleton()
{
    QNetworkAccessManager *restclient; //in class
    restclient = new QNetworkAccessManager(this); //constructor
//    QNetworkReply *reply = restclient->post(request,payload);
//    qDebug() << reply->readAll();
}
