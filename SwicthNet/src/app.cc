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


#include "app.h"

Define_Module(App);

App::App()
{
	timeoutMsg = message = NULL;
}
void App::initialize()
{
	timeout = uniform(0,10);//TODO 10 needed to be defined in ini file
	// Generate and send initial message.
	EV << "Sending initial message\n";
	message = generateMsg();
	timeoutMsg = new cMessage("Data packet generated");
	send(message, "downLayer");
	scheduleAt(simTime()+timeout, timeoutMsg);
	// TODO - Generated method body
}

void App::handleMessage(App_pck *msg)
{
	if (msg==timeoutMsg)
	{
		// If we receive the timeoutMsg, that it's time to generate another message
		EV << "Rand timeout expired, sending the new message and restarting timer\n";
		message = generateMsg();
		send(message, "downLayer");
		timeout = uniform(0,10);//TODO 10 needed to be defined in ini file
		scheduleAt(simTime()+timeout, timeoutMsg);
	}
	else // message arrived
	{
		// Data packet received!
		EV << "Received from downLayer: " << msg->getData() << "\n";//TODO change that we want to print
		delete msg;

//		// Also delete the stored message and cancel the timeout event.
//		EV << "Timer cancelled.\n";
//		cancelEvent(timeoutEvent);
//		delete message;

		// Ready to send another one.
//		message = generateNewMessage();
//		sendCopyOf(message);
//		scheduleAt(simTime()+timeout, timeoutEvent);
	}
	// TODO - Generated method body
}

App_pck *App::generateMsg()
{
	// Generate a random data in application layer with a different length .
    int i;
	int dataLength = uniform(0,100);//TODO 100 needed to be defined in *.ini file
	char msgdata[dataLength];
	for (i = 0; i < dataLength; i++)
		msgdata[i]=uniform(50,125);//random data generation
    App_pck *msg = new App_pck();
    msg->setData(msgdata);
    return msg;
}

