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
        itemsFromJson(json, root);
    });

    connect(
        ui, &MainWindow::userEdited,
        [=]( int id, QTreeWidgetItem *root )
    {
        QJsonDocument obj = toJson(root);
        m_api->sendUserDetails(id, obj);

    });
}

void Controll::itemsFromJson(QJsonValue jsonRoot, QTreeWidgetItem *treeRoot)
{
    QJsonArray array = jsonRoot.toObject().value("items").toArray();
    ui->blockTreeWidgetSignal(true);
    treeRoot->addChild(recursiveJsonToTree(array.at(0), treeRoot));
    ui->blockTreeWidgetSignal(false);

    //Debug
//    foreach(const QString& key, obj.keys())
//    {
//        QJsonValue value = obj.value(key);
//        qDebug() << "Key = " << key << ", Value = " << value.toInt();
//    }
}

QTreeWidgetItem* Controll::recursiveJsonToTree(const QJsonValue& value, QTreeWidgetItem* parent)
{
    QTreeWidgetItem * rootItem = new QTreeWidgetItem(parent);
    rootItem->setFlags(Qt::ItemIsEditable|Qt::ItemIsEnabled);
    rootItem->setText(0, "");

    if (value.isObject())
    {
        foreach(const QString& key, value.toObject().keys())
        {
            QJsonValue v = value.toObject().value(key);
            QTreeWidgetItem * child = recursiveJsonToTree(v,rootItem);
            child->setFlags(Qt::ItemIsEditable|Qt::ItemIsEnabled);
            child->setText(0, key);
            rootItem->addChild(child);
        }
    }
    else if (value.isArray())
    {
        foreach(QJsonValue v, value.toArray())
        {
            QTreeWidgetItem * child = recursiveJsonToTree(v,rootItem);
            child->setFlags(Qt::ItemIsEditable|Qt::ItemIsEnabled);
            child->setText(0, "");
            rootItem->addChild(child);
        }
    }
    else
    {
        rootItem->setText(1, value.toVariant().toString());
        rootItem->setData(1, Qt::UserRole, value.type());
    }
    return rootItem;
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

QJsonDocument Controll::toJson(QTreeWidgetItem *root)
{
    QJsonValue out = recursiveTreeToJson(root);
    if(out.isArray())
    {
        return QJsonDocument(out.toArray());
    }
    else
    {
        return QJsonDocument(out.toObject());
    }
}
QJsonValue Controll::recursiveTreeToJson(QTreeWidgetItem *item)
{
    if(item->childCount() == 0)
    {
        //termination condition, only value
        if(item->data(1, Qt::UserRole) == QJsonValue::Double)
        {
            return QJsonValue(item->text(1).toDouble());
        }
        else if(item->data(1, Qt::UserRole) == QJsonValue::Null)
        {
            return QJsonValue();
        }
        else
        {
            return QJsonValue(item->text(1));
        }

    }
    else
    {
        //child has no name -> array
        if(item->child(0)->text(0) == "")
        {
            QJsonArray array;
            for (int i = 0; i < item->childCount(); ++i)
            {
                array.append(recursiveTreeToJson(item->child(i)));
            }
            return array;
        }
        //item has children and is not an array -> object
        else
        {
            QJsonObject obj;
            for (int i = 0; i < item->childCount(); ++i)
            {
                obj.insert(item->child(i)->text(0), recursiveTreeToJson(item->child(i)));
            }
            return obj;
        }
    }
}










