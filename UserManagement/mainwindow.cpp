#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "apisingleton.h"

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

void MainWindow::initTree()
{
    ui->treeWidget->addTopLevelItem(userItem);
    ui->treeWidget->addTopLevelItem(groupItem);
    ui->treeWidget->addTopLevelItem(permissionItem);

    QList<QPair<int, QString>> list = ApiSingleton::getInstance().userList();

    for (int var = 0; var < list.size(); ++var)
    {
        userItem->addChild(new QTreeWidgetItem({QString::number(list.at(var).first), list.at(var).second}));
    }
    userItem->
}
