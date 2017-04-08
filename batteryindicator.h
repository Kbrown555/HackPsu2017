#ifndef BATTERYINDICATOR_H
#define BATTERYINDICATOR_H
#include <QDialog>


namespace Ui{
class BatteyIndicator;
}

class BatteryIndicator:public QDialog{
    Q_OBJECT

public:
    explicit BatteryIndicator(QWidget *parent =0);
    ~BatteryIndicator();

    void setValue(int val);
private:
    Ui::BatteyIndicator *ui;
    void setupGeneral();




};



#endif // BATTERYINDICATOR_H

