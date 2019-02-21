#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "QDebug"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showAdminTab(bool show)
{
    if(show)
    {
        m_admintab = ui->tabWidget->addTab(ui->adminTab, "Admin");
    }
    else
    {
        ui->tabWidget->removeTab(m_admintab);
    }
}
