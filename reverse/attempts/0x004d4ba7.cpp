// ?rva004D4BA7@Transport@@QAE_NXZ
// partial score=0.99 date=2026-10-05
// ?rva004D4BA7@Transport@@QAE_NXZ
// partial score=0.99 date=2026-10-01
// ?rva004D4BA7@Transport@@QAE_NXZ
// partial score=0.99 date=2026-09-30
// ?rva004D4BA7@Transport@@QAE_NXZ
// partial score=0.99 date=2026-09-30
// cl: /O1 /G7 /DNDEBUG /MD /EHsc
// ?rva004D4BA7@Transport@@QAE_NXZ @0x004D4BA7 353B drain 128 out-messages via slot UDP Write
// Evidence: callers 0x004D3736 0x004D54FE 0x005A83AF jmp 0x004CF900; callees timeGetTime IAT + rowed 0x00594C12 Write; stash 0.98 je-vs-jne plus clear-vs-ok order
extern "C" {
__declspec(dllimport) unsigned int __stdcall timeGetTime(void);
}

class Rva00594C12
{
public:
	int rva00594C12(const char *buf, int len, unsigned long addr, unsigned short port);
};

#define NULL 0

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
	bool rva004D4BA7(void);
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

// ?rva004D4BA7@Transport@@QAE_NXZ present-unmatched
// retail 0x004D4BA7 353B: drain 128 out-messages via slot UDP Write.
bool Transport::rva004D4BA7(void)
{
	struct MsgTail
	{
		int m_len;
		unsigned long m_addr;
		unsigned short m_port;
	};
	int i = 0;
	Rva004D4A80Slot *slot = m_slots;
	for (; i < 8; ++i, ++slot) {
		if (slot->m_object != NULL)
			break;
	}
	if (i == 8)
		return false;
	unsigned int now = timeGetTime();
	unsigned int limit = (unsigned int)m_int40E70 + 1000;
	if (limit < now) {
		m_int40E70 = (int)now;
		int mod = (m_int40E6C + 1) % 30;
		m_int40E6C = mod;
		m_stats5[mod] = 0;
		m_stats2[*(volatile int *)&m_int40E6C] = 0;
		m_stats3[*(volatile int *)&m_int40E6C] = 0;
		m_stats0[*(volatile int *)&m_int40E6C] = 0;
		m_stats4[*(volatile int *)&m_int40E6C] = 0;
		m_stats1[*(volatile int *)&m_int40E6C] = 0;
	}
	bool ok = true;
	char *msg = (char *)m_outBuffer + 0x404;
	int n = 0x80;
	do {
		MsgTail *tail = (MsgTail *)msg;
		if (tail->m_len != 0) {
			Rva00594C12 *udp;
			if (m_flag40E00) {
				udp = (Rva00594C12 *)m_slots[0].m_object;
			} else {
				int j = 0;
				int *px = &m_slots[0].m_x;
				for (;;) {
					if (px[-1] != 0 && px[0] == (int)tail->m_addr && *(unsigned short *)(px + 1) == tail->m_port)
						break;
					++j;
					px += 3;
					if (j >= 8) {
						udp = NULL;
						goto L_clear;
					}
				}
				int off = (j + 0x5681) * 12;
				udp = *(Rva00594C12 **)((char *)this + off);
			}
			int sent;
			if (udp == NULL)
				goto L_clear;
			sent = udp->rva00594C12(msg - 0x404, tail->m_len + 4, tail->m_addr, tail->m_port);
			if (sent <= 0)
				goto L_fail;
			m_stats5[m_int40E6C]++;
			m_stats2[m_int40E6C] += tail->m_len + 4;
L_clear:
			tail->m_len = 0;
			goto L_next;
L_fail:
			ok = false;
L_next:;
		}
		msg += 0x40E;
	} while (--n != 0);
	return ok;
}
