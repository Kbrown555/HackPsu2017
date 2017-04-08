#include "canhandler.h"

CanHandler::CanHandler()
{

    canStatus stat;
    canInitializeLibrary();
    hnd=canOpenChannel(0,canWANT_EXCLUSIVE);
    if(hnd<0){
        ::exit(22);
    }

    canSetBusParams(hnd,canBITRATE_500K,0,0,0,0,0);
    canSetBusOutputControl(hnd,canDRIVER_NORMAL);
    stat = canBusOn(hnd);
    if(stat!= canOK){
        ::exit(21);
    }
}

void CanHandler::getData(double &CurrSOC){
    double SOC;
    unsigned char msgbuffer[8];
    int data[8];
    uint dlc;

    canReadSpecificSkip(hnd,1040,&msgbuffer,&dlc,NULL,NULL);

    std::stringstream ss;
    std::string s;
    for(int i=0;i<dlc;i++){
        data[i]=(int)msgbuffer[i];
    }

    SOC=data[3]/2;
    CurrSOC=SOC;
}
