/*
 *  the app module= its job is to create packets and send the to lower layer,
 *  also counts statistics for arriving packets from Ip layer
 */

#ifndef __SWICTHNET_APP_H_
#define __SWICTHNET_APP_H_

#include <stdio.h>
#include <string.h>
#include <omnetpp.h>
#include "App_pck_m.h"

/**
 * the App class
 */
class App : public cSimpleModule
{
public:
	App();
protected:
	virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual App_pck *generateMsg(); // this function creates a new message and sends it
    void finish(); // function calculates statistics when simulation is finished
  private:
    simtime_t delay;  // timeout
    cMessage *timeoutMsg;  // holds pointer to the timeout self-message
    App_pck *message;  // message that has to be re-sent on timeout

    //statistic variables and graphs
    simtime_t lastMsgTime;
    cOutVector arrivelTimes;
    cOutVector betweenTimes;

    cStdDev timeOfLife;
    cStdDev difTime;

};

#endif
