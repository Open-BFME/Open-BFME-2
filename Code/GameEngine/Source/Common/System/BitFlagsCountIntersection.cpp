// cl: /O1 /DNDEBUG /MD
//
// BitFlags<11> intersection popcounts. Retail is the dword SWAR fold, not
// std::bitset::count. Dedicated TU so SparseMatchFinder cannot inline these.

template <int NUMBITS>
class BitFlags
{
	unsigned m_bits;

public:
	int countIntersection(const BitFlags &that) const;
	int countInverseIntersection(const BitFlags &that) const;
};

template <int NUMBITS>
int BitFlags<NUMBITS>::countIntersection(const BitFlags &that) const
{
	unsigned v = that.m_bits & m_bits;
	v = v - ((v >> 1) & 0x55555555);
	v = (v & 0x33333333) + ((v >> 2) & 0x33333333);
	v = (v + (v >> 4)) & 0x0F0F0F0F;
	return (int)((v * 0x01010101u) >> 24);
}

template <int NUMBITS>
int BitFlags<NUMBITS>::countInverseIntersection(const BitFlags &that) const
{
	unsigned v = (~m_bits) & that.m_bits;
	v = v - ((v >> 1) & 0x55555555);
	v = (v & 0x33333333) + ((v >> 2) & 0x33333333);
	v = (v + (v >> 4)) & 0x0F0F0F0F;
	return (int)((v * 0x01010101u) >> 24);
}

template class BitFlags<11>;
