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

#include "switch.h"

Define_Module(Switch);

Switch::Switch()
{
	tblLength = 0;
	dataBase = NULL;
}

/*
 * Description: Initialize the parameters of the switch
 * 				Creating and zerorise the switch table
 * 				Schedule self event time for ageing timer update
 */
void Switch::initialize()
{
	tblLength = par("tableLength");
	dataBase = new FilterTable[tblLength];
	agTime = par("ageingTime");
	int i;
	for (i = 0; i < tblLength; i++)
		initRow(i);//reset table entry at row i

	//Set timer delay for cheking Ageing time
//	EV << "Initial Ageing timer sets\n";
//	event = new cMessage("event");
//	sendEvent = new cMessage("sendEvent");
//	scheduleAt(simTime()+agTime, event);
}

void Switch::handleMessage(cMessage *msg)
{
	if(msg->isSelfMessage() && !strcmp(msg->getName(),"event"))
	{
		int i=msg->getKind();
		EV<< "****SWITCH TABLE ENTRY DELITED at port: "<< i <<endl;
		resetRow(i);//reset table entry at row
		//cancelAndDelete(msg);
	}
	else if(msg->isSelfMessage() && !strcmp(msg->getName(),"sendEvent"))
	{
		msgStore temp = msgQueue.front();
		forward(temp.msg);//forwarding the Eth packet that arrived
		cancelAndDelete(temp.self);
		//delete temp.msg;
		msgQueue.erase(msgQueue.begin());
	}
	else
	{
		int arrivedPort = -1;
		handledMsg = check_and_cast<Eth_pck *>(msg);
		msgStore temp2;
		temp2.msg = handledMsg;
		temp2.self = new cMessage("sendEvent");
		temp2.self->setKind(msgQueue.size());
		latency = par("latencyTime");
		latency = (handledMsg->getByteLength()*latency)/1000;
		scheduleAt(simTime()+latency,temp2.self);
		msgQueue.push_back(temp2);
		cGate *temp = handledMsg->getArrivalGate();
		if (temp != NULL)
			arrivedPort = temp->getIndex();
		else
			EV << "Null error in the switch\n";
		if (dataBase[arrivedPort].gate == -1)
		{
			dataBase[arrivedPort].gate = arrivedPort;//new table entry:
			copySrcMac(handledMsg, dataBase[arrivedPort].mac);// copy MAC src to the table at port that msg arrived
			dataBase[arrivedPort].selfEvent = new cMessage("event");
			dataBase[arrivedPort].selfEvent->setKind(arrivedPort);
			scheduleAt(simTime()+agTime,dataBase[arrivedPort].selfEvent);
		}
		else//table entry present
		{
			cancelAndDelete(dataBase[arrivedPort].selfEvent);
			dataBase[arrivedPort].selfEvent = new cMessage("event");
			dataBase[arrivedPort].selfEvent->setKind(arrivedPort);
			scheduleAt(simTime()+agTime,dataBase[arrivedPort].selfEvent);
		}
		//scheduleAt(simTime()+latency, sendEvent);

	}
}

void Switch::copySrcMac(Eth_pck *src, unsigned char *dest)
{
	int i;
	for (i = 0; i < 6; i++)
	{
		dest[i]=src->getMacSrc(i);
	}
}

void Switch::forward(Eth_pck *msgToForward)
{
	bool equal;
	int i,j,outPort =-1,arrPort;
	for(i = 0; i < tblLength && outPort == -1; i++)
	{
		equal=true;
		if(dataBase[i].gate != -1)
		{
			for(j = 0; j < 6 && equal; j++)
			{
				if(msgToForward->getMacDest(j)!=dataBase[i].mac[j])
					equal = false;
			}
			if (equal)
				outPort = dataBase[i].gate;
		}
	}
	if (outPort > -1)
		send(msgToForward, "out",outPort);//send to port
	else
	{
		for (i = 0; i < tblLength;i++)
		{
			cGate *temp = msgToForward->getArrivalGate();
			if (temp != NULL)
				arrPort = temp->getIndex();
			if(i != arrPort)
				send(msgToForward->dup(), "out",i);//send to port
		}
		delete msgToForward;
	}//broadcast the message
}

void Switch::resetRow(int index)
{
	int j;
	dataBase[index].gate = -1;
	if (dataBase[index].selfEvent != NULL)
		delete dataBase[index].selfEvent;
	for (j = 0; j < 6; j++)
		dataBase[index].mac[j] = 0;

}

void Switch::initRow(int index)
{
	int j;
	dataBase[index].gate = -1;
	dataBase[index].selfEvent = NULL;
	for (j = 0; j < 6; j++)
		dataBase[index].mac[j] = 0;

}

/*
 * Description: sending a message - also checks if channel is busy, in case it is busy
 * 				will put the message in a queue and initiate a self event "busy" will grab it in the future
 * 				and send the msg in the queue later.
 */
void Switch::sendMessage(Eth_pck* etherPacket,const char * gateName,int port)
{
	cGate* outGate= gate(gateName, port);
	cChannel* channel = outGate->getTransmissionChannel();
	if (!channel->isBusy())
	{
		send(etherPacket,gateName,port);
	}
	else
	{
		msgStore temp;
		temp.msg = etherPacket;
		temp.self = new cMessage("busy");
		scheduleAt(channel->getTransmissionFinishTime(),temp.self);
		busyQueue.push_back(temp);
	}
}
