#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setValue(int value){
    QString allgood="QProgressBar::chunk {background-color: green;width: 10px; margin 0.5 px;}";
    ui->progressBar->setValue(value);
    ui->progressBar->setStyleSheet(allgood);
}
