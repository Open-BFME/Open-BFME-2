// cl: /O1 /DNDEBUG /MD
//
// ?countInverseIntersection@?$BitFlags@$0HF@@@QBEHABV1@@Z @0x0033AE53 89B
// BitFlags<117> (ModelConditionSetFlags) inverse-intersection popcount over
// four dwords. Evidence: pinned caller findBestInfoSlow for
// SparseMatchFinder<UModelConditionInfo, BitFlags<$0HF>> at 0x0033BDF8 calls
// this (second call, tie-break) next to countIntersection at 0x0033ADFC;
// retail computes (~mine & theirs) SWAR popcount summed over 4 words.

template <int NUMBITS>
class BitFlags
{
public:
	int countInverseIntersection(const BitFlags &that) const;
	int countIntersection(const BitFlags &that) const;

private:
	unsigned m_words[4];
};

template <>
inline int BitFlags<117>::countInverseIntersection(const BitFlags &that) const
{
	int total = 0;
	const unsigned *mine = m_words;
	const unsigned *theirs = that.m_words;
	for (unsigned i = 0; i < 4; i++) {
		unsigned v = (~mine[i]) & theirs[i];
		v = v - ((v >> 1) & 0x55555555);
		v = (v & 0x33333333) + ((v >> 2) & 0x33333333);
		v = (v + (v >> 4)) & 0x0F0F0F0F;
		total += (int)((v * 0x01010101u) >> 24);
	}
	return total;
}
// Target 0033ADFC..0033AE53: four-word mine/theirs intersection.
// The separate mask temporaries follow verified SWAR sibling 00046827.
template <>
int BitFlags<117>::countIntersection(const BitFlags &that) const
{
    int total = 0;
    const unsigned *mine = m_words;
    const unsigned *theirs = that.m_words;
    for (unsigned i = 0; i < 4; ++i) {
        unsigned v = theirs[i] & mine[i];
        v = v - ((v >> 1) & 0x55555555);
        unsigned orig = v;
        unsigned low = orig & 0x33333333;
        unsigned high = (orig >> 2) & 0x33333333;
        v = high + low;
        v = ((v >> 4) + v) & 0x0F0F0F0F;
        v = (v * 0x01010101) >> 24;
        total += (int)v;
    }
    return total;
}

#pragma inline_depth(0)
// ?bfmeEmitBitFlags117CountInverseIntersection@@YAXPAV?$BitFlags@$0HF@@@@Z present-unmatched
void bfmeEmitBitFlags117CountInverseIntersection(BitFlags<117> *p)
{
	p->countInverseIntersection(*(BitFlags<117> *)0);
}
#pragma inline_depth()
