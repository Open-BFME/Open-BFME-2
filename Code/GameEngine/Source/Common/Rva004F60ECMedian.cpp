// cl: /MD
// ?Rva004F60ECMedian@@YAPAURva004F6352@@PAU1@00@Z, retail 0x004F60EC, 62 bytes.
// Median-of-three for quicksort caller 0x004F95A8: returns median of a b c by key at +8 via double deref.
// Evidence: stride 0xC caller; loads [arg] then [+8]; integer compares; returns one arg; same shape as STL median.
struct MedianKey004F60EC
{
	int _00[2];
	int m_key;
};

struct Rva004F6352
{
	MedianKey004F60EC *m_ptr;
	int m_04;
	int m_08;
};

Rva004F6352 *Rva004F60ECMedian(Rva004F6352 *a, Rva004F6352 *b, Rva004F6352 *c)
{
	if (a->m_ptr->m_key > b->m_ptr->m_key)
	{
		if (b->m_ptr->m_key > c->m_ptr->m_key)
			return b;
		else if (a->m_ptr->m_key > c->m_ptr->m_key)
			return c;
		else
			return a;
	}
	else
	{
		if (a->m_ptr->m_key > c->m_ptr->m_key)
			return a;
		else if (b->m_ptr->m_key > c->m_ptr->m_key)
			return c;
		else
			return b;
	}
}
