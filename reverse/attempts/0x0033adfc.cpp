// ?countIntersection@?$BitFlags@$0HF@@@QBEHABV1@@Z
// partial score=0.78 date=2026-10-07
// cl: /O1 /DNDEBUG /MD
// Native 0x0033ADFC..0x0033AE53, RET4. Named call from the matched
// ModelConditionInfo/BitFlags<117> findBestInfoSlow body establishes identity.
// Reuse the four-word view and flags of the matched inverse-intersection
// sibling; native performs SWAR counts on each mine/theirs intersection.
template <int NUMBITS>
class BitFlags
{
public:
    int countIntersection(const BitFlags &that) const;
private:
    unsigned m_words[4];
};

template <>
int BitFlags<117>::countIntersection(const BitFlags &that) const
{
    int total = 0;
    const unsigned *mine = m_words;
    const unsigned *theirs = that.m_words;
    for (unsigned i = 0; i < 4; ++i)
    {
        unsigned v = theirs[i] & mine[i];
        v -= (v >> 1) & 0x55555555;
        v = (v & 0x33333333) + ((v >> 2) & 0x33333333);
        v = (v + (v >> 4)) & 0x0F0F0F0F;
        total += (int)((v * 0x01010101) >> 24);
    }
    return total;
}
