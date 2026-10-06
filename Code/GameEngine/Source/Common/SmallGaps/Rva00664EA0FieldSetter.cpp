// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Address-derived body for retail 0x00664EA0 (17 bytes). The exact BFME1
// donor is setPair in Rva007F0A50PairStore.cpp, but its owner and member names
// are not target evidence: the BFME1 body is ICF-folded across three names.
// Retail independently shows a thiscall method taking two stack dwords and
// storing them at this+0x28 and this+0x2C. The extent is bounded by the int3
// run at 0x00664E9B..0x00664E9F and the int3 at 0x00664EB1, with ret 8 at the
// end of the body.

class Rva00664EA0
{
	unsigned char m_prefix[0x28];
	unsigned int m_word28;
	unsigned int m_word2C;

public:
	void rva00664EA0(unsigned int first, unsigned int second);
};

void Rva00664EA0::rva00664EA0(unsigned int first, unsigned int second)
{
	m_word28 = first;
	m_word2C = second;
}
