// cl: /O1 /DNDEBUG /MD
//
// ?testSetAndClear@?$BitFlags@$0HE@@@QBE_NABV1@0@Z @0x0030A146
// Seven-dword mustBeSet/mustBeClear test, donor
// BitFlags::testSetAndClear. Called by the rowed Thing::isKindOfMulti
// forwarder. Register-starved loop keeps its counter in [ebp-4], hence
// the framed shape.

template <int N>
class BitFlags
{
public:
	bool testSetAndClear(const BitFlags &mustBeSet, const BitFlags &mustBeClear) const;

private:
	unsigned m_words[7];
};

// ?testSetAndClear@?$BitFlags@$0HE@@@QBE_NABV1@0@Z
template <>
inline bool BitFlags<116>::testSetAndClear(const BitFlags &mustBeSet, const BitFlags &mustBeClear) const
{
	const unsigned *mine = m_words;
	const unsigned *set = mustBeSet.m_words;
	const unsigned *clear = mustBeClear.m_words;
	for (unsigned i = 0; i < 7; i++) {
		if (clear[i] & mine[i])
			return false;
		if ((set[i] & mine[i]) != set[i])
			return false;
	}
	return true;
}

// testSetAndClear is a header inline in retail: other units emit select-any
// copies, so a strong definition here was a duplicate in the linked build.
// This anchor makes this unit emit its copy for the ledger row. Its own body
// also compiles byte-identical to retail's 18-byte cdecl forwarder at
// 0x0030A8D1 (object pointer as the first stack argument), which is rowed
// under this placeholder name; that forwarder's real identity is unknown.
#pragma inline_depth(0)
void bfmeEmitBitFlags116TestSetAndClear(BitFlags<116> *p, const BitFlags<116> &a, const BitFlags<116> &b)
{
	p->testSetAndClear(a, b);
}
#pragma inline_depth()
