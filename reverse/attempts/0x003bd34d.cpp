// ?rva003BD34D@@YGXH@Z
// partial score=0.94 date=2026-10-06
// cl: /O1 /DNDEBUG /MD
//
// Third member of the four-strong homogeneous family at 0x003BD32B..0x003BD391
// (34B each, dump range 18): resolves the 0x00E031E8 global's +0x10 slot to a
// Rva004266A1 (the rowed QAEEH family at 0x0042680D proves the class) and
// forwards (index - 1, 0) to 0x0042682B. Retail bytes at 0x003BD34D:
// a1 e8 31 e0 00 | 85 c0 | 74 16 | 8b 40 10 | 85 c0 | 74 0f | 8b 4c 24 04 |
// 49 | 6a 00 | 51 | 8b c8 | e8 bf 94 06 00 (rel32 -> 0x0042682B) | c2 04 00.
// Kept in its own TU: beside its flag-1 sisters the flag-0 spelling emits
// the slot10 load into ecx (32B) instead of retail's eax shape.
class Rva004266A1
{
public:
	void rva0042682B(int index, int value);
};

struct Rva004266A1Holder
{
	char m_pad[0x10];
	Rva004266A1 *m_slot10;
};

extern Rva004266A1Holder *g_00E031E8;

void __stdcall rva003BD34D(int index)
{
	Rva004266A1Holder *holder = g_00E031E8;
	if (holder == 0)
		return;
	Rva004266A1 *p = holder->m_slot10;
	if (p == 0)
		return;
	p->rva0042682B(index - 1, 0);
}
