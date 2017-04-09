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
    ui->fatboy->setVisible(false);
    ui->progressBar->setTextVisible(false);
    ui->progressBar->setValue(100);
    ui->orb1->setValue(100);
    ui->orb1->setTextVisible(false);
    ui->orb1_8->setValue(100);
    ui->orb1_8->setTextVisible(false);
    ui->orb1_2->setValue(100);
    ui->orb1_2->setTextVisible(false);
    ui->orb1_3->setValue(100);
    ui->orb1_3->setTextVisible(false);
    ui->orb1_4->setValue(100);
    ui->orb1_4->setTextVisible(false);
    ui->orb1_5->setValue(100);
    ui->orb1_5->setTextVisible(false);
    ui->orb1_6->setValue(100);
    ui->orb1_6->setTextVisible(false);
    ui->orb1_7->setValue(100);
    ui->orb1_7->setTextVisible(false);
    ui->orb1_9->setValue(100);
    ui->orb1_9->setTextVisible(false);
    can= new CanHandler();
    startTimer();
    timerShaftOrb= new QTimer(this);
    connect(timerShaftOrb,SIGNAL(timeout()),this,SLOT(updateShaftOrbs()));
    timerShaftOrb->start(252);
    orbDischarge= new QTimer(this);
    connect(orbDischarge,SIGNAL(timeout()),this,SLOT(updateOrbs()));
    orbDischarge->start(315);


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
        ui->fatboy->setVisible(true);
        ui->dischargearrow->setVisible(true);
        ui->skinnyboy->setVisible(false);
        ui->chargarrow->setVisible(false);
        regen=false;
    }
    else{
        ui->current_discharge->setValue(0);
        ui->dischargenum->setVisible(false);
        ui->regen_num->display(newCurr);
        ui->regen_num->setVisible(true);
        ui->current_regen->setValue(newCurr);
        ui->fatboy->setVisible(false);
        ui->chargarrow->setVisible(true);
        ui->skinnyboy->setVisible(true);
        ui->dischargearrow->setVisible(false);
        regen=true;
    }
    can->getTempData(newTemp);

    ui->temp_prog->setValue(newTemp);
    ui->temp_prog->setFormat(QString::number(newTemp)+QString::fromUtf8("°C"));

}



void MainWindow::updateOrbs(){
    static int currOrb=0;
    if(!regen){
    switch(currOrb){
    case 0:
        ui->orb1->setVisible(true);
        ui->orb1_2->setVisible(false);
        ui->orb1_3->setVisible(false);
        ui->orb1_4->setVisible(false);
        currOrb=1;
        break;
    case 1:
        ui->orb1->setVisible(false);
        ui->orb1_2->setVisible(true);
        ui->orb1_3->setVisible(false);
        ui->orb1_4->setVisible(false);
        currOrb=2;
        break;
    case 2:
        ui->orb1->setVisible(false);
        ui->orb1_2->setVisible(false);
        ui->orb1_3->setVisible(true);
        ui->orb1_4->setVisible(false);
        currOrb=3;
        break;
    default:
        ui->orb1->setVisible(false);
        ui->orb1_2->setVisible(false);
        ui->orb1_3->setVisible(false);
        ui->orb1_4->setVisible(true);
        currOrb=0;
        break;
    }
    }
    else{
        switch(currOrb){
        case 0:
            ui->orb1->setVisible(false);
            ui->orb1_2->setVisible(false);
            ui->orb1_3->setVisible(false);
            ui->orb1_4->setVisible(true);
            currOrb=1;
            break;
        case 1:
            ui->orb1->setVisible(false);
            ui->orb1_2->setVisible(false);
            ui->orb1_3->setVisible(true);
            ui->orb1_4->setVisible(false);
            currOrb=2;
            break;
        case 2:
            ui->orb1->setVisible(false);
            ui->orb1_2->setVisible(true);
            ui->orb1_3->setVisible(false);
            ui->orb1_4->setVisible(false);
            currOrb=3;
            break;
        default:
            ui->orb1->setVisible(true);
            ui->orb1_2->setVisible(false);
            ui->orb1_3->setVisible(false);
            ui->orb1_4->setVisible(false);
            currOrb=0;
            break;
        }
    }
}


void MainWindow::updateShaftOrbs(){
    static int orbon=0;
    if(orbon==0){
        ui->orb1_5->setVisible(true);
        ui->orb1_6->setVisible(false);
        ui->orb1_7->setVisible(false);
        ui->orb1_8->setVisible(false);
        ui->orb1_9->setVisible(false);
        orbon=1;
    }
    else if(orbon==1){
        ui->orb1_5->setVisible(false);
        ui->orb1_6->setVisible(true);
        ui->orb1_7->setVisible(false);
        ui->orb1_8->setVisible(false);
        ui->orb1_9->setVisible(false);
        orbon=2;
    }
    else if(orbon==2){
        ui->orb1_5->setVisible(false);
        ui->orb1_6->setVisible(false);
        ui->orb1_7->setVisible(true);
        ui->orb1_8->setVisible(false);
        ui->orb1_9->setVisible(false);
        orbon=3;
    }
    else if(orbon==3){
        ui->orb1_5->setVisible(false);
        ui->orb1_6->setVisible(false);
        ui->orb1_7->setVisible(false);
        ui->orb1_8->setVisible(true);
        ui->orb1_9->setVisible(false);
        orbon=4;
    }
    else{
        ui->orb1_5->setVisible(false);
        ui->orb1_6->setVisible(false);
        ui->orb1_7->setVisible(false);
        ui->orb1_8->setVisible(false);
        ui->orb1_9->setVisible(true);
        orbon=0;
    }

}

