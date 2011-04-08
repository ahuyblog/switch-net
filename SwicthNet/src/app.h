//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef __SWICTHNET_APP_H_
#define __SWICTHNET_APP_H_

#include <stdio.h>
#include <string.h>
#include <omnetpp.h>
#include "App_pck_m.h"

/**
 * TODO - Generated class
 */
class App : public cSimpleModule
{
public:
	App();
protected:
	virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual App_pck *generateMsg();
    void finish();
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
