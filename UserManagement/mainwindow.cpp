#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "apisingleton.h"

#include "QDebug"

#include <QTreeView>
#include <QMessageBox>
#include <QInputDialog>

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

    connect(
        ui->m_addUserButton, &QPushButton::pressed,
        [=](  )
    {
        bool ok;
        QString text = QInputDialog::getMultiLineText(this, "Json Input field",
                       tr("User Json:"), "", &ok);
        if (ok && !text.isEmpty())
        {
            emit userAdded(text);
        }
    });

    connect(
        ui->m_deleteUserButton, &QPushButton::pressed,
        [=](  )
    {
        bool ok = false;
        int id = ui->m_deleteUserId->text().toInt(&ok, 10);
        if(ok)
        {
            if(id <0)
            {
                QMessageBox msgBox;
                msgBox.setText("Please insert a positiv number");
                msgBox.exec();
            }
            else
            {
                emit userDeleted(id);
            }
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setText("Please insert a number");
            msgBox.exec();
        }
    });
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

void MainWindow::addUserList(QList<QPair<int, QString> > userList)
{
    ui->treeWidget->clear();

    userItem = new QTreeWidgetItem({"Users", ""});
    ui->treeWidget->addTopLevelItem(userItem);
    userItem->setFlags(Qt::ItemIsEditable|Qt::ItemIsEnabled);

    for (int var = 0; var < userList.size(); ++var)
    {
        //item with id and userName (problem, what happens on editing id or userName)
        QTreeWidgetItem *item = new QTreeWidgetItem({QString::number(userList.at(var).first), userList.at(var).second}, itemTypes::user);
        //item without id and userName
//        QTreeWidgetItem *item = new QTreeWidgetItem({"User"}, itemTypes::user);
        item->setData(0, Qt::UserRole, userList.at(var).first);
        item->setChildIndicatorPolicy(QTreeWidgetItem::ShowIndicator);
        item->setFlags(Qt::ItemIsEditable|Qt::ItemIsEnabled);
        userItem->addChild(item);
    }
}

void MainWindow::initTree()
{
    //Not enough time to implement group and permission editing
//    ui->treeWidget->addTopLevelItem(groupItem);
//    ui->treeWidget->addTopLevelItem(permissionItem);

    ui->treeWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

//    groupItem->setFlags(Qt::ItemIsEditable|Qt::ItemIsEnabled);
//    permissionItem->setFlags(Qt::ItemIsEditable|Qt::ItemIsEnabled);

    connect(
        ui->treeWidget, &QTreeWidget::itemExpanded,
        [=]( QTreeWidgetItem * item )
    {
        if(item->type() == itemTypes::user)
        {
            foreach(auto i, item->takeChildren()) delete i;
            emit userExpanded(item->data(0, Qt::UserRole).toInt());
        }
        for(int i = 0; i < ui->treeWidget->columnCount(); i++)
        {
            ui->treeWidget->resizeColumnToContents(i);
        }
    });

    connect(ui->treeWidget, &QTreeWidget::itemDoubleClicked,
            [=](QTreeWidgetItem *item, int column)
    {
        if(isColumnEditable(column))
        {
            if(item->text(0).toLower() == "id")
            {
                QMessageBox msgBox;
                msgBox.setText("ID is not editable!");
                msgBox.exec();
            }
            else if (item->childCount() > 0)
            {
                //No parent editing
            }
            else if (item->type() == itemTypes::value)
            {
                ui->treeWidget->editItem(item, column);
            }
        }
    });

    connect(ui->treeWidget, &QTreeWidget::itemChanged,
            [=](QTreeWidgetItem *item, int column)
    {
        qDebug() << "item edited";
        QTreeWidgetItem *superParent = item;
        while(superParent->parent() != Q_NULLPTR && superParent->type() != itemTypes::user)
        {
            superParent = superParent->parent();
        }
        emit userEdited(superParent->data(0, Qt::UserRole).toInt(), superParent->child(0));
    });
}

QTreeWidgetItem *MainWindow::getUserItem() const
{
    return userItem;
}

QTreeWidgetItem *MainWindow::getUserItem()
{
    return userItem;
}

void MainWindow::blockTreeWidgetSignal(bool val)
{
    ui->treeWidget->blockSignals(val);
}

QTreeWidgetItem *MainWindow::getTreeItemFromId(int id)
{
    for (int i = 0; i < userItem->childCount(); ++i)
    {
        QTreeWidgetItem *child = userItem->child(i);
        if(child->data(0, Qt::UserRole) == id)
        {
            return child;
        }

    }
    return Q_NULLPTR;
}

bool MainWindow::isColumnEditable(int column)
{
    switch (column)
    {
    case 0:
        return false;
    default:
        return true;
    }
}




