#ifndef ECOCAR_H
#define ECOCAR_H

#include <QTabWidget>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <canhandler.h>

namespace Ui {
class EcoCAR;
}

class EcoCAR : public QTabWidget
{
    Q_OBJECT

public:
    explicit EcoCAR(QWidget *parent = 0);
    ~EcoCAR();

    void updateValue();
    void startTimer();

public slots:
    void updateValueTimed();
private:
    Ui::EcoCAR *ui;
    CanHandler *can;
    QTimer *timer;
};

#endif // ECOCAR_H
