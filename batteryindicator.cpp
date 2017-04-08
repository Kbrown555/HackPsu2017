#include "batteryindicator.h"
#include "ui_batteryindicator.h"

BatteryIndicator::BatteryIndicator(QWidget *parent):
    QDialog(parent),
    ui(new Ui::BatteyIndicator),
    deviceInfo(NULL)
{
    ui->setupUi(this);
    setupGeneral();
}

BatteryIndicator::~BatteryIndicator(){
    delete ui;
}
void BatteryIndicator::setupGeneral(){

}

void BatteryIndicator::setValue(int val){

}
