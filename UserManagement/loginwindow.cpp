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
        ApiSingleton::getInstance().login(ui->m_nameLineEdit->text(), ui->m_passwordLineEdit->text(), ui->m_serverLineEdit->text());
    });
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::login(ApiSingleton::loginReply status)
{
    QMessageBox msgBox;
    switch (status)
    {
    case ApiSingleton::loginUser:
        emit loggedIn(false);
        break;
    case ApiSingleton::loginAdmin:
        emit loggedIn(true);
        break;
    case ApiSingleton::authenticationError:
        msgBox.setText("Invalid Username + Password combination");
        msgBox.exec();
        break;
    case ApiSingleton::serverError:
        msgBox.setText("Invalid Server Address");
        msgBox.exec();
        break;
    default:
        msgBox.setText("An Error occured. Please contact your system administrator");
        msgBox.exec();
        break;
    }
}

