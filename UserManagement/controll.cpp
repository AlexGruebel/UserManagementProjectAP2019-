#include "controll.h"
#include "ui_mainwindow.h"
#include <QDebug>

Controll::Controll(QObject *parent) :
    m_api(&ApiSingleton::getInstance())
{
    w = new LoginWindow();
    w->setWindowTitle("User Administration Login");
    w->show();
//    connect(
//        w, &LoginWindow::loggedIn,
//        this, &Controll::initMainWindow
//    );
    connect(
        w, &LoginWindow::loggedIn,
        [=]( bool admin )
    {
        this->initMainWindow(admin);
    }
    );
}

Controll::~Controll()
{

}

void Controll::initMainWindow(bool admin)
{
    //remove login window
    if(w)
    {
        w->hide();
        delete w;
    }
    ui = new MainWindow();
    if(admin)
    {
        ui->showAdminTab(true);
    }
    ui->setWindowTitle("User Administration Tool");
    ui->show();

    ui->initTree();

}
