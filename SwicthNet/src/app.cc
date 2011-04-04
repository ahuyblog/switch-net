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
	//Set timer delay befor sending the first message
	simtime_t delay = par("delayTime");
	EV << "Initial delay timer sets\n";
	timeoutMsg = new cMessage("Data packet generated");
	scheduleAt(simTime()+delay, timeoutMsg);
}

void App::handleMessage(cMessage *msg)
{

	if (msg==timeoutMsg)
	{
		// If we receive the timeoutMsg, that it's time to generate and to send the message
		EV << "Rand delay expired, sending the new message and restarting timer\n";
		message = generateMsg();
		send(message, "downLayer$o");
		delay = par("delayTime");
		scheduleAt(simTime()+delay, timeoutMsg);
	}
	else // message arrived
	{
		App_pck *handledMsg = check_and_cast<App_pck *>(msg);
		// Data packet received!
		EV << "Received from downLayer: " << handledMsg->getData() << "\n";//TODO change that we want to print
		delete msg;

	}
}

App_pck *App::generateMsg()
{
	// Generate a random data in application layer with a different length .
	int dataLgth = 0;
	while (dataLgth < 26 || dataLgth > 1480)
	{
		dataLgth = par("dataLength");
		dataLgth = dataLgth - (dataLgth%4);
	}
	App_pck *data = new App_pck("Application data");
	data->setByteLength(dataLgth);

//	char msgdata[dataLgth];
//	for (i = 0; i < dataLgth; i++)
//		msgdata[i]=uniform(50,125);//random data generation
//    App_pck *msg = new App_pck();
//    msg->setData(msgdata);
    return data;
}

