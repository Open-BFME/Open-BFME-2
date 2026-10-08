// ?init@Transport@@QAE_NPBUTransportAddress@@@Z
// partial score=0.9878640776699029 date=2026-10-08
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
// BFME1 Transport.cpp rev9cbfb551fe20 is the semantic guide.
// Native complete [004D5219,004D53B5) and WB callgraph witness the
// eight-slot adaptation. Existing proper Bind188 provider now landed.
// WSAData has the actual190B/align4 extent including vendor pointer;
// the earlier bank shortened this to18C and hid four frame bytes.
// Current412B body preserves the API buffer size, but native reuses
// dead parameter storage for localPort; compiler uses a separate slot.
// UDP ctor/dtor ABI comes from existing address pins; owner identities
// still need reconciliation before this could become linking source.
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
	void *m_vendorInfo;
};

class UDP {
public: UDP(); ~UDP(); int Bind(unsigned int,unsigned short);
 int getLocalAddr(unsigned int&,unsigned short&);
private: char consumed[32];
};
struct TransportAddress {unsigned int ip;unsigned short port; TransportAddress(unsigned int a,unsigned short b):ip(a),port(b) {}};
void* __cdecl operator new(unsigned int);
void __cdecl operator delete(void*);

#ifndef BFME2_NETWORK_TRANSPORT_H
#define BFME2_NETWORK_TRANSPORT_H

// BFME 2 Transport layout retained from the byte-verified home unit.
// Target evidence: 0x004D53B5 clears two 128-entry rings at stride 0x40E,
// eight 12-byte slots at +0x40E0C, and six 30-word statistics arrays.
// 0x004D51A7 and 0x004D51ED independently witness both address words.
// WorldBuilder Transport.cpp supplies the class/setter identity; private
// field labels below describe offsets, without asserting original names.
// Header adoption is gated per unit; incompatible views remain queued.

class Rva00594DC0;
struct TransportAddress;
struct NetPacketAddress;

struct Rva004D4A80Slot
{
	void *m_object;
	int m_x;
	short m_y;
	char m_pad[2];
	Rva004D4A80Slot(void);
	~Rva004D4A80Slot(void) {}
};

class Transport
{
public:
	Transport(void);
	bool allowBroadcasts(bool allowBroadcasts);
	~Transport(void);
	void RemoveSocketForSlot(unsigned short index);
	void Rva004D5496(void);
	void clearBuffer_Rva004D4A59(void);
	bool rva004D53B5(void *addr);
	void setSlotSocket(void *obj, unsigned short index, int *vals);
	void setDestAddrToSocket(int index, void *address);
	bool doRecv(Rva00594DC0 *receiver);
	bool update(Rva00594DC0 *receiver);
	bool doSend();
	bool init(const TransportAddress *);
	bool queueSend(NetPacketAddress *, const unsigned char *, int);

private:
#pragma pack(push, 1)
	struct Message
	{
		unsigned int m_crc;
		unsigned char m_data[0x400];
		int m_length; // +0x404
		unsigned long m_addr;
		unsigned short m_port;
	};
#pragma pack(pop)
	Message m_outBuffer[128];
	Message m_inBuffer[128];
	bool m_flag40E00;
	union { void *m_ptr40E04; unsigned int m_localIP; };
	bool m_winsockActive;
	// Eight 12-byte slots at +0x40E0C. The first word holds the slot's
	// object pointer (the clearer compares and zeroes it); the element
	// constructor zeroes the first ten bytes and the destructor is an
	// empty inline, folded with the other empty dtors.
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

typedef char TransportSizeWitness[(sizeof(Transport) == 0x41148) ? 1 : -1];

#endif

bool Transport::init(const TransportAddress *addr) {
 unsigned short localPort;
 if(!m_winsockActive) {
  WSAData40E wsadata;
  int err=WSAStartup(0x202,&wsadata);
  if(err!=0) return false;
  if(wsadata.m_versionLow!=2 || wsadata.m_versionHigh!=2) {
   WSACleanup(); return false;
  }
  m_winsockActive=true;
 }
 m_flag40E00=true;
 for(int i=0;i<8;++i) RemoveSocketForSlot((unsigned short)i);
 m_slots[0].m_object=new UDP();
 if(!m_slots[0].m_object) return false;
 int result=-1; unsigned now=timeGetTime();
 while((result!=0) && ((timeGetTime()-now)<1000)) {
  result=((UDP *)m_slots[0].m_object)->Bind(addr->ip,addr->port);
 }
 if(result!=0) {
  delete (UDP *)m_slots[0].m_object; m_slots[0].m_object=0; return false;
 }
 *(TransportAddress *)&m_slots[0].m_x=TransportAddress(0,0);

 ((UDP *)m_slots[0].m_object)->getLocalAddr(m_localIP,localPort);
 for(int i=0;i<128;++i) {
  m_outBuffer[i].m_length=0; m_inBuffer[i].m_length=0;
 }
 for(int i=0;i<30;++i) {
  m_stats0[i]=0; m_stats2[i]=0; m_stats1[i]=0;
  m_stats3[i]=0; m_stats5[i]=0; m_stats4[i]=0; m_badPackets=0;
 }
 m_int40E6C=0; m_int40E70=(int)timeGetTime(); return true;
}
