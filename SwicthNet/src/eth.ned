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

//
// TODO auto-generated module
//


simple Eth
{
    
    parameters:
        @display("i=block/ifcard");
        int id;
        int hostNum = default(4);
		volatile double aging @unit(s);
    gates:
        inout upLayer;
        input downLayerIn;
        output downLayerOut;
}
