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
    explicit MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow();

    void showAdminTab(bool show);
    void initTree();
    void addUserList(QList<QPair<int, QString> > userList);

    QTreeWidgetItem *addUserValue(QString key, QVariant val, QTreeWidgetItem *parent);
    QTreeWidgetItem *getUserItem() const;
    QTreeWidgetItem *getUserItem();

    void blockTreeWidgetSignal(bool val);

    QTreeWidgetItem *getTreeItemFromId(int id);

private:
    Ui::MainWindow *ui;
    int m_admintab = 0;

    QTreeWidgetItem *userItem;
//    QTreeWidgetItem *groupItem = new QTreeWidgetItem({"Groups", ""});
//    QTreeWidgetItem *permissionItem = new QTreeWidgetItem({"Permissions", ""});
    void onTreeWidgetItemDoubleClicked(QTreeWidgetItem *item, int column);
    bool isColumnEditable(int column);
signals:
    void userExpanded(int id);
    void userEdited(int id, QTreeWidgetItem *root);
    void userDeleted(int id);
    void userAdded(QString str);
};

#endif // MAINWINDOW_H
