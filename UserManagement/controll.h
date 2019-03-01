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
    /**
     * @brief Controll basic constructor
     * @param parent
     */
    explicit Controll(QObject *parent = nullptr);
    virtual ~Controll();
private:
    LoginWindow *w;
    MainWindow *ui;
    ApiSingleton *m_api;

    /**
     * @brief detailsFromJson converting a json document to a treebased strcture
     * This conversion is dynamic. It doesn't matter what is inside the json document
     * (as long as the json document is valid)
     * @param jsonRoot the json document to be converted
     * @param [in/out] treeRoot the root element the newly generated tree structure should be appended to
     */
    void detailsFromJson(QJsonValue jsonRoot, QTreeWidgetItem *treeRoot);
    /**
     * @brief recursiveJsonToTree help method to recursivly parse over a json document and generate a tree from it
     * @param value the json value containing a value/object/array
     * @param parent the last tree parent
     * @return
     */
    QTreeWidgetItem* recursiveJsonToTree(const QJsonValue &value, QTreeWidgetItem* parent);

    /**
     * @brief jsonToUsers converts a QJsonObject to a List
     * @param jsonRoot
     * @return the newly created root item
     */
    QList<QPair<int, QString>> jsonToUsers(QJsonObject jsonRoot);

    /**
     * @brief toJson generating a json document from a tree
     * @param root the tree root element
     * @return the generated document
     */
    QJsonDocument toJson(QTreeWidgetItem *root);

    /**
     * @brief recursiveTreeToJson helper method to generate a json value from a tree
     * @param item the tree item to be converted to a json value
     * @return the generated json object
     */
    QJsonValue recursiveTreeToJson(QTreeWidgetItem *item);

private slots:
    /**
     * @brief creating and connecting the mainwindow
     * @param admin logged in as admin or user
     */
    void initMainWindow(bool admin = false);
};

#endif // CONTROLL_H
