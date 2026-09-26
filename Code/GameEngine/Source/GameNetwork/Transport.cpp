// cl: /O1 /G7 /DNDEBUG /MD /EHsc
//
// BFME2 network Transport helpers. The class is a BFME2 rewrite of the
// Zero Hour / BFME1 Transport: the message rings still sit at +0x00000 and
// +0x20700 with stride 0x40E, but the tail is reworked around an 8-slot
// table (cleared one slot at a time through the word-indexed slot clearer
// at 0x4D5133) and a winsock-active byte flag at +0x40E08.

extern "C" {
__declspec(dllimport) int __stdcall WSACleanup(void);
}

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

class Transport
{
public:
	Transport(void);
	~Transport(void);
	void clearSlot_Rva004D5133(unsigned short index);
	void Rva004D5496(void);
	void clearBuffer_Rva004D4A59(void);

private:
	struct Message
	{
		char m_bytes[0x40E];
	};
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

// ??0Rva004D4A80Slot@@QAE@XZ present-unmatched
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
		clearSlot_Rva004D5133((unsigned short)i);
	if (m_winsockActive) {
		WSACleanup();
		m_winsockActive = false;
	}
}

// ??0Transport@@QAE@XZ
// retail 0x004D4AF2, 153 bytes.
Transport::Transport(void)
{
	m_flag40E00 = true;
	m_ptr40E04 = NULL;
	m_winsockActive = false;
	m_int40E6C = 0;
	m_int40E70 = 0;
	m_badPackets = 0;
	Message *out = m_outBuffer;
	int n = 128;
	do {
		((Transport*)out)->clearBuffer_Rva004D4A59();
		((Transport*)(out + 128))->clearBuffer_Rva004D4A59();
		++out;
	} while (--n != 0);
	int *p = m_stats1;
	int m = 30;
	do {
		p[-30] = 0;
		p[0] = 0;
		p[30] = 0;
		p[60] = 0;
		p[90] = 0;
		p[120] = 0;
		++p;
	} while (--m != 0);
}

// ??1Transport@@QAE@XZ
// retail 0x004494BA, 64 bytes. Runs the slot clearer, then the eight
// slot destructors run through the vector destructor iterator.
Transport::~Transport(void)
{
	Rva004D5496();
}
