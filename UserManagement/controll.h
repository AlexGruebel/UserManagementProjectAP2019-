#ifndef CONTROLL_H
#define CONTROLL_H

#include "loginwindow.h"
#include "mainwindow.h"
#include "apisingleton.h"

#include <QObject>

class Controll : public QObject
{
    Q_OBJECT
public:
    explicit Controll(QObject *parent = nullptr);
    virtual ~Controll();
private:
    LoginWindow *w;
    MainWindow *ui;
    ApiSingleton *m_api;

    void itemsFromJson(QJsonValue jsonRoot, QTreeWidgetItem *treeRoot);
    QTreeWidgetItem* recursiveJsonToTree(const QJsonValue &value, QTreeWidgetItem* parent);

    QList<QPair<int, QString>> jsonToUsers(QJsonObject jsonRoot);

    QJsonDocument toJson(QTreeWidgetItem *root);
    QJsonValue recursiveTreeToJson(QTreeWidgetItem *item);

private slots:
    void initMainWindow(bool admin = false);
};

#endif // CONTROLL_H
