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
    /**
     * @brief LoginWindow basic constructor
     * @param parent
     */
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private:
    Ui::LoginWindow *ui;
    /**
     * @brief login method to react to an loggin try
     * @param status status of the login try
     */
    void login(ApiSingleton::loginReply status);

signals:
    /**
     * @brief loggedIn signal emiting a successfull login
     * @param admin logged in as admin or user
     */
    void loggedIn(bool admin);
};

#endif // LOGINWINDOW_H
