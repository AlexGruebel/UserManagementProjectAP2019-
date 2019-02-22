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

    QTreeWidgetItem *addUserValue(QString key, QVariant val, QTreeWidgetItem *parent);
private:
    Ui::MainWindow *ui;
    int m_admintab = 0;

    QTreeWidgetItem *userItem = new QTreeWidgetItem({"Users", ""});
    QTreeWidgetItem *groupItem = new QTreeWidgetItem({"Groups", ""});
    QTreeWidgetItem *permissionItem = new QTreeWidgetItem({"Permissions", ""});

signals:
    void userExpanded(int id, QTreeWidgetItem *item);
};

#endif // MAINWINDOW_H
