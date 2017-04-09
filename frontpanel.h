#ifndef FRONTPANEL_H
#define FRONTPANEL_H

#include <QMainWindow>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <canhandler.h>

namespace Ui {
class FrontPanel;
}

class FrontPanel : public QMainWindow
{
    Q_OBJECT

public:
    explicit FrontPanel(QWidget *parent = 0);
    ~FrontPanel();

    void updateValue();
    void startTimer();

public slots:
    void updateValueTimed();


private:
    Ui::FrontPanel *ui;
    CanHandler *can;
    QTimer *timer;

};

#endif // FRONTPANEL_H
