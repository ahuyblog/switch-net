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

module Host
{
    gates:
        input in;
        output out;

    submodules:
        ether: Eth {
            @display("p=70,209;i=,lightGreen");
        }
        ipLayer: Ip {
            @display("p=70,130;i=,dodgerBlue");
        }
        app: App {

            @display("p=70,56;i=,pink");
        }

    connections:
        ether.upLayer <--> ipLayer.downLayer;
        ipLayer.upLayer <--> app.downLayer;
        ether.downLayerIn <-- in;
        ether.downLayerOut --> out;
}
