#include "batteryindicator1.h"
#include "ui_batteryindicator1.h"

BatteryIndicator1::BatteryIndicator1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BatteryIndicator1)
{
    ui->setupUi(this);
}

BatteryIndicator1::~BatteryIndicator1()
{
    delete ui;
}
