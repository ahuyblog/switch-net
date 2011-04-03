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
	latency = par("latencyTime");
	int i;
	for (i = 0; i < tblLength; i++)
		resetRow(i);//reset table entry at row i

	//Set timer delay for cheking Ageing time
	EV << "Initial Ageing timer sets\n";
	event = new cMessage("Ageing timer");
	sendEvent = new cMessage("it's time to forward message");
	scheduleAt(simTime()+agTime, event);
}

void Switch::handleMessage(cMessage *msg)
{
	if(msg==event)
	{
		int i;
		for(i = 0; i < tblLength; i++)
		{
			dataBase[i].lastEvnt = simTime()-dataBase[i].lastEvnt;//TODO update last event field
			if(dataBase[i].lastEvnt > agTime)
			{
				resetRow(i);//reset table entry at row i
			}
		}
	}
	else if(msg == sendEvent)
	{
		forward(msgQueue.front());//forwarding the Eth packet that arrived
		msgQueue.erase(msgQueue.begin());
	}
	else
	{
		int arrivedPort = -1;
		handledMsg = check_and_cast<Eth_pck *>(msg);
		msgQueue.push_back(handledMsg);
		cGate *temp = handledMsg->getArrivalGate();
		if (temp != NULL)
			arrivedPort = temp->getIndex();
		else
			EV << "Null error in the switch\n";
		if (dataBase[arrivedPort].gate == -1)
		{
			dataBase[arrivedPort].gate = arrivedPort;//new table entry:
			dataBase[arrivedPort].lastEvnt = simTime();
			copySrcMac(handledMsg, dataBase[arrivedPort].mac);// copy MAC src to the table at port that msg arrived
		}
		else//table entry present
		{
			dataBase[arrivedPort].lastEvnt = simTime()-dataBase[arrivedPort].lastEvnt;//TODO update last event field???need to check
		}
		scheduleAt(simTime()+latency, sendEvent);

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
	bool equal = true;
	int i,j,outPort =-1;
	for(i = 0; i < tblLength; i++)
	{
		if(dataBase[i].gate != -1)
		{
			for(j = 0; j < 6 && equal; j++)
			{
				if(msgToForward->getMacDest(j)==dataBase[i].mac[j])
					equal = true;
				else
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
			if(i != msgToForward->getArrivalGateId())
				send(msgToForward->dup(), "out",i);//send to port
		}
	}//broadcast the message
}

void Switch::resetRow(int index)
{
	int j;
	dataBase[index].gate = -1;
	dataBase[index].lastEvnt =0;
	for (j = 0; j < 6; j++)
		dataBase[index].mac[j] = 0;

}
