#ifndef CANHANDLER_H
#define CANHANDLER_H

#include <canlib.h>
#include <iostream>
#include <fstream>
#include <sstream>

class CanHandler
{
public:
    CanHandler();

    void getData(double &);

private:
    canHandle hnd;
};

#endif // CANHANDLER_H
