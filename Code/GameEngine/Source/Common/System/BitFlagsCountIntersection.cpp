// cl: /DNDEBUG /MD
//
// BitFlags<11> intersection popcounts. Retail is the dword SWAR fold, not
// std::bitset::count. Dedicated TU so SparseMatchFinder cannot inline these.

#include "../../../Include/Common/BitFlagsTemplate.h"

// These generic definitions read word 0 only. That matches retail's two bodies
// (0x0033ADC0, 0x0028F55C) for N = 11, the one instantiation below. Any N above
// 32 would undercount, so do not instantiate them for a larger set.
template <int NUMBITS>
int BitFlags<NUMBITS>::countIntersection(const BitFlags &that) const
{
	unsigned v = that.m_bits[0] & m_bits[0];
	v = v - ((v >> 1) & 0x55555555);
	v = (v & 0x33333333) + ((v >> 2) & 0x33333333);
	v = (v + (v >> 4)) & 0x0F0F0F0F;
	return (int)((v * 0x01010101u) >> 24);
}

template <int NUMBITS>
int BitFlags<NUMBITS>::countInverseIntersection(const BitFlags &that) const
{
	unsigned v = (~m_bits[0]) & that.m_bits[0];
	v = v - ((v >> 1) & 0x55555555);
	v = (v & 0x33333333) + ((v >> 2) & 0x33333333);
	v = (v + (v >> 4)) & 0x0F0F0F0F;
	return (int)((v * 0x01010101u) >> 24);
}

template int BitFlags<11>::countIntersection(const BitFlags<11> &) const;
template int BitFlags<11>::countInverseIntersection(const BitFlags<11> &) const;
