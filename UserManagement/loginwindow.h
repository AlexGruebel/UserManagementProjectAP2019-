#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>

#include "apisingleton.h"

namespace Ui
{
class LoginWindow;
}

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private:
    Ui::LoginWindow *ui;
    void login(ApiSingleton::loginReply status);

signals:
    void loggedIn(bool admin);
};

#endif // LOGINWINDOW_H
