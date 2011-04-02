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

#ifndef __SWICTHNET_IP_H_
#define __SWICTHNET_IP_H_

#include <omnetpp.h>
#include <stdio.h>
#include <string.h>
#include "IP_pck_m.h"
#include "Eth_pck_m.h"
#include "App_pck_m.h"

/**
 * TODO - Generated class
 */
class Ip : public cSimpleModule
{
	private:
		int *randArr;
	protected:
		int ipId;
		virtual void initialize();
		virtual void handleMessage(cMessage *msg);
		virtual void processMsgFromHigherLayer(App_pck *packet);
		virtual void processMsgFromLowerLayer(IP_pck *packet);
		char *myIp;
};

#endif
