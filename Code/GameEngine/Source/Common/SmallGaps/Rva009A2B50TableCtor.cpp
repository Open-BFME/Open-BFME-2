// ??0Rva009A2B50Table@@QAE@XZ
extern "C" void* __cdecl memset(void*, int, unsigned int);
#pragma intrinsic(memset)
struct Rva009A2B50Table {
	int m_slots[0x493];
	int m_count;
	int m_first;
	int m_last;
	Rva009A2B50Table();
	void rva00758B60();
};
Rva009A2B50Table::Rva009A2B50Table()
{
	m_first = 0;
	m_last = 0;
	memset(m_slots, 0, sizeof(m_slots));
	m_count = 0;
}

// Clean BF1 9cb Rva009A2B50TableCtor.cpp supplies this structural restart.
// Target758B60: complete INT3-delimited19B reads raw word0 then zeros word1250
// and copies the saved word into word1254. Reuse the existing constructor
// carrier because its independently measured field offsets agree. No direct
// calls establish the original semantic owner or an original method name.
// ?rva00758B60@Rva009A2B50Table@@QAEXXZ
void Rva009A2B50Table::rva00758B60()
{
	int current = m_slots[0];
	m_first = 0;
	m_last = current;
}
