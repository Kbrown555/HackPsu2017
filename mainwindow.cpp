#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent,Qt::FramelessWindowHint),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->temp_prog->setOrientation(Qt::Vertical);
    ui->SOC_prog->setRange(0,100);
    ui->temp_prog->setRange(0,85);

    ui->current_regen->setInvertedAppearance(true);
    ui->current_regen->setTextVisible(false);
    ui->current_discharge->setTextVisible(false);
    ui->current_regen->setRange(0,100);
    ui->current_discharge->setRange(0,300);
    ui->regen_num->setSegmentStyle(QLCDNumber::Filled);
    ui->dischargenum->setSegmentStyle(QLCDNumber::Filled);
    ui->regen_num->setPalette(Qt::green);
    ui->dischargenum->setPalette(QColor::fromRgb(251,90,11));
    ui->regen_num->setNumDigits(3);
    ui->dischargenum->setNumDigits(4);

    can= new CanHandler();
    startTimer();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startTimer(){
    timer= new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(updateValueTimed()));
    timer->start(100);
}



void MainWindow::updateValueTimed(){
    QString basestr="QProgressBar{border: none;border-radius: 3px;text-align: center;background:black;color:white;}";
    QString allgood="QProgressBar::chunk {background-color: green;border-radius: 3px;}";
    QString notgood="QProgressBar::chunk {background-color: red;border-radius: 3px;}";

    double newSOC= 0,newTemp=0,newCurr=0;
    can->getData(newSOC,newCurr);

    ui->SOC_prog->setValue(newSOC);
    ui->SOC_prog->setFormat(QString().sprintf("%.1f%",newSOC));
    if(newSOC>20)
        ui->SOC_prog->setStyleSheet(allgood.append(basestr));
    else
        ui->SOC_prog->setStyleSheet(notgood.append(basestr));

    if(newCurr<0){              //discharge
        ui->current_discharge->setValue(-newCurr);
        ui->dischargenum->display(newCurr);
        ui->regen_num->setVisible(false);
        ui->dischargenum->setVisible(true);
        ui->current_regen->setValue(0);
    }
    else{
        ui->current_discharge->setValue(0);
        ui->dischargenum->setVisible(false);
        ui->regen_num->display(newCurr);
        ui->regen_num->setVisible(true);
        ui->current_regen->setValue(newCurr);
    }
    can->getTempData(newTemp);

    ui->temp_prog->setValue(newTemp);
    ui->temp_prog->setFormat(QString::number(newTemp)+QString::fromUtf8("°C"));

}

