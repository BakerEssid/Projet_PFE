#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

#include "mainpage.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pushButton_Login_clicked();     // Slot appelé quand on clique sur Login
    void on_pushButton_Cancel_clicked();    // Slot appelé quand on clique sur Cancel


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
