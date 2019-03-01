#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief MainWindow basic constructor
     * @param parent
     */
    explicit MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow();

    /**
     * @brief showAdminTab display or disable the admin tab
     * @param show true to show, false to disable
     */
    void showAdminTab(bool show);
    /**
     * @brief initTree connect treewidget to code
     */
    void initTree();
    /**
     * @brief addUserList add a list of users to the treewidget
     * @param userList the list to be added containing id and name
     */
    void addUserList(QList<QPair<int, QString> > userList);

    /**
     * @brief getUserItem getter for UserItem
     * @return userItem as const
     */
    QTreeWidgetItem *getUserItem() const;
    /**
     * @brief getUserItem getter for userItem
     * @return editable userItem
     */
    QTreeWidgetItem *getUserItem();

    /**
     * @brief blockTreeWidgetSignal block blocks all signals from the TreeWidget
     * @param val ture for block, false for unblocking
     */
    void blockTreeWidgetSignal(bool val);

    /**
     * @brief getTreeItemFromId searches for the user in the tree with the id
     * @param id of the user
     * @return Null if no Widget was found, else the TreeWidget of the User
     */
    QTreeWidgetItem *getTreeItemFromId(int id);

private:
    Ui::MainWindow *ui;
    int m_admintab = 0;

    QTreeWidgetItem *userItem;
    //Not enough time to implement groups and permissions
//    QTreeWidgetItem *groupItem = new QTreeWidgetItem({"Groups", ""});
//    QTreeWidgetItem *permissionItem = new QTreeWidgetItem({"Permissions", ""});

    /**
     * @brief onTreeWidgetItemDoubleClicked method to connect the double click event to
     * @param item that was clicked
     * @param column column that was clicked
     */
    void onTreeWidgetItemDoubleClicked(QTreeWidgetItem *item, int column);
    /**
     * @brief isColumnEditable method returning of a specific column is editable
     * @param column you want to know if it is editable
     * @return true if editable, else false
     */
    bool isColumnEditable(int column);
signals:
    /**
     * @brief userExpanded signal if a user TreeItem was expanded
     * @param id of the user that was expanded
     */
    void userExpanded(int id);
    /**
     * @brief userEdited signal when a value was edited
     * @param id of the user that was edited
     * @param root the treeitem that was edited
     */
    void userEdited(int id, QTreeWidgetItem *root);
    /**
     * @brief userDeleted signal when a user is deleted
     * @param id of the user to be deleted
     */
    void userDeleted(int id);
    /**
     * @brief userAdded signal when a user is added
     * @param str Json String describing the new user
     */
    void userAdded(QString str);
};

#endif // MAINWINDOW_H
