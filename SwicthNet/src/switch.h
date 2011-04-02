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
#include "Eth_pck_m.h"

struct FilterTable{
		int gate;
		unsigned char mac[6];
	}FilterTable;

class Switch : public cSimpleModule
{
public:
	Switch();

protected:
	int tblLength;
	struct FilterTable{
				int gate;
				unsigned char mac[6];
	}dataBase[];

    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

#endif
