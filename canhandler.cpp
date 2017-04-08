#include "canhandler.h"

CanHandler::CanHandler()
{


    canInitializeLibrary();
    hnd=canOpenChannel(0,canWANT_EXCLUSIVE);
    if(hnd<0){
        std::cout<<"failed to get can channel";
    }

    canSetBusParams(hnd,canBITRATE_500K,0,0,0,0,0);
    canSetBusOutputControl(hnd,canDRIVER_NORMAL);
    canBusOn(hnd);
}

void CanHandler::getData(double &CurrSOC){
    double SOC;
    char msgbuffer[25];
    uint dlc;
    canReadSpecificSkip(hnd,1040,&msgbuffer,&dlc,NULL,NULL);
    std::stringstream ss;
    std::string s;
    ss<<msgbuffer[6];
    ss<<msgbuffer[7];
    ss<<msgbuffer[8];
    std::cout<<s;
    ss>>s;
    scanf(s.c_str(),"%lA",&SOC);
    SOC=SOC/2;
    CurrSOC=SOC;
}
