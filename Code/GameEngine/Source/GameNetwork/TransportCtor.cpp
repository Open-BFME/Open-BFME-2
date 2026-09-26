// cl: /O1 /G7 /DNDEBUG /MD /EHsc
//
// BFME2 network Transport constructor. Same class model as Transport.cpp
// but this TU builds without EH: retail's constructor has no exception
// prologue even though it constructs the slot array through the vector
// constructor iterator.

#define NULL 0

// Slot element at +0x40E0C (declared-only here; defined in Transport.cpp).
struct Rva004D4A80Slot
{
	void *m_object;
	int m_x;
	short m_y;
	char m_pad[2];
	Rva004D4A80Slot(void);
	~Rva004D4A80Slot(void);
};

class Transport
{
public:
	Transport(void) throw();
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

// ??0Transport@@QAE@XZ
// retail 0x004D4AF2, 153 bytes. The three flag/pointer scalars ride in
// the mem-init list (prologue, interleaved with the slot array setup by
// the scheduler); the counters zero in the body after the array call.
Transport::Transport(void) throw()
  : m_flag40E00(true),
    m_ptr40E04(NULL),
    m_winsockActive(false)
{
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
