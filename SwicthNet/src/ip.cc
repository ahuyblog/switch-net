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

#include "ip.h"

Define_Module(Ip);
#define IP1 172
#define IP2 168
#define IP3 32
#define TTL 255
#define TCP 6
#define ICMP 1
#define UDP 17
#define HEADER_LENGTH_VERSION 74 // 10 - header length 4- version
#define TOS 0
#define IDENTIFICATION 0
#define FLAGS_OFFSET 0
#define HEADER_LENGTH 20

void Ip::initialize()
{
	ipId = par("ip4");
	EV << "Initialize IP layer: "<< ipId <<"\n";
	// init my ip
    myIp = new unsigned char[4];
    myIp[0] = 172;
    myIp[1] = 168;
    myIp[2] = 32;
    myIp[3] = ipId;
    // init rand array for ip randomize
    int size = par("hostNum");
    size = size-1;
    randArr = new int[size];
    for (int i=0,j=0; j<size; i++)
    {
    	if (i !=ipId)
    	{
    		randArr[j]=i;
    		j++;
    	}
    }
}

void Ip::handleMessage(cMessage *msg)
{
	EV << "handeling message!!!\n"<< msg->getName();
	if (msg->arrivedOn("downLayer$i"))
    	processMsgFromLowerLayer(check_and_cast<IP_pck *>(msg));
    else
    	processMsgFromHigherLayer(check_and_cast<App_pck *>(msg));
}
void Ip::processMsgFromLowerLayer(IP_pck *packet)
{
	bool isMine = true;
	for (unsigned int i=0;i<packet->getDestIpArraySize() && isMine;i++)
	{
		if (packet->getDestIp(i) != myIp[i])
			isMine = false;
	}
	if (isMine)
	{
		App_pck *appPacket = check_and_cast<App_pck *>(packet->decapsulate());
		send(appPacket,"upLayer$o");
	}
	else
	{
		delete packet;
	}
}
void Ip::processMsgFromHigherLayer(App_pck *packet)
{
	EV << "Message arrived from Higher level\n";
	int i=0;
	IP_pck *ipPacket = new IP_pck("IP");
	ipPacket->setF_frOffset(FLAGS_OFFSET);
	ipPacket->setLength(packet->getByteLength()+HEADER_LENGTH);
	ipPacket->setByteLength(HEADER_LENGTH);
	ipPacket->setProtocol(TCP);
	ipPacket->setTtl(TTL);
	ipPacket->setIdent(IDENTIFICATION);
	ipPacket->setVerHlengthTos(HEADER_LENGTH_VERSION);
	for (i=0; i<4; i++)
	{
		ipPacket->setSrcIp(i,myIp[i]);
	}
	for (i=0; i<3; i++)
	{
		ipPacket->setDestIp(i,myIp[i]);
	}
	int hostNum = par("hostNum");
	ipPacket->setDestIp(i,randArr[intuniform(0,hostNum-2)]);
	const char *data = packet->getData();
	int size= packet->getByteLength();
	unsigned short checksum=0;
	for (i=0; i<size/2;i=i+2)
	{
		unsigned short temp = data[i];
		temp = temp << 8;
		temp += data[i+1];
		checksum += temp;
	}
	ipPacket->setCheckSum(checksum);
	ipPacket->encapsulate(packet);
	EV << "Sending message to Downlayer\n";
	send(ipPacket,"downLayer$o");
}
