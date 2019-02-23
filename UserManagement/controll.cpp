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

    ui->initTree(jsonToUsers(m_api->userList()));

    connect(
        ui, &MainWindow::userExpanded,
        [=]( int id, QTreeWidgetItem *root )
    {
        QJsonObject json = m_api->userDetails(id);
        JsonTree(json, root);
    });

    connect(
        ui, &MainWindow::userEdited,
        [=]( int id, QTreeWidgetItem *root )
    {

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

QList<QPair<int, QString>> Controll::jsonToUsers(QJsonObject jsonRoot)
{
    QJsonArray array = jsonRoot.value("items").toArray();
    QList<QPair<int, QString>> outputList;
    foreach (QJsonValue val, array)
    {
        if(val.isObject())
        {
            QPair<int, QString> pair(val.toObject().value("id").toInt(-1),
                                     val.toObject().value("userName").toString("NO NAME"));
            outputList.append(pair);
        }
        else
        {
            qCritical() << "Invalid User List";
        }
    }
    return outputList;
}

//QJsonDocument Controll::toJson()
//{

//    auto v = genJson(mRootItem);
//    QJsonDocument doc;

//    if (v.isObject()) {
//        doc = QJsonDocument(v.toObject());
//    } else {
//        doc = QJsonDocument(v.toArray());
//    }

//    return doc;
//}

//QJsonValue  Controll::generateJson(QTreeWidgetItem *item)
//{
//    int  children = item->childCount();

//    if(children == 0)
//    {

//    }
//    if (QJsonValue::Object == type) {
//        QJsonObject jo;
//        for (int i = 0; i < nchild; ++i) {
//            auto ch = item->child(i);
//            auto key = ch->key();
//            jo.insert(key, genJson(ch));
//        }
//        return  jo;
//    } else if (QJsonValue::Array == type) {
//        QJsonArray arr;
//        for (int i = 0; i < nchild; ++i) {
//            auto ch = item->child(i);
//            arr.append(genJson(ch));
//        }
//        return arr;
//    } else {
//        QJsonValue va(item->value());
//        return va;
//}











