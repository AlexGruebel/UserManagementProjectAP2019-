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

    QList<QPair<int, QString>> userList();
private:
    ApiSingleton();
    ~ApiSingleton()= default;
    ApiSingleton(const ApiSingleton&)= delete;
    ApiSingleton& operator=(const ApiSingleton&)= delete;

};

#endif // APISINGLETON_H
