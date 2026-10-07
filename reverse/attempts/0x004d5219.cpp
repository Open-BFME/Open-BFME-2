// ?init@Transport@@QAE_NPBUTransportAddress@@@Z
// partial score=0.99 date=2026-10-07
// ?init@Transport@@QAE_NPBUTransportAddress@@@Z
// partial score=0.98 date=2026-10-05
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
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
// Bank: native Ghidra [4D5219,4D53B5),412B. BFME1 6583b3c1
// Transport::init supplies WSA version check / UDP bind retry / cleanup
// semantics. Target adds eight slots and measured first-slot address8
// at40E10, with packet/statistics layout from exact sibling4D53B5.
// Opaque UDP allocation32 is independently measured; ctor35/dtor69
// and local-address getter25 are rowed. Bind188B594B56 remains unrowed.
// Correct412B extent but native frame19C vs compiled1A0: unused localPort
// at-1C vs retail retired parameter storage+0A; WSA data consequently
// shifted4B. Startup result TEST instead of retail CMP against zero EBX.
// No forced pointer-parameter overlap or persistent new pins retained.
// ?rva004D53B5@Transport@@QAE_NPAX@Z @0x004D53B5 225B: Transport winsock init plus buffer clear.
// Original matched sibling layout evidence: WSAStartup IAT 0x00BBA96C plus WSACleanup 0x00BBA970 plus timeGetTime 0x00BBA918 plus clearSlot 0x004D5133 plus offsets +0x40E00/+0x40E04/+0x40E08/+0x40E6C/+0x40E70 plus ret 4; caller 0x005A6B28; neighbours Transport.cpp and TransportRva004D5046.cpp.
extern "C" {
__declspec(dllimport) int __stdcall WSACleanup(void);
__declspec(dllimport) int __stdcall WSAStartup(unsigned short wVersionRequired, void *lpWSAData);
__declspec(dllimport) unsigned int __stdcall timeGetTime(void);
}

struct WSAData40E
{
	unsigned char m_versionLow;
	unsigned char m_versionHigh;
	char m_pad[0x18c - 2];
};

class UDP {
public: UDP(); ~UDP(); int Bind(unsigned int,unsigned short);
 int getLocalAddr(unsigned int&,unsigned short&);
private: char consumed[32];
};
struct TransportAddress {unsigned int ip;unsigned short port; TransportAddress(unsigned int a,unsigned short b):ip(a),port(b) {}};
void* __cdecl operator new(unsigned int);
void __cdecl operator delete(void*);
struct Rva004D4A80Slot
{
	UDP *m_object;
	TransportAddress address;
};

#pragma pack(push, 1)
struct TransportMessage
{
	char m_pad[0x404];
	int m_length;
	char m_tail[6];
};
#pragma pack(pop)

class Transport
{
public:
	bool init(const TransportAddress *addr);
	void clearSlot_Rva004D5133(unsigned short index);
private:
	TransportMessage m_outBuffer[128];
	TransportMessage m_inBuffer[128];
	bool m_flag40E00;
	char m_pad40E01[3];
	union {void *m_ptr40E04;unsigned int m_localIP;};
	bool m_winsockActive;
	char m_pad40E09[3];
	Rva004D4A80Slot m_slots[8];
	int m_int40E6C;
	int m_int40E70;
	int m_stats0[30];
	int m_stats1[30];
	int m_stats2[30];
	int m_stats3[30];
	int m_stats4[30];
	int m_stats5[30];
	int m_badPackets;
};


bool Transport::init(const TransportAddress *addr) {
 if(!m_winsockActive) {
  WSAData40E wsadata;
  if(WSAStartup(0x202,&wsadata)!=0) return false;
  if(wsadata.m_versionLow!=2 || wsadata.m_versionHigh!=2) {
   WSACleanup(); return false;
  }
  m_winsockActive=true;
 }
 m_flag40E00=true;
 for(int i=0;i<8;++i) clearSlot_Rva004D5133((unsigned short)i);
 m_slots[0].m_object=new UDP();
 if(!m_slots[0].m_object) return false;
 int result=-1; unsigned now=timeGetTime();
 while((result!=0) && ((timeGetTime()-now)<1000)) {
  result=m_slots[0].m_object->Bind(addr->ip,addr->port);
 }
 if(result!=0) {
  delete m_slots[0].m_object; m_slots[0].m_object=0; return false;
 }
 m_slots[0].address=TransportAddress(0,0);
 unsigned short localPort;
 m_slots[0].m_object->getLocalAddr(m_localIP,localPort);
 for(int i=0;i<128;++i) {
  m_outBuffer[i].m_length=0; m_inBuffer[i].m_length=0;
 }
 for(int i=0;i<30;++i) {
  m_stats0[i]=0; m_stats2[i]=0; m_stats1[i]=0;
  m_stats3[i]=0; m_stats5[i]=0; m_stats4[i]=0; m_badPackets=0;
 }
 m_int40E6C=0; m_int40E70=(int)timeGetTime(); return true;
}
