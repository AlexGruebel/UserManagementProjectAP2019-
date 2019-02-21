#include "loginwindow.h"
#include "ui_loginwindow.h"

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
    qDebug() << "Login Pressed";
    //insert access to rest api

    emit loggedIn(true);
}
