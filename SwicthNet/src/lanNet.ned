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

package SwicthNet.src;

network LanNet
{
    types:
        channel Channel extends ned.DatarateChannel
        {
            datarate = 100Mbps;
            //delay = 10us;
            //ber = 1e-10;
        }
    submodules:
        host[4]: Host;
        switch: Switch {
            @display("i=,gold");
        }
    connections:

        switch.in++ <-- Channel <-- host[0].out;
        host[0].in <-- Channel <-- switch.out++;

        switch.in++ <-- Channel <-- host[1].out;
        host[1].in <-- Channel <-- switch.out++;

        switch.in++ <-- Channel <-- host[2].out;
        host[2].in <-- Channel <-- switch.out++;

        switch.in++ <-- Channel <-- host[3].out;
        host[3].in <-- Channel <-- switch.out++;
}
