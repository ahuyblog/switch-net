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

//
// TODO generated message class
//
packet Eth_pck {
//    int someField;
//    string anotherField;
//    double arrayField1[];
//    double arrayField2[10];
//    
    //Our Ethernet field defenitions 
    unsigned char[8] preamble;
    unsigned char[6] macDest;
    unsigned char[6] macSrc;
    unsigned short length;
    string data;
    unsigned long fcs;
}
