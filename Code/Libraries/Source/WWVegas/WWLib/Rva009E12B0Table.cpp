// cl: /MD
// Provenance: Open-BFME-1 game/Libraries/Source/WWVegas/WWLib/Rva009E12B0Table.cpp at 6583b3c1ff; include paths repointed at the
// reference checkout and built the BFME2 way (/arch:SSE /G7), where its body places
// exactly once in game.dat by masked byte search.
// Retail 0x009E12B0: initialize the two 256-entry tables and scalar flags.
// The native owner is unknown, so the address stays in the class identity.
extern "C" void* __cdecl memset(void*, int, unsigned int);
#pragma intrinsic(memset)
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
struct Rva009E12B0Pair { int m_a; int m_b; };
struct Rva009E12B0Table {
	int m_owner;
	int m_4;
	int m_8;
	int m_table[0x100];
	Rva009E12B0Pair m_pairs[0x100];
	bool m_flag;
	int m_c10;
	short m_c14;
	Rva009E12B0Table(int owner);
};
Rva009E12B0Table::Rva009E12B0Table(int owner)
	: m_owner(owner), m_4(0), m_8(0)
{
	// Retail initializes each pair before setting the table flags.
	Rva009E12B0Pair *pair = m_pairs;
	int remaining = 0x100;
	do { pair->m_a = 0; pair->m_b = 0; ++pair; } while (--remaining);
	m_flag = false;
	m_c10 = 0;
	// Preserve the two flag stores before the zeroing loop's EAX setup.
	_ReadWriteBarrier();
	memset(m_table, 0, 0x400);
	memset(m_pairs, 0, 0x800);
	m_c14 = 0;
}
