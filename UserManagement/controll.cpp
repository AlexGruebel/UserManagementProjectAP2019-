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
    else
    {
        ui->showAdminTab(false);
    }
    ui->setWindowTitle("User Administration Tool");
    ui->show();

    ui->initTree();

    connect(
        m_api, &ApiSingleton::userListReceived,
        [=]( QJsonObject obj )
    {
        ui->blockTreeWidgetSignal(true);
        ui->addUserList(jsonToUsers(obj));
        ui->blockTreeWidgetSignal(false);
    });

    m_api->userList();

    connect(
        m_api, &ApiSingleton::userDetailsReceived,
        [=]( int id, QJsonObject obj )
    {
        detailsFromJson(obj, ui->getTreeItemFromId(id));
    });

    connect(
        ui, &MainWindow::userExpanded,
        [=]( int id)
    {
        m_api->userDetails(id);
    });

    connect(
        ui, &MainWindow::userEdited,
        [=]( int id, QTreeWidgetItem *root )
    {
        QJsonDocument obj = toJson(root);
        m_api->sendUserDetails(id, obj);

    });

    connect(
        ui, &MainWindow::userDeleted,
        [=]( int id )
    {
        m_api->deleteUser(id);
    });

    connect(
        ui, &MainWindow::userAdded,
        [=]( QString str )
    {
        QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8());
        if(doc.isNull())
        {
            qDebug() << "Json not valid";
        }
        m_api->addUser(doc);
    });
}

void Controll::detailsFromJson(QJsonValue jsonRoot, QTreeWidgetItem *treeRoot)
{
    ui->blockTreeWidgetSignal(true);
    treeRoot->addChild(recursiveJsonToTree(jsonRoot, treeRoot));
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










