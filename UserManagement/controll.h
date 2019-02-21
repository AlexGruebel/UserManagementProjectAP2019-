#ifndef CONTROLL_H
#define CONTROLL_H

#include <QObject>
#include "loginwindow.h"
#include "mainwindow.h"
#include "apisingleton.h"

class Controll : public QObject
{
    Q_OBJECT
public:
    explicit Controll(QObject *parent = nullptr);
    virtual ~Controll();
private:
    LoginWindow *w;
    MainWindow *ui;
    ApiSingleton *m_api;

private slots:
    void initMainWindow(bool admin = false);
};

#endif // CONTROLL_H
