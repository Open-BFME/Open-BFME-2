// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O1 /G7
// ?rva0059517F@Rva0059517F@@QAE_NKGGG_N@Z @0x0059517F 148B: GameNetwork packet send via Rva00594DC0 convert plus CRC plus FirewallHelper search plus Rva00594C12 write. Evidence: rowed Convert 0x00594DC0 with ecx plus Msg arg; CRC over Msg+4 len 0x10 seed 0 then htonl into m_00; rowed Search 0x00594D77 by port; Write 0x00594C12 with buf len 0x14; ret 0x14 with 5 stack args and bool result.
// ?rva00595213@Rva0059517F@@QAE_NPAVUDP@@KGG_N@Z @0x00595213 177B: BFME 2's
// UDP-socket variant of the same mangler request (no ZH counterpart). Target
// evidence: the rowed UDP error query 0x00594A06 (-11 returns false), the
// pinned UDP::getLocalAddr whose port becomes the packet's original port,
// the same memset/convert/CRC/htonl sequence, the rowed UDP write 0x00594C12
// to (address, port), the packet ID stored at +0x88, ret 0x14.
#include <string.h>

extern "C" __declspec(dllimport) unsigned long __stdcall htonl(unsigned long hostlong);
unsigned int __cdecl BFMEComputeCRC(const unsigned char *data, unsigned int len, unsigned int seed);

struct Rva00594DC0Msg
{
	unsigned long m_00;
	unsigned short m_04;
	unsigned short m_06;
	unsigned short m_08;
	unsigned short m_0A;
};

class Rva00594DC0
{
public:
	void rva00594DC0(Rva00594DC0Msg *msg);
};

class FirewallHelperClass
{
public:
	void *rva00594D77(unsigned short port);
};

class Rva00594C12
{
public:
	int rva00594C12(const char *buf, int len, unsigned long addr, unsigned short port);
};

struct Rva0059517FPacket
{
	unsigned long m_crc;
	unsigned short m_04;
	unsigned short m_06;
	unsigned short m_08;
	unsigned short m_0A;
	unsigned char m_0C[4];
	unsigned char m_10;
	unsigned char m_11;
	unsigned char m_12[2];
	int _len;
	char _pad[8];
};

class UDP
{
public:
	int rva00594A06();
	int getLocalAddr(unsigned int &ip, unsigned short &port);
};

class Rva0059517F
{
public:
	bool rva0059517F(unsigned long a1, unsigned short a2, unsigned short a3, unsigned short a4, bool a5);
	bool rva00595213(UDP *udp, unsigned long address, unsigned short packetID, unsigned short port, bool blitzme);
private:
	char m_pad[0x88];
	unsigned short m_88;
};

bool Rva0059517F::rva0059517F(unsigned long a1, unsigned short a2, unsigned short a3, unsigned short a4, bool a5)
{
	Rva0059517FPacket pkt;
	memset(&pkt, 0x44, 0x14);
	pkt.m_06 = a3;
	pkt.m_11 = (a5 != 0);
	pkt.m_10 = 0xC;
	pkt.m_04 = 0xF00E;
	pkt.m_0A = a2;
	((Rva00594DC0 *)this)->rva00594DC0((Rva00594DC0Msg *)&pkt);
	unsigned int crc = BFMEComputeCRC((const unsigned char *)&pkt.m_04, 0x10, 0);
	pkt.m_crc = htonl(crc);
	pkt._len = 0x14;
	void *entry = ((FirewallHelperClass *)this)->rva00594D77(a2);
	if (entry == 0)
		return false;
	Rva00594C12 *udp = *(Rva00594C12 **)entry;
	udp->rva00594C12((const char *)&pkt, 0x14, a1, a4);
	return true;
}

bool Rva0059517F::rva00595213(UDP *udp, unsigned long address, unsigned short packetID, unsigned short port, bool blitzme)
{
	if (udp->rva00594A06() == -11)
		return false;
	unsigned int localIP;
	unsigned short localPort;
	udp->getLocalAddr(localIP, localPort);
	Rva0059517FPacket pkt;
	memset(&pkt, 0x44, 0x14);
	pkt.m_11 = (blitzme != 0);
	pkt.m_0A = localPort;
	pkt.m_10 = 0xC;
	pkt.m_06 = packetID;
	pkt.m_04 = 0xF00E;
	((Rva00594DC0 *)this)->rva00594DC0((Rva00594DC0Msg *)&pkt);
	unsigned int crc = BFMEComputeCRC((const unsigned char *)&pkt.m_04, 0x10, 0);
	pkt.m_crc = htonl(crc);
	pkt._len = 0x14;
	((Rva00594C12 *)udp)->rva00594C12((const char *)&pkt, 0x14, address, port);
	m_88 = packetID;
	return true;
}
