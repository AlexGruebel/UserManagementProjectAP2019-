#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private:
    Ui::MainWindow *ui;
    int m_admintab = 0;

signals:

};

#endif // MAINWINDOW_H
