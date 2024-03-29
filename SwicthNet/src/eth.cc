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
	int myId = par("id");
	/*
	 * initializing my mac adress by using the id on the parmeters on ini file
	 */
	myMac = new unsigned char[6];
	myMac[0] = 17; // 11 HEX
	myMac[1] = 17;
	myMac[2] = 17;
	myMac[3] = 17;
	myMac[4] = 17;
	myMac[5] = myId;
	myIp = new unsigned char[4];
	myIp[0] =IP1;
	myIp[1] =IP2;
	myIp[2] =IP3;
	myIp[3] = myId;
	EV << "Initialize Eth layer: "<< myMac[5] <<"\n";
	// init rand array for ip randomize, array will hold all adresses of all host but myself
	// on later stages will random one of the cells.
	int size = par("hostNum");
	size = size -1;
	randArr = new int[size];
	for (int i=0,j=0; j<size; i++)
	{
		if (i !=myId)
		{
			randArr[j]=i;
			j++;
		}
	}
}
/*
 * Description: when getting a message this function checks from where and calls the correct function
 */
void Eth::handleMessage(cMessage *msg)
{
	if (msg->isSelfMessage())
		processSelfTimer(msg);
	else if (msg->arrivedOn("downLayerIn")) // message arrived from switch
	    processMsgFromLowerLayer(check_and_cast<Eth_pck *>(msg));
	else // message arrived from ip layer
	    processMsgFromHigherLayer(check_and_cast<IP_pck *>(msg));
}
/*
 * Description: this function handles a packet that was recievd from the ip layer
 * 				thus it recievs an IP_pck as a paramter. the function checks if the dest mac is on the arp table
 * 				if dest mac is not there - and arp request is sent and recievd packet enters a queue-
 * 				later on this packet will be sent.
 */
void Eth::processMsgFromHigherLayer(IP_pck *packet)
{
	//**** creating the eth packet to send
	Eth_pck *etherPacket = new Eth_pck("ether");
	unsigned int i=0;
	for (i=0; i<etherPacket->getMacSrcArraySize();i++)
	{
		etherPacket->setMacSrc(i,myMac[i]);
	}
	etherPacket->setByteLength(14);
	unsigned char *destMac = getMacFromTable(packet); // getting mac dest from the table - will be NULL if not found
	if (destMac != NULL) // found on table
	{ // finishing making packet using the dest mac
		for (i=0; i<etherPacket->getMacDestArraySize();i++)
		{
			etherPacket->setMacDest(i,destMac[i]);
		}
		etherPacket->setLength(packet->getByteLength());
		etherPacket->encapsulate(packet);
		//** sending the message by using sendMessage function to prevent sending a message when line is busy.
		sendMessage(etherPacket,"downLayerOut");
		// checking if there are more packets that can be sent (those that are on the arp table)
		IP_pck* ipPacket = checkForMore();
		if (ipPacket != NULL)
		{
			processMsgFromHigherLayer(ipPacket);
		}
	}
	else //not found on table need to send arp request
	{
		//*** creating arp packet request - then encapsulating it with eth packet
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
		sendMessage(etherPacket,"downLayerOut");
		// putting the message from the higher layer on the queue to send it later.
		fifo.push_back(packet);
	}
}
/*
 * Description: handles a message from lower layer. if its an arp reply fills table and checking queue for waiting packets to send
 * 				if its a data message - will be decapsulated and sent up to the higher layer - of course it will happen only if dest mac on msg equals to my mac
 */
void Eth::processMsgFromLowerLayer(Eth_pck *packet)
{
	// checking message type - if is mac it will be handled differently
	if (packet->getLength() == ARP_TYPE)
	{
		// getting the src mac for later useage (dest mac is broadcast so it is irrelevent
		unsigned char *srcMac = new unsigned char[6]; // TODO check deletion
		for (int i=0; i<6;i++)
		{
			srcMac[i] = packet->getMacSrc(i);
		}

		Arp* arpPacket = check_and_cast<Arp *>(packet->decapsulate());
		delete packet; // deleting the eth packet only. dont need it anymore. i have a pointer for the arp itself
		if (ARP_REQUEST == arpPacket->getType()) // arp request, will check if its mine, if it is will send arp reply
		{
			bool isMine = true;
			unsigned int i=0;
			for (i=0;i<arpPacket->getIpArraySize() && isMine;i++)
			{
				if (arpPacket->getIp(i)!=myIp[i])
					isMine = false;
			}
			if (isMine==true) // need to send arp reply
			{
				Arp* arpReply = new Arp("Arp message");
				Eth_pck * etherPacket = new Eth_pck("ether");
				arpReply->setType(ARP_REPLY);
				for (i=0; i<arpReply->getIpArraySize();i++)
				{
					arpReply->setIp(i,arpPacket->getIp(i));
				}
				for (i=0; i<arpReply->getMacArraySize();i++)
				{
					arpReply->setMac(i,myMac[i]);
				}
				arpReply->setByteLength(ARP_REPLY_LENGTH);
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
				sendMessage(etherPacket,"downLayerOut");
			}
		}
		else //got an arp reply message need to fill table with new info
		{
			unsigned char *destIp = new unsigned char[4]; //TODO delete this later
			for (int i=0; i<4; i++)
			{
				destIp[i]=arpPacket->getIp(i);
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
			// checking for messages that are still on the fifo - if found going back to higher layer function which handles those messages
			IP_pck* ipPacket = checkForMore();
			if (ipPacket !=NULL)
			{
				processMsgFromHigherLayer(ipPacket);
			}
		}
		delete srcMac;
		delete arpPacket;
	}
	else // regular message need to pass to higher layer and update arp table
	{
		bool isMine = true;
		for (unsigned int i=0;i<packet->getMacDestArraySize() && isMine;i++)
		{
			if (myMac[i] != packet->getMacDest(i))
				isMine = false;
		}
		if (isMine) // message is mine
		{
			IP_pck *ipPacket = check_and_cast<IP_pck*>(packet->decapsulate());
			send(ipPacket,"upLayer$o");
			delete packet;
		}
		else // message is not mine
		{
			delete packet;
		}
	}
}
/*
 * Description: function gets an IP packet and returns the mac
 * 				if mac is not on table - returns NULL
 */
unsigned char *Eth::getMacFromTable(IP_pck* packet)
{
	int index = UNDEFINED;
	for (unsigned int j=0;j<iTable && index == UNDEFINED;j++)
	{
		bool isFound = true;
		for (unsigned int i=0; i<packet->getDestIpArraySize() && isFound;i++)
		{
			if (table[j].destIp[i]!=packet->getDestIp(i))
				isFound = false;
		}
		if (isFound)
			index = j;
	}
	if (index != UNDEFINED)
	{
		unsigned char* destMac = new unsigned char[6];
		for (int i=0; i<6;i++)
		{
			destMac[i]=table[index].mac[i];
		}
		return destMac;
	}
	return NULL;
}
/*
 * Description: will delete the correct entry from the table
 */
void Eth::processSelfTimer(cMessage *msg)
{
	if (!strcmp(msg->getName(),"del"))
	{
		int index = msg->getKind();
		cancelAndDelete(table[index].timer);
		for (unsigned int i=index;i<iTable-1;i++)
		{
			copyArpEntry(&table[i],&table[i+1]);
		}
		iTable--;
	}
	else
	{
		msgStore temp=msgQueue.front();
		msgQueue.erase(msgQueue.begin());
		cancelAndDelete(msg);
		sendMessage(temp.msg,"downLayerOut");
	}
}
/*
 * Descripition: copies an entry of arpTable
 */
void Eth::copyArpEntry(arpTable* dst,arpTable* src)
{
	for (int i=0;i<4;i++)
	{
		dst->destIp[i]=src->destIp[i];
	}
	for (int i=0;i<6;i++)
	{
		dst->mac[i]=src->mac[i];
	}
	dst->timer=src->timer;
}
/*
 * Description: checking fifo for packets that exists on the arp table returning NULL if none were found
 */
IP_pck *Eth::checkForMore()
{
	unsigned int i=0;
	unsigned char* mac=NULL;
	unsigned int size = fifo.size();
	for (i =0;i<size && mac==NULL;i++)
	{
		mac=getMacFromTable((fifo[i]));
	}
	if (mac != NULL)
	{
		IP_pck *tempPacket= fifo[i-1];
		fifo.erase(fifo.begin()+i-1);
		return tempPacket;
	}
	return NULL;
}
/*
 * Description: searching for an entry in the arp table. gets an IP returns the index in the table
 */
int Eth::searchEntry(unsigned char* ip)
{
	int index = UNDEFINED;
	bool isFound = true;
	for (unsigned int j=0;j<iTable && index == UNDEFINED;j++)
	{
		isFound=true;
		for (int i=0; i<4 && isFound;i++)
		{
			if (table[j].destIp[i]!=ip[i])
				isFound = false;
		}
		if (isFound)
			return index;
	}
	return index;
}
/*
 * Description: sending a message - also checks if channel is busy, in case it is busy
 * 				will put the message in a queue and initiate a self event "busy" will grab it in the future
 * 				and send the msg in the queue later.
 */
void Eth::sendMessage(Eth_pck* etherPacket,const char * gateName)
{
	cGate* outGate= gate(gateName)->getNextGate();
	cChannel* channel = outGate->getTransmissionChannel();
	//simtime_t txFinishTime =channel->getTransmissionFinishTime();
	if (!channel->isBusy())
	{
		send(etherPacket,gateName);
	}
	else
	{
		msgStore temp;
		temp.msg = etherPacket;
		temp.self = new cMessage("busy");
		scheduleAt(channel->getTransmissionFinishTime(),temp.self);
		msgQueue.push_back(temp);
	}
}
