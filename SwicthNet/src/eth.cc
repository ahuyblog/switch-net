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
#define PREAMBLE_START 170 // 0xAA
#define PREAMBLE_END 171 // 0xAB
#define ARP_REQUEST 0
#define ARP_REPLY 1
#define ARP_TYPE 1600
#define ARP_REPLY_LENGTH 10
#define ARP_REQUEST_LENGTH 6
#define ETH_LENGTH 14
#define BROADCAST 0xFF
#define UNDEFINED -1
#define IP1 172
#define IP2 168
#define IP3 32
Define_Module(Eth);

void Eth::initialize()
{
	iTable = 0;
	myMac = new char[6];
	myMac[0] = 17; // 11 HEX
	myMac[1] = 17;
	myMac[2] = 17;
	myMac[3] = 17;
	myMac[4] = 17;
	myMac[5] = par("id");
	myIp = new char[4];
	myIp[0] =IP1;
	myIp[1] =IP2;
	myIp[2] =IP3;
	myIp[3] = par("id");
	EV << "Initialize Eth layer: "<< myMac[5] <<"\n";
	// init rand array for ip randomize
	int size = par("hostNum");
	size = size -1;
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
	if (msg->isSelfMessage())
		processSelfTimer(msg);
	else if (msg->arrivedOn("downLayer$i"))
	    processMsgFromLowerLayer(check_and_cast<Eth_pck *>(msg));
	else
	    processMsgFromHigherLayer(check_and_cast<IP_pck *>(msg));
}
void Eth::processMsgFromHigherLayer(IP_pck *packet)
{
	Eth_pck *etherPacket = new Eth_pck("ether");
	unsigned int i=0;
	/* no preamble according to 14B size stated in exercise
	for (i=0; i<etherPacket->getPreambleArraySize()-1; i++)
	{
		etherPacket->setPreamble(i,PREAMBLE_START);
	}
	etherPacket->setPreamble(i,PREAMBLE_END);*/
	for (i=0; i<etherPacket->getMacSrcArraySize();i++)
	{
		etherPacket->setMacSrc(i,myMac[i]);
	}
	etherPacket->setByteLength(14);
	char *destMac = getMacFromTable(packet);
	if (destMac != NULL)
	{
		for (i=0; i<etherPacket->getMacDestArraySize();i++)
		{
			etherPacket->setMacDest(i,destMac[i]);
		}
		etherPacket->setLength(packet->getByteLength());
		etherPacket->encapsulate(packet);
		send(etherPacket,"downLayerOut");
		// checking if there are more packets that can be sent (those that are on the arp table)
		IP_pck* ipPacket = checkForMore();
		if (ipPacket != NULL)
		{
			processMsgFromHigherLayer(ipPacket);
		}
	}
	else // need to send arp request
	{
		Arp* arpPacket = new Arp("Arp message");
		arpPacket->setType(ARP_REQUEST);
		for (i=0; i<arpPacket->getIpArraySize();i++)
		{
			arpPacket->setIp(i,packet->getDestIp(i));
		}
		arpPacket->setByteLength(6);
		etherPacket->setLength(ARP_TYPE);
		for (i=0; i<etherPacket->getMacDestArraySize();i++)
		{
			etherPacket->setMacDest(i,BROADCAST);
		}
		etherPacket->encapsulate(arpPacket);
		send(etherPacket,"downLayerOut");
		fifo.push_back(packet);
	}
}
void Eth::processMsgFromLowerLayer(Eth_pck *packet)
{
	if (packet->getLength() == ARP_TYPE)
	{
		// getting the src mac for later useage (dest mac is broadcast so it is irrelevent
		char *srcMac = new char[6]; // TODO check deletion
		for (int i=0; i<6;i++)
		{
			srcMac[i] = packet->getMacSrc(i);
		}

		Arp* arpPacket = check_and_cast<Arp *>(packet->decapsulate());


		if (ARP_REQUEST == arpPacket->getType()) // arp request
		{
			bool isMine = true;
			unsigned int i=0;
			for (i=0;i<arpPacket->getMacArraySize() && isMine;i++)
			{
				if (arpPacket->getIp(i)!=myIp[i])
					isMine = false;
			}
			if (isMine) // need to send arp reply
			{
				Arp* arpReply = new Arp("Arp message");
				Eth_pck * etherPacket = new Eth_pck("ether");
				arpPacket->setType(ARP_REPLY);
				for (i=0; i<arpPacket->getIpArraySize();i++)
				{
					arpReply->setIp(i,arpPacket->getIp(i));
				}
				for (i=0; i<arpReply->getMacArraySize();i++)
				{
					arpReply->setMac(i,myMac[i]);
				}
				arpPacket->setByteLength(ARP_REPLY_LENGTH);
				etherPacket->setLength(ARP_TYPE);
				etherPacket->setByteLength(ETH_LENGTH);
				for (i=0; i<etherPacket->getMacDestArraySize();i++)
				{
					etherPacket->setMacDest(i,srcMac[i]);
				}
				for (i=0; i<etherPacket->getMacSrcArraySize();i++)
				{
					etherPacket->setMacSrc(i,myMac[i]);
				}
				etherPacket->encapsulate(arpReply);
				send(etherPacket,"downLayerOut");
			}
			else // TODO wtf should i do here which message should i delete the arp one or the eth?
			{
				delete packet;
			}
		}
		else //got an arp reply message need to fill table with new info
		{
			char *destIp = new char[4]; //TODO delete this later
			for (int i=0; i<4; i++)
			{
				destIp[0]=arpPacket->getIp(i);
			}
			int index=searchEntry(destIp);
			if (index == UNDEFINED)
			{
				for (int i=0; i<4;i++)
				{
					table[iTable].destIp[i]=arpPacket->getIp(i);
				}
				for (int i=0;i<6;i++)
				{
					table[iTable].mac[i]=arpPacket->getMac(i);
				}
				table[iTable].timer= new cMessage("del");
				table[iTable].timer->setKind(iTable); // using this variable to know which entry invoked this msg
				double age = par("aging");
				scheduleAt(simTime()+age,table[iTable].timer); // lanching a delete entry event at this time
				iTable++;
			}
			else //found the index updating mac and time
			{
				for (int i=0; i<6;i++)
				{
					table[index].mac[i]=arpPacket->getMac(i);
				}
				cancelAndDelete(table[index].timer); // canceling the deletion event of this entry
				table[index].timer= new cMessage("del");
				table[index].timer->setKind(index); // using this variable to know which entry invoked this msg
				double age = par("aging");
				scheduleAt(simTime()+age,table[index].timer);  // launching a new delete entry event
			}
			IP_pck* ipPacket = checkForMore();
			if (ipPacket !=NULL)
			{
				processMsgFromHigherLayer(ipPacket);
			}
		}
		delete srcMac;
	}
	else // regular message need to pass to higher layer and update arp table
	{

	}
}
char *Eth::getMacFromTable(IP_pck* packet)
{
	return NULL;//TODO change this!!!
}
/*
 * Description: will delete the correct entry from the table
 */
void Eth::processSelfTimer(cMessage *msg)
{

}
/*
 * Description: checking fifo for packets that exists on the arp table returning NULL if none were found
 */
IP_pck *Eth::checkForMore()
{
	return NULL;
}
int Eth::searchEntry(char* ip)
{
	return UNDEFINED;
}
