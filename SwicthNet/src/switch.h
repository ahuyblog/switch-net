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

#ifndef __SWICTHNET_SWITCH_H_
#define __SWICTHNET_SWITCH_H_

#include <stdio.h>
#include <string.h>
#include <omnetpp.h>
#include <vector>
#include "Eth_pck_m.h"
using namespace std;

typedef struct FilterTable{
		int gate;
		unsigned char mac[6];
		cMessage * selfEvent;
	}FilterTable;
typedef struct msgStore{
	Eth_pck* msg;
	cMessage* self;
}msgStore;
class Switch : public cSimpleModule
{

public:
	Switch();

protected:
	simtime_t agTime;//Ageing time for each table row
	simtime_t latency;//Deley for forwording message
	int tblLength;
	vector<msgStore> msgQueue;
	vector<msgStore> busyQueue;
	Eth_pck *handledMsg;
	FilterTable *dataBase;
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void copySrcMac(Eth_pck *src, unsigned char *dest);
    void forward(Eth_pck *msgToForward);
    void resetRow(int index);
    void initRow(int index);
    void sendMessage(Eth_pck* etherPacket,const char * gateName,int port);
};

#endif
