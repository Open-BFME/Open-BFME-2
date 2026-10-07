// cl: /DNDEBUG /MD /EHsc
// ?rva004D53B5@Transport@@QAE_NPAX@Z @0x004D53B5 225B: Transport winsock init plus buffer clear.
// Target evidence: WSAStartup IAT 0x00BBA96C plus WSACleanup 0x00BBA970 plus timeGetTime 0x00BBA918 plus clearSlot 0x004D5133 plus offsets +0x40E00/+0x40E04/+0x40E08/+0x40E6C/+0x40E70 plus ret 4; caller 0x005A6B28; neighbours Transport.cpp and TransportRva004D5046.cpp.
extern "C" {
__declspec(dllimport) int __stdcall WSACleanup(void);
__declspec(dllimport) int __stdcall WSAStartup(unsigned short wVersionRequired, void *lpWSAData);
__declspec(dllimport) unsigned int __stdcall timeGetTime(void);
}

struct WSAData40E
{
	unsigned char m_versionLow;
	unsigned char m_versionHigh;
	char m_pad[0x190 - 2];
};

struct Rva004D4A80Slot
{
	void *m_object;
	int m_x;
	short m_y;
	char m_pad[2];
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
	bool rva004D53B5(void *addr);
	// Native calls target the verified TransportUpdate.cpp slot-removal provider.
	void RemoveSocketForSlot(unsigned short index);
private:
	TransportMessage m_outBuffer[128];
	TransportMessage m_inBuffer[128];
	bool m_flag40E00;
	char m_pad40E01[3];
	void *m_ptr40E04;
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

bool Transport::rva004D53B5(void *addr)
{
	if (!m_winsockActive)
	{
		unsigned short verReq = 0x202;
		WSAData40E wsadata;
		int err = WSAStartup(verReq, &wsadata);
		if (err != 0)
			return false;
		if (wsadata.m_versionLow != 2 || wsadata.m_versionHigh != 2)
		{
			WSACleanup();
			return false;
		}
		m_winsockActive = true;
	}
	m_flag40E00 = false;
	m_ptr40E04 = addr;
	for (int i = 0; i < 8; ++i)
		RemoveSocketForSlot((unsigned short)i);
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
