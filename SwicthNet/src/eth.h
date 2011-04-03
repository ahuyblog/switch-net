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

#ifndef __SWICTHNET_ETH_H_
#define __SWICTHNET_ETH_H_

#include <omnetpp.h>
#include <string.h>
#include <stdio.h>
#include <vector>
#include "Eth_pck_m.h"
#include "IP_pck_m.h"
#include "Arp_m.h"
using namespace std;
typedef struct arpTable
{
	unsigned char destIp[4];
	unsigned char mac[6];
	cMessage * timer;
}arpTable;

class Eth : public cSimpleModule
{
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void processMsgFromHigherLayer(IP_pck *packet);
    virtual void processMsgFromLowerLayer(Eth_pck *packet);
    virtual void processSelfTimer(cMessage *msg);
    unsigned char *myMac;
    unsigned char *myIp;
    arpTable table[10];
    unsigned int iTable;
  private:
    virtual unsigned char *getMacFromTable(IP_pck* packet);
    virtual IP_pck *checkForMore();
    virtual int searchEntry(unsigned char* ip);
    int *randArr;
    void copyArpEntry(arpTable* dst,arpTable* src);
    vector<IP_pck*> fifo; // will hold all messeges that need to be sent
};
#endif
