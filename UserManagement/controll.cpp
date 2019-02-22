#include "controll.h"
#include "ui_mainwindow.h"
#include <QDebug>

#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>

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

    connect(
        ui, &MainWindow::userExpanded,
        [=]( int id, QTreeWidgetItem *root )
    {
        QJsonObject json = m_api->userDetails(id);
        JsonTree(json, root);
    });
}

void Controll::JsonTree(QJsonObject jsonRoot, QTreeWidgetItem *treeRoot)
{

    QJsonArray array = jsonRoot.value("items").toArray();
    QJsonObject obj = (array.at(0).toObject());
    recursiveJsonObject(obj, treeRoot);

    //Debug
//    foreach(const QString& key, obj.keys())
//    {
//        QJsonValue value = obj.value(key);
//        qDebug() << "Key = " << key << ", Value = " << value.toInt();
//    }
}

void Controll::recursiveJsonObject(QJsonObject obj, QTreeWidgetItem *i)
{
    foreach(const QString& key, obj.keys())
    {
        QJsonValue value = obj.value(key);
        if(value.isArray())
        {
            QTreeWidgetItem *newGroup = ui->addUserValue(key, "", i);
            recursiveJsonArray(value.toArray(), newGroup);
        }
        else
        {
            ui->addUserValue(key, value.toVariant(), i);
        }
    }
}

void Controll::recursiveJsonArray(QJsonArray array, QTreeWidgetItem *i)
{
    foreach (QJsonValue val, array)
    {
        if(val.isObject())
        {
            QJsonObject child = (val.toObject());
            recursiveJsonObject(child, i);
        }
        else if(val.isArray())
        {
            recursiveJsonArray(val.toArray(), i);
        }
        else
        {
            ui->addUserValue("", val.toVariant(), i);
        }
    }
}













