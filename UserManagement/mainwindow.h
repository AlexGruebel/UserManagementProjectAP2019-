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
    void initTree(QList<QPair<int, QString> > userList);

    QTreeWidgetItem *addUserValue(QString key, QVariant val, QTreeWidgetItem *parent);
    QTreeWidgetItem *getUserItem() const;
    QTreeWidgetItem *getUserItem();

private:
    Ui::MainWindow *ui;
    int m_admintab = 0;

    QTreeWidgetItem *userItem = new QTreeWidgetItem({"Users", ""});
    QTreeWidgetItem *groupItem = new QTreeWidgetItem({"Groups", ""});
    QTreeWidgetItem *permissionItem = new QTreeWidgetItem({"Permissions", ""});
    void onTreeWidgetItemDoubleClicked(QTreeWidgetItem *item, int column);
    bool isColumnEditable(int column);
signals:
    void userExpanded(int id, QTreeWidgetItem *item);
    void userEdited(int id, QTreeWidgetItem *root);
};

#endif // MAINWINDOW_H
