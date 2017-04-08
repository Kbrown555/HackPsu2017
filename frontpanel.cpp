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
    ui->current_regen->setFormat("");
    ui->current_discharge->setFormat("");
    ui->current_regen->setValue(25);
    ui->current_discharge->setValue(10);

    can= new CanHandler();


}

FrontPanel::~FrontPanel()
{
    delete ui;
}



void FrontPanel::updateValue(){
    QString basestr="QProgressBar{border: 2px solid grey;border-radius: 3px;text-align: center;background:grey;color:white;}";
    QString allgood="QProgressBar::chunk {background-color: green;border-radius: 5px;}";

    double newSOC= 97;
    can->getData(newSOC);

    ui->SOC_prog->setValue(newSOC);
    ui->SOC_prog->setStyleSheet(allgood.append(basestr));


    ui->temp_prog->setValue(34);
    ui->temp_prog->setFormat(QString::number(34)+QString::fromUtf8("°C"));
}
