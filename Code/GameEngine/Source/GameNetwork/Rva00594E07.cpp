// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD
//
// ?rva00594E07@Rva00594E07@@QAEGGH@Z, retail 0x00594E07, 232 bytes.
// Firewall spare-socket pump over 8 entries calling rowed findEmptyMessage UDP Read CRC Convert plus IAT htonl htons.
// Evidence: prev Rva00594DC0Convert plus FirewallHelper 8x0x1E at +0x8A length at +0x14 plus SpareSocket 8B at +0x14; 6 callers unclaimed; unblocks 6 (4 ready); same flags as neighbours.
extern "C" __declspec(dllimport) unsigned long __stdcall htonl(unsigned long hostlong);
extern "C" __declspec(dllimport) unsigned short __stdcall htons(unsigned short hostshort);
#pragma pack(push, 1)
struct ManglerData
{
	unsigned int m_crc;
	unsigned short m_magic;
	unsigned short m_packetID;
	unsigned short m_mangledPortNumber;
	unsigned short m_originalPortNumber;
	unsigned char m_mangledAddress[4];
	unsigned char m_netCommandType;
	unsigned char m_blitzMe;
	unsigned short m_padding;
};
struct ManglerMessage
{
	ManglerData m_data;
	int m_length;
	unsigned int m_ip;
	unsigned short m_port;
};
#pragma pack(pop)
struct sockaddr_in
{
	char m_data[16];
};
class UDP
{
public:
	int Read(unsigned char *a, unsigned int b, struct sockaddr_in *c);
};
unsigned int __cdecl ComputeCRC(const unsigned char *a, unsigned int b, unsigned int c);
class Rva00594E07;
class FirewallHelperClass
{
	friend class Rva00594E07;
	ManglerMessage *findEmptyMessage();
};
struct SpareSocket
{
	UDP *m_udp;
	int m_unk;
};
struct Rva00594DC0Msg
{
	unsigned long m_00;
	unsigned short m_04;
	unsigned short m_06;
	unsigned short m_08;
	unsigned short m_0a;
};
class Rva00594DC0
{
public:
	void rva00594DC0(Rva00594DC0Msg *msg);
};
class Rva00594E07
{
public:
	unsigned short rva00594E07(unsigned short a, int b);
private:
	char m_pad0[0x14];
	SpareSocket m_spare[8];
	char m_pad1[0x8A - 0x14 - 8 * 8];
	ManglerMessage m_msgs[8];
};
unsigned short Rva00594E07::rva00594E07(unsigned short a, int b)
{
	(void)b;
	ManglerMessage *sel = 0;
	SpareSocket *s = m_spare;
	int i = 0;
	sockaddr_in from;
	unsigned int crc;
	for (; i < 8; ++i, ++s)
	{
		UDP *udp = s->m_udp;
		if (udp != 0)
		{
			ManglerMessage *msg = ((FirewallHelperClass *)this)->findEmptyMessage();
			if (msg == 0)
				break;
			int len = udp->Read((unsigned char *)msg, 0x14, &from);
			if (len > 0)
			{
				crc = ComputeCRC((const unsigned char *)msg + 4, 0x10, 0);
				if (crc == htonl(msg->m_data.m_crc))
				{
					((Rva00594DC0 *)this)->rva00594DC0((Rva00594DC0Msg *)msg);
					unsigned short pid = msg->m_data.m_packetID;
					msg->m_length = len;
					if (pid == a)
					{
						msg->m_length = 0;
						sel = msg;
					}
					if (htons(pid) == a)
					{
						msg->m_length = 0;
						sel = msg;
					}
				}
			}
		}
	}
	if (sel == 0)
	{
		int n = 8;
		int *pl = &m_msgs[0].m_length;
		for (; n != 0; --n)
		{
			if (*pl != 0)
			{
				if (*(unsigned short *)((char *)pl - 0xE) == a)
				{
					sel = (ManglerMessage *)((char *)pl - 0x14);
					*pl = 0;
				}
			}
			pl = (int *)((char *)pl + 0x1E);
		}
	}
	if (sel == 0)
		return 0;
	return sel->m_data.m_mangledPortNumber;
}
