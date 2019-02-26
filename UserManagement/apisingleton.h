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

    void login(QString user, QString pw);
    void userList();
    void userDetails(int id);
    void sendUserDetails(int id, QJsonDocument doc);
private:
    ApiSingleton();
    ~ApiSingleton()= default;
    ApiSingleton(const ApiSingleton&)= delete;
    ApiSingleton& operator=(const ApiSingleton&)= delete;

    QJsonObject stringToJsonObject(QString s);

    QNetworkAccessManager *m_restClient;

    QString m_user = "";
    QString m_pw = "";
    QString createPWString(QString user, QString pw);

signals:
    void userListReceived(QJsonObject list);
    void userDetailsReceived(int id, QJsonObject details);
    void loginReceived(int status);
};

#endif // APISINGLETON_H
