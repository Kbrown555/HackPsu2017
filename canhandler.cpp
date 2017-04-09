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
   // canBusOff(hnd);
}

void CanHandler::getData(double &CurrSOC,double &current){
    unsigned char msgbuffer[8];
    int data[8];
    int id=1040;
    uint dlc;



    canIoCtl(hnd,canIOCTL_FLUSH_RX_BUFFER,0,0);
    canReadSyncSpecific(hnd,id,1000);
    canReadSpecificSkip(hnd,id,&msgbuffer,&dlc,NULL,NULL);

    for(int i=0;i<8;i++){
        data[i]=(int)msgbuffer[i];
    }

    CurrSOC=data[3]/2.00;
    double currentVal=(data[4]*256+data[5])*.025-1000;
    if(currentVal !=-1000)
        current=currentVal;

}

void CanHandler::getTempData(double &temp){
    unsigned char msgbuffer[8];
    int data[8];
    int id=1072;
    uint dlc;



    canReadSyncSpecific(hnd,id,1000);
    canReadSpecificSkip(hnd,id,&msgbuffer,&dlc,NULL,NULL);

    for(int i=0;i<8;i++){
        data[i]=(int)msgbuffer[i];
    }

    double temperature=data[4]/2.00-40;
    if(temperature!=-40)
        temp=temperature;

}
