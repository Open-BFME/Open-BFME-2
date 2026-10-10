// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /ICode/GameEngine/Include
// ?init@Transport@@QAE_NPBUTransportAddress@@@Z
// Retail 0x004D5219..0x004D53B5 (412 bytes ret 4).
// Transport::init: starts Winsock 2.2 once (WSAStartup 0x202 then a
// version check with WSACleanup on mismatch) then frees all eight socket
// slots through RemoveSocketForSlot 0x004D5133 and allocates a 32-byte UDP
// for slot 0 (UDP ctor 0x005948F5 dtor 0x00594918 under the new/delete
// unwind state). Binds it to the given address for up to one second of
// timeGetTime retries (UDP::Bind 0x00594B56) or deletes it and fails.
// Clears the slot address words and reads the local address back through
// UDP::getLocalAddr 0x0059495D into +0x40E04 and a scratch port. Then zeroes
// both 128-entry message rings (+0x404 lengths) the six 30-word statistics
// arrays and the bad-packet count and stamps +0x40E70 with timeGetTime.
// Evidence: WorldBuilder Transport::init callgraph and BFME1 Transport.cpp
// (rev 9cbfb551fe20) as the semantic guide; ZH Transport::init shape.
// Layout from the canonical Transport.h. The scratch port is block scoped
// after the bind so cl packs it into the dead address parameter slot
// (retail lea eax,[ebp+0xA]).
extern "C" {
__declspec(dllimport) int __stdcall WSACleanup(void);
__declspec(dllimport) int __stdcall WSAStartup(unsigned short wVersionRequired, void *lpWSAData);
__declspec(dllimport) unsigned int __stdcall timeGetTime(void);
}
#include "GameNetwork/Transport.h"

// Winsock WSADATA (0x190 bytes): only the negotiated version bytes are read.
struct WSAData40E
{
	unsigned char m_versionLow;
	unsigned char m_versionHigh;
	char m_pad[0x18c - 2];
	void *m_vendorInfo;
};

class UDP
{
public:
	UDP();
	~UDP();
	int Bind(unsigned int ip, unsigned short port);
	int getLocalAddr(unsigned int &ip, unsigned short &port);
private:
	char m_body[32];
};

struct TransportAddress
{
	unsigned int ip;
	unsigned short port;
	TransportAddress(unsigned int a, unsigned short b) : ip(a), port(b) {}
};

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

bool Transport::init(const TransportAddress *addr)
{
	if (!m_winsockActive)
	{
		WSAData40E wsadata;
		int err = WSAStartup(0x202, &wsadata);
		if (err != 0)
			return false;
		if (wsadata.m_versionLow != 2 || wsadata.m_versionHigh != 2)
		{
			WSACleanup();
			return false;
		}
		m_winsockActive = true;
	}
	m_flag40E00 = true;
	for (int i = 0; i < 8; ++i)
		RemoveSocketForSlot((unsigned short)i);
	m_slots[0].m_object = new UDP();
	if (!m_slots[0].m_object)
		return false;

	int result = -1;
	unsigned int now = timeGetTime();
	while ((result != 0) && ((timeGetTime() - now) < 1000))
	{
		result = ((UDP *)m_slots[0].m_object)->Bind(addr->ip, addr->port);
	}
	if (result != 0)
	{
		delete (UDP *)m_slots[0].m_object;
		m_slots[0].m_object = 0;
		return false;
	}
	*(TransportAddress *)&m_slots[0].m_x = TransportAddress(0, 0);

	{
		unsigned short localPort;
		((UDP *)m_slots[0].m_object)->getLocalAddr(*(unsigned int *)&m_ptr40E04, localPort);
	}
	for (int i = 0; i < 128; ++i)
	{
		m_outBuffer[i].m_length = 0;
		m_inBuffer[i].m_length = 0;
	}
	for (int i = 0; i < 30; ++i)
	{
		m_stats0[i] = 0;
		m_stats2[i] = 0;
		m_stats1[i] = 0;
		m_stats3[i] = 0;
		m_stats5[i] = 0;
		m_stats4[i] = 0;
		m_badPackets = 0;
	}
	m_int40E6C = 0;
	m_int40E70 = (int)timeGetTime();
	return true;
}
