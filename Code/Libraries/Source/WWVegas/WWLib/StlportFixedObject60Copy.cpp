// cl: /O1 /DNDEBUG /MD

// ??0BfmeFixedObject60@@QAE@ABU0@@Z, retail 0x000B41EF (122B).
// Neutral 60-byte structured copy: vtable plus two ints init-listed, then
// three 16-byte blocks copied word by word over compiler-built elements.
// The array-cursor local is load-bearing: it homes the block base in edi
// so the twelve word stores ride the cursor while src stays in esi and
// this stays in ebx (all other homings sink this to esi and lose). The
// element default ctor is empty and defined here; its push address is a
// DIR32 absolute so any slot verifies, and the ??_H iterator call resolves
// through its ledger row with zero new pins. Original class and element
// names remain unknown; member names stay positional and honest.

struct BfmeFixedBlock16
{
	int m_word00;
	int m_word04;
	int m_word08;
	int m_word0C;
	BfmeFixedBlock16();
};

BfmeFixedBlock16::BfmeFixedBlock16()
{
}

struct BfmeFixedObject60
{
	void *m_vtable;
	int m_int04;
	int m_int08;
	BfmeFixedBlock16 m_blocks0C[3];
	BfmeFixedObject60(const BfmeFixedObject60 &src);
};

BfmeFixedObject60::BfmeFixedObject60(const BfmeFixedObject60 &src)
	: m_vtable(src.m_vtable), m_int04(src.m_int04), m_int08(src.m_int08)
{
	BfmeFixedBlock16 *dstBlocks = m_blocks0C;
	dstBlocks[0].m_word00 = src.m_blocks0C[0].m_word00;
	dstBlocks[0].m_word04 = src.m_blocks0C[0].m_word04;
	dstBlocks[0].m_word08 = src.m_blocks0C[0].m_word08;
	dstBlocks[0].m_word0C = src.m_blocks0C[0].m_word0C;
	dstBlocks[1].m_word00 = src.m_blocks0C[1].m_word00;
	dstBlocks[1].m_word04 = src.m_blocks0C[1].m_word04;
	dstBlocks[1].m_word08 = src.m_blocks0C[1].m_word08;
	dstBlocks[1].m_word0C = src.m_blocks0C[1].m_word0C;
	dstBlocks[2].m_word00 = src.m_blocks0C[2].m_word00;
	dstBlocks[2].m_word04 = src.m_blocks0C[2].m_word04;
	dstBlocks[2].m_word08 = src.m_blocks0C[2].m_word08;
	dstBlocks[2].m_word0C = src.m_blocks0C[2].m_word0C;
}
