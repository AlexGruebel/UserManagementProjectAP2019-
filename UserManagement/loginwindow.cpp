#include "loginwindow.h"
#include "ui_loginwindow.h"

#include "apisingleton.h"

#include "QDebug"

LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    connect(ui->m_loginButton, &QPushButton::pressed, this, &LoginWindow::login);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::login()
{
    ApiSingleton::getInstance().login(ui->m_nameLineEdit->text(), ui->m_passwordLineEdit->text());

    emit loggedIn(true);
}
