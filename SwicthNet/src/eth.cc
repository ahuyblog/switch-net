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

#include "eth.h"
#include "Eth_pck_m.h"

Define_Module(Eth);

void Eth::initialize()
{
	 myMac = new char[6];
	 myMac[0] = 11;
	 myMac[1] = 11;
	 myMac[2] = 11;
	 myMac[3] = 11;
	 myMac[4] = 11;
	 myMac[5] = par("mac6");
	 EV << "Initialize Eth layer: "<< myMac[5] <<"\n";
	 // init rand array for ip randomize
	 int size = getVectorSize()-1;
	 randArr = new int[size];
	 for (int i=0,j=0; j<size; i++)
	 {
		 if (i != getIndex())
		 {
			 randArr[j]=i;
			 j++;
		 }
	 }
}

void Eth::handleMessage(cMessage *msg)
{
	if (msg->arrivedOn("downLayer"))
	    processMsgFromLowerLayer(check_and_cast<Eth_pck *>(msg));
	else
	    processMsgFromHigherLayer(check_and_cast<IP_pck *>(msg));
}
void Eth::processMsgFromHigherLayer(IP_pck *packet)
{

}
void Eth::processMsgFromLowerLayer(Eth_pck *packet)
{

}
char *Eth::getMacFromTable(char* ip)
{
	return NULL;//TODO change this!!!
}
