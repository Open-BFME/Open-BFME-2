// ?SetLocalIP@LANAPI@@UAE_NI@Z
// partial score=1.0 date=2026-10-05
// cl: /O1 /Oy- /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
// Native Ghidra44A9E6..44AA84 158B; vtable83E680 slot53, followed
// by rowed77B string-address overload44AA84 slot52. Fields48/4C/50/54
// established independently by native loads/stores. Standalone virtual
// declaration only emits this body; it does not emit a shortened vtable.
// BFME1 6583b3c1 LANAPILocalAddress port scan and ZH LANAPI SetLocalIP
// supply semantic guides. Target adds loopback-aware broadcast destination.
// PE proves msvcr71 getenv/atoi; exact literals _EA_RTS_HEADLESS / 0 /
// 127.0.0.1 read independently from target. All158 bytes match with
// existing call pins. Full43B reset4D5496,33B broadcast4D5112,155B
// ResolveIP581339 and65B narrow construction37BA0 already rowed; initializer
// 412B4D5219 remains banked. Do not land until that dependency can link.
#include "ascii_string.h"
extern "C" {
__declspec(dllimport) char* __cdecl getenv(const char*);
__declspec(dllimport) int __cdecl atoi(const char*);
}
struct TransportAddress {unsigned ip;unsigned short port;};
class Transport {
public: void Rva004D5496(); bool init(const TransportAddress*); bool allowBroadcasts(bool);
};
unsigned __cdecl ResolveIP(AsciiString);
class LANAPI {
public: virtual bool SetLocalIP(unsigned);
private: char consumedPrefix[0x44];
 TransportAddress address; Transport* transport; unsigned broadcastIP;
};
bool LANAPI::SetLocalIP(unsigned localIP) {
 address.ip=localIP;
 transport->Rva004D5496();
 const char* headless=getenv("_EA_RTS_HEADLESS");
 int port=8086+atoi(headless?headless:"0");
 while((unsigned short)port<8094) {
  address.port=(unsigned short)port;
  if(transport->init(&address)) break;
  ++port;
 }
 if(address.ip==ResolveIP(AsciiString("127.0.0.1"))) {
  transport->allowBroadcasts(false); broadcastIP=address.ip;
 }else {
  transport->allowBroadcasts(true); broadcastIP=~0u;
 }
 return (unsigned short)port<8094;
}
