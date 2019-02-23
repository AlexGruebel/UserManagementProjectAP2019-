#ifndef APISINGLETON_H
#define APISINGLETON_H

#include <QObject>
#include <QList>
#include <QPair>

class ApiSingleton : public QObject
{
    Q_OBJECT
public:
    static ApiSingleton& getInstance();

    QJsonObject userList();
    QJsonObject userDetails(int id);
private:
    ApiSingleton();
    ~ApiSingleton()= default;
    ApiSingleton(const ApiSingleton&)= delete;
    ApiSingleton& operator=(const ApiSingleton&)= delete;

    QJsonObject stringToJsonObject(QString s);
};

#endif // APISINGLETON_H
