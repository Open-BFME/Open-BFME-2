// ??0Rva009A2A20Table@@QAE@XZ
extern "C" void* __cdecl memset(void*, int, unsigned int);
#pragma intrinsic(memset)
struct Rva009A2A20Table {
	int m_slots[0x2b7b];
	int m_count;
	int m_first;
	int m_last;
	Rva009A2A20Table();
	void rva00758A30();
};
Rva009A2A20Table::Rva009A2A20Table()
{
	m_first = 0;
	m_last = 0;
	memset(m_slots, 0, sizeof(m_slots));
	m_count = 0;
}

// Clean BF1 9cb Rva009A2A20TableCtor.cpp supplies this structural restart.
// Target758A30: complete INT3-delimited19B reads raw word0 then zeros wordADF0
// and copies the saved word into wordADF4. Reuse the existing constructor
// carrier because its independently measured field offsets agree. No direct
// calls establish the original semantic owner or an original method name.
// ?rva00758A30@Rva009A2A20Table@@QAEXXZ
void Rva009A2A20Table::rva00758A30()
{
	int current = m_slots[0];
	m_first = 0;
	m_last = current;
}
