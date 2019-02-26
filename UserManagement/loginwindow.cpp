#include "loginwindow.h"
#include "ui_loginwindow.h"

#include "apisingleton.h"

#include "QDebug"
#include <QMessageBox>

LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);

    connect(&ApiSingleton::getInstance(), &ApiSingleton::loginReceived, this, &LoginWindow::login);
    connect(
        ui->m_loginButton, &QPushButton::pressed,
        [=](  )
    {
        ApiSingleton::getInstance().login(ui->m_nameLineEdit->text(), ui->m_passwordLineEdit->text());
    });
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::login(int status)
{
    switch (status)
    {
    case 1:
        emit loggedIn(false);
        break;
    case 2:
        emit loggedIn(true);
        break;
    default:
        QMessageBox msgBox;
        msgBox.setText("Invalid Username + Password combination");
        msgBox.exec();
        break;
    }
}

//bool string2bool (const QString &str)
//{
//    return !str.empty () &&
//        (strcasecmp (str.c_str (), "true") == 0 ||
//         atoi (str.c_str ()) != 0);
//}
