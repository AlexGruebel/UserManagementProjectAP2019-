#include "apisingleton.h"
#include <QtNetwork/QNetworkAccessManager>

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
