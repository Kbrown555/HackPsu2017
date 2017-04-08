#ifndef BATTERYINDICATOR1_H
#define BATTERYINDICATOR1_H

#include <QWidget>

namespace Ui {
class BatteryIndicator1;
}

class BatteryIndicator1 : public QWidget
{
    Q_OBJECT

public:
    explicit BatteryIndicator1(QWidget *parent = 0);
    ~BatteryIndicator1();

private:
    Ui::BatteryIndicator1 *ui;
};

#endif // BATTERYINDICATOR1_H
