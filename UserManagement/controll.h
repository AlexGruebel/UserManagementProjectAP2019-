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

    void JsonTree(QJsonObject jsonRoot, QTreeWidgetItem *treeRoot);
    void recursiveJsonObject(QJsonObject obj, QTreeWidgetItem *i);
    void recursiveJsonArray(QJsonArray array, QTreeWidgetItem *i);
    QList<QPair<int, QString>> jsonToUsers(QJsonObject jsonRoot);
private slots:
    void initMainWindow(bool admin = false);
};

#endif // CONTROLL_H
