#ifndef CANHANDLER_H
#define CANHANDLER_H

#include <canlib.h>
#include <iostream>
#include <ostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <QtCore>
#include <QApplication>
#include <iomanip>

using namespace std;

class CanHandler
{
public:
    CanHandler();

    void getData(double &,double &);
    void getTempData(double &);
private:
    canHandle hnd;

};

#endif // CANHANDLER_H
