#ifndef APISINGLETON_H
#define APISINGLETON_H

#include <QObject>
#include <QList>
#include <QPair>
#include <QJsonObject>

#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>

class ApiSingleton : public QObject
{
    Q_OBJECT
public:
    static ApiSingleton& getInstance();

    void userList();
    QJsonObject userDetails(int id);
    void sendUserDetails(int id, QJsonDocument doc);
private:
    ApiSingleton();
    ~ApiSingleton()= default;
    ApiSingleton(const ApiSingleton&)= delete;
    ApiSingleton& operator=(const ApiSingleton&)= delete;

    QJsonObject stringToJsonObject(QString s);

    QNetworkAccessManager *m_restClient;

signals:
    void userListReceived(QJsonObject list);
};

#endif // APISINGLETON_H
