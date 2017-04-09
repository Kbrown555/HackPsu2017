#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <canhandler.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


    void startTimer();

public slots:
    void updateValueTimed();
private:
    Ui::MainWindow *ui;
    CanHandler *can;
    QTimer *timer;
};

#endif // MAINWINDOW_H
