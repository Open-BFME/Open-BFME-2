// cl: /DNDEBUG /MD
// ?rva005DBA9C@Rva005DB98E@@QAE_N_N@Z retail 0x005DBA9C 177B
// Unlock human/slot scan for m_arr2 value 3; same class/offsets as neighbours.
// Retail funnels both branches' success through the single `return true;` after
// the if/else (true loop jumps forward over the false loop), which also reads
// the flag from [esp+8] before saving ebx/ebp/edi. Evidence: neighbours
// 0x005DBA60/0x005DBBA5 same class; offsets +0x14 +0x18 +0x8b8; callee isHuman
// 0x003FF0F1; classic 8x8 exclusive pair scan.
struct Elem005DB98E
{
	char m_data[20];
};

class GameSlot
{
public:
	bool isHuman() const;
};

class Rva005DB98E
{
	char m_pad0[0x14];
	unsigned short m_cur;
	char m_pad0b[2];
	int m_arr2[81];
	char m_pad1[0x218 - 0x18 - 81 * 4];
	Elem005DB98E m_arr[81];
	char m_pad2[0x8b8 - 0x86c];
	GameSlot **m_slots;
public:
	void* rva005DB98E(unsigned short x, unsigned short y);
	int rva005DB9BC(unsigned short x, unsigned short y);
	bool rva005DBA60(unsigned short x);
	bool rva005DBA9C(bool flag);
};

bool Rva005DB98E::rva005DBA9C(bool flag)
{
	if (m_cur >= 8)
		return true;
	if (flag)
	{
		for (int bx = 0; bx < 8; ++bx)
		{
			for (int bp = 0; bp < 8; ++bp)
			{
				if (bx == bp)
					continue;
				GameSlot *a = m_slots[bx];
				if (!a)
					continue;
				if (!a->isHuman())
					continue;
				GameSlot *b = m_slots[bp];
				if (!b)
					continue;
				if (!b->isHuman())
					continue;
				if (m_arr2[bp + bx * 8] != 3)
					return false;
			}
		}
	}
	else
	{
		for (int i = 0; i < 8; ++i)
		{
			if (i == m_cur)
				continue;
			GameSlot *s = m_slots[i];
			if (!s)
				continue;
			if (!s->isHuman())
				continue;
			if (m_arr2[m_cur + i * 8] != 3)
				return false;
			if (m_arr2[i + m_cur * 8] != 3)
				return false;
		}
	}
	return true;
}
