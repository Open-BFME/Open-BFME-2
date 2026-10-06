// cl: /MD
// ?rva00531132@Rva00531132@@QAEX_NH@Z @ 0x00531132 (77B): __thiscall add/remove int in 12-entry set; caller at 0x005315A5.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
class Rva00531132
{
public:
	void rva00531132(bool add, int value);
	int rva0053117F(int index);
	int m_count;
	int m_items[12];
};
void Rva00531132::rva00531132(bool add, int value)
{
	if (value == 0)
		return;
	int count = m_count;
	int index = 0;
	if (count > 0)
	{
		int *p = m_items;
		do
		{
			if (*p == value)
				break;
			++index;
			++p;
			_ReadWriteBarrier();
		} while (index < m_count);
	}
	if (add)
	{
		if (index < count)
			return;
		if (count >= 12)
			return;
		m_items[count] = value;
		++m_count;
	}
	else
	{
		if (index >= count)
			return;
		int last = count - 1;
		m_count = last;
		m_items[index] = m_items[last];
	}
}

// BFME1 donor6d9434269164392c5ba62aaa7c15a86b5b020d76:
// htreemgr.cpp Get_Tree(int) under O1/G7/MD supplied the bounds-check lead.
// Copyright2025 Electronic Arts Inc.; GPL-3.0-or-later, as in the donor.
// Target Ghidra23B at53117F; caller531660 accesses the same +0 count/+4
// word array used by the rowed77B mutator above. Its add limit is12.
// The caller's cell stride is44h, not a proof of the donor's tree manager.
// Original names and value identity (integer ID versus pointer bits) are
// unknown. Reuse the existing integer view; do not claim HTreeClass.
int Rva00531132::rva0053117F(int index)
{
	if (index >= 0 && index < m_count)
		return m_items[index];
	return 0;
}
