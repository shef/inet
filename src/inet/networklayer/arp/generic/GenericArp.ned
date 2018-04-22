//
// Copyright (C) 2004 Andras Varga
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//

package inet.networklayer.arp.generic;

import inet.networklayer.contract.IArp;


//
// Resolves an L3 address to a MAC address. Currently it supports 
// three types of addresses: moduleId, modulePath, and MAC address
// as L3 address. These address types are resolved synchronously, 
// without any protocol messaging. IPv4 and IPv6 addresses are not
// supported. (For IPv4 use ~Arp, and for IPv6 use ~Ipv6NeighbourDiscovery.)
//
simple GenericArp like IArp
{
    parameters:
        @display("i=block/layer");
        string interfaceTableModule;   // The path to the InterfaceTable module
    gates:
        input netwIn @labels(IGenericDatagram); // incoming ARP requests and replies
        output netwOut @labels(IGenericDatagram);  // outgoing ARP requests/replies, and datagrams with resolved next hop
        input ifIn @labels(ArpPacket,Ieee802Ctrl);
        output ifOut @labels(ArpPacket,Ieee802Ctrl);
}
