#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "apisingleton.h"

#include "QDebug"

#include <QTreeView>

enum itemTypes
{
    value = 0,
    user = 1
};

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

void MainWindow::initTree(QList<QPair<int, QString>> userList)
{
    ui->treeWidget->addTopLevelItem(userItem);
    ui->treeWidget->addTopLevelItem(groupItem);
    ui->treeWidget->addTopLevelItem(permissionItem);

    connect(
        ui->treeWidget, &QTreeWidget::itemExpanded,
        [=]( QTreeWidgetItem * item )
    {
        if(item->type() == itemTypes::user)
        {
            emit userExpanded(item->data(0, Qt::UserRole).toInt(), item);
        }
        for(int i = 0; i < ui->treeWidget->columnCount(); i++)
        {
            ui->treeWidget->resizeColumnToContents(i);
        }
    });

    for (int var = 0; var < userList.size(); ++var)
    {
        QTreeWidgetItem *item = new QTreeWidgetItem({QString::number(userList.at(var).first), userList.at(var).second}, itemTypes::user);
        item->setData(0, Qt::UserRole, userList.at(var).first);
        item->setChildIndicatorPolicy(QTreeWidgetItem::ShowIndicator);
        userItem->addChild(item);
    }
}

QTreeWidgetItem *MainWindow::addUserValue(QString key, QVariant val, QTreeWidgetItem *parent)
{
    QTreeWidgetItem *item = new QTreeWidgetItem({key, val.toString()}, itemTypes::value);
    parent->addChild(item);
    return item;
}

QTreeWidgetItem *MainWindow::getUserItem() const
{
    return userItem;
}

QTreeWidgetItem *MainWindow::getUserItem()
{
    return userItem;
}








