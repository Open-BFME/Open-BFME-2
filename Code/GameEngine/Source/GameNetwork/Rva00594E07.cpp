// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/bfme2_firewallhelper /Ireference/shims/bfme2_ascii /Ireference/shims/bfme2_ascii_common /Ireference/open-bfme-1/inputs/reference/shims/firewall /Ireference/open-bfme-1/inputs/reference/shims/ini /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
//
// ?rva00594E07@Rva00594E07@@QAEGGH@Z, retail 0x00594E07, 232 bytes.
// Firewall spare-socket pump over 8 entries calling rowed findEmptyMessage UDP Read CRC Convert plus IAT htonl htons.
// Evidence: prev Rva00594DC0Convert plus FirewallHelper 8x0x1E at +0x8A length at +0x14 plus SpareSocket 8B at +0x14; 6 callers unclaimed; unblocks 6 (4 ready); same flags as neighbours.
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/crc.h"
#include "Common/UserPreferences.h"
#include "GameNetwork/FirewallHelper.h"
#include "GameNetwork/NAT.h"
#include "GameNetwork/udp.h"
#include "GameNetwork/NetworkDefs.h"
#include "GameNetwork/GameSpy/GSConfig.h"

unsigned int __cdecl ComputeCRC(const unsigned char *a, unsigned int b, unsigned int c);
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
	bool rva005952C4(void *src, unsigned short len, unsigned short *out);
	char m_pad00[0x88];
private:
	unsigned short m_88; // +0x88
};
class Rva00594E07
{
public:
	unsigned short rva00594E07(unsigned short packetID, int time);
private:
	char m_pad0[0x14];
	SpareSocketStruct m_spare[8];
	char m_pad1[0x8A - 0x14 - 8 * 8];
	ManglerMessage m_msgs[8];
};
unsigned short Rva00594E07::rva00594E07(unsigned short packetID, int time)
{
	(void)time;
	ManglerMessage *sel = 0;
	SpareSocketStruct *spareSocket = m_spare;
	int i = 0;
	sockaddr_in from;
	unsigned int crc;
	for (; i < 8; ++i, ++spareSocket)
	{
		UDP *udp = spareSocket->udp;
		if (udp != 0)
		{
			ManglerMessage *msg = ((FirewallHelperClass *)this)->findEmptyMessage();
			if (msg == 0)
				break;
			int len = udp->Read((unsigned char *)msg, 0x14, &from);
			if (len > 0)
			{
				crc = ComputeCRC((const unsigned char *)msg + 4, 0x10, 0);
				if (crc == htonl(msg->data.CRC))
				{
					((Rva00594DC0 *)this)->rva00594DC0((Rva00594DC0Msg *)msg);
					unsigned short pid = msg->data.PacketID;
					msg->length = len;
					if (pid == packetID)
					{
						msg->length = 0;
						sel = msg;
					}
					if (htons(pid) == packetID)
					{
						msg->length = 0;
						sel = msg;
					}
				}
			}
		}
	}
	if (sel == 0)
	{
		int remainingMessages = 8;
		int *pl = &m_msgs[0].length;
		for (; remainingMessages != 0; --remainingMessages)
		{
			if (*pl != 0)
			{
				if (*(unsigned short *)((char *)pl - 0xE) == packetID)
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
	return sel->data.MyMangledPortNumber;
}
