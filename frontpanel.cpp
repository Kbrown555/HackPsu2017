#include "frontpanel.h"
#include "ui_frontpanel.h"

FrontPanel::FrontPanel(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FrontPanel)
{
    ui->setupUi(this);
    ui->temp_prog->setOrientation(Qt::Vertical);
    ui->SOC_prog->setRange(0,100);
    ui->temp_prog->setRange(0,85);

    ui->current_regen->setInvertedAppearance(true);
    ui->current_regen->setTextVisible(false);
    ui->current_discharge->setTextVisible(false);
    ui->current_regen->setValue(25);
    ui->current_discharge->setValue(10);

    can= new CanHandler();


}

FrontPanel::~FrontPanel()
{
    delete ui;
}

void FrontPanel::startTimer(){
    timer= new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(updateValueTimed()));
    timer->start(100);
}

void FrontPanel::updateValue(){
    QString basestr="QProgressBar{border: 2px solid grey;border-radius: 3px;text-align: center;background:grey;color:white;}";
    QString allgood="QProgressBar::chunk {background-color: green;border-radius: 5px;}";

    double newSOC= 0,newTemp=0,newCurr=0;
    can->getData(newSOC,newCurr);

    ui->SOC_prog->setValue(newSOC);
    ui->SOC_prog->setStyleSheet(allgood.append(basestr));

    can->getTempData(newTemp);
    ui->temp_prog->setValue(newTemp);
    ui->temp_prog->setFormat(QString::number(newTemp)+QString::fromUtf8("°C"));
}

void FrontPanel::updateValueTimed(){
    QString basestr="QProgressBar{border: 2px solid grey;border-radius: 3px;text-align: center;background:grey;color:white;}";
    QString allgood="QProgressBar::chunk {background-color: green;border-radius: 5px;}";

    double newSOC= 0,newTemp=0,newCurr=0;
    can->getData(newSOC,newCurr);

    ui->SOC_prog->setValue(newSOC);
    ui->SOC_prog->setFormat(QString().sprintf("%.1f%",newSOC));
    ui->SOC_prog->setStyleSheet(allgood.append(basestr));

    if(newCurr<0){              //discharge
        ui->current_discharge->setValue(-newCurr);
        ui->current_regen->setValue(0);
    }
    else{
        ui->current_discharge->setValue(0);
        ui->current_regen->setValue(newCurr);
    }
    can->getTempData(newTemp);

    ui->temp_prog->setValue(newTemp);
    ui->temp_prog->setFormat(QString::number(newTemp)+QString::fromUtf8("°C"));

}
