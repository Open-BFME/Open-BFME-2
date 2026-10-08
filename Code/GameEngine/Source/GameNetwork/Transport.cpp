// cl: /O1 /G7 /DNDEBUG /MD /EHsc
//
// BFME2 network Transport helpers. The class is a BFME2 rewrite of the
// Zero Hour / BFME1 Transport: the message rings still sit at +0x00000 and
// +0x20700 with stride 0x40E, but the tail is reworked around an 8-slot
// table (cleared one slot at a time through the word-indexed slot clearer
// at 0x4D5133) and a winsock-active byte flag at +0x40E08.
// The winsock init (0x004D53B5) and slot setter (0x004D51A7) were folded in
// from split units with these exact flags. The constructor keeps its own
// unit: it builds the slot array against an out-of-line element destructor.

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

struct SlotVals
{
	int x;
	int y;
};

#define NULL 0

// Slot element constructor at 0x004D4A80 (14 bytes, present-unmatched):
// zeroes the pointer, the int and the short, leaving two pad bytes.
// The empty destructor folds with the other empty dtors.
struct Rva004D4A80Slot
{
	void *m_object;
	int m_x;
	short m_y;
	char m_pad[2];
	Rva004D4A80Slot(void);
	~Rva004D4A80Slot(void) {}
};

// ?clearBuffer_Rva004D4A59@Transport@@QAEXXZ present-unmatched
// (declared-only; resolves through the pin at 0x004D4A59)

// Zero Hour's UDP socket wrapper; AllowBroadcasts is rowed at 0x00594B2E.
class UDP
{
public:
	int AllowBroadcasts(bool status);
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

private:
#pragma pack(push, 1)
	struct Message
	{
		char m_pad[0x404];
		int m_length; // +0x404
		char m_tail[6];
	};
#pragma pack(pop)
	Message m_outBuffer[128];
	Message m_inBuffer[128];
	bool m_flag40E00;
	void *m_ptr40E04;
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

Rva004D4A80Slot::Rva004D4A80Slot(void)
{
	m_object = NULL;
	m_x = 0;
	m_y = 0;
}

// ?Rva004D5496@Transport@@QAEXXZ
// retail 0x004D5496, 43 bytes. Clears the 8 transport slots, then shuts
// down winsock if the active flag is set.
void Transport::Rva004D5496(void)
{
	for (int i = 0; i < 8; ++i)
		RemoveSocketForSlot((unsigned short)i);
	if (m_winsockActive) {
		WSACleanup();
		m_winsockActive = false;
	}
}

// ??0Transport@@QAE@XZ
// retail 0x004D4AF2, 153 bytes.
// Transport::Transport: defined in TransportCtor.cpp (its row's unit).

// ??1Transport@@QAE@XZ
// retail 0x004494BA, 64 bytes. Runs the slot clearer, then the eight
// slot destructors run through the vector destructor iterator.
Transport::~Transport(void)
{
	Rva004D5496();
}

// Transport::allowBroadcasts, retail 0x004D5112 (33 bytes): Zero Hour's body
// under WB's name (Transport.cpp). The UDP socket is the first slot's object;
// retail folds the two tests into one && (xor/inc for the true arm).
bool Transport::allowBroadcasts(bool allowBroadcasts)
{
	UDP *udpsock = (UDP *)m_slots[0].m_object;
	return udpsock != NULL && udpsock->AllowBroadcasts(allowBroadcasts) != 0;
}

// ?setSlotSocket@Transport@@QAEXPAXGPAH@Z @0x004D51A7 70B: Transport slot setter
// at +0x40E0C. When index < 8 clears the slot via rowed clearSlot then
// stores object and two ints. Evidence: retail cmp word 8 jae plus call
// 0x004D5133 plus dual imul 0xC plus stores at +0x40E0C/+0x40E10/+0x40E14;
// ret 0xC proves 3 args; caller at 0x005A6E62.
void Transport::setSlotSocket(void *obj, unsigned short index, int *vals)
{
	if (index >= 8)
		return;
	RemoveSocketForSlot(index);
	m_slots[index].m_object = obj;
	*(SlotVals *)&m_slots[index].m_x = *(SlotVals *)vals;
}

// ?rva004D53B5@Transport@@QAE_NPAX@Z @0x004D53B5 225B: Transport winsock init plus buffer clear.
// Target evidence: WSAStartup IAT 0x00BBA96C plus WSACleanup 0x00BBA970 plus
// timeGetTime 0x00BBA918 plus clearSlot 0x004D5133 plus offsets
// +0x40E00/+0x40E04/+0x40E08/+0x40E6C/+0x40E70 plus ret 4; caller 0x005A6B28.
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
