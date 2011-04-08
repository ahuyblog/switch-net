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

	lastMsgTime = simTime();
	arrivelTimes.setName("Arrival Time");
	betweenTimes.setName("Bettwen arrivals Time");

	timeOfLife.setName("Time of life for massege");
	difTime.setName("Diferance time");
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

		//collect time of life of each message arrived to the module
		simtime_t eed = simTime() - msg->getCreationTime();
		timeOfLife.collect(eed.dbl());
		betweenTimes.record(eed.dbl());

		delete msg;

		//statistic calculation
		simtime_t stat = simTime()-lastMsgTime;
		arrivelTimes.record(stat);
		lastMsgTime = simTime();

		difTime.collect(stat);

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

    return data;
}

void App::finish()
{
	// This function is called by OMNeT++ at the end of the simulation.
	EV << "Final statistic " << endl;
	EV << "Time of life mean: " << timeOfLife.getMean() << endl;
	EV << "Time of life Max: " << timeOfLife.getMax() << endl;
	EV << "Time of life Min: " << timeOfLife.getMin() << endl;
	EV << "Time of life StdDev: " << timeOfLife.getStddev() << endl;
	EV << "--------------------" << endl;
	EV << "Time between arrivals mean: " << difTime.getMean() << endl;
	EV << "Time between arrivals Max: " << difTime.getMax() << endl;
	EV << "Time between arrivals Min: " << difTime.getMin() << endl;
	EV << "Time between arrivals StdDev: " << difTime.getStddev() << endl;
	EV << "********************" << endl;
}

