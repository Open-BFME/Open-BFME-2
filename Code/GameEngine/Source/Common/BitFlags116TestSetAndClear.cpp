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
bool BitFlags<116>::testSetAndClear(const BitFlags &mustBeSet, const BitFlags &mustBeClear) const
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
