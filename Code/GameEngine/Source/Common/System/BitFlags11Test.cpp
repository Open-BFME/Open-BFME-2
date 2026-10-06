// cl: /DNDEBUG /MD
//
// ?test@?$BitFlags@$0L@@@QBE_NPBX@Z @0x0023C59F, 37B.
// BitFlags<11>::test – one-word overlap check for DisabledMask.
// Retail loops one dword with other-minus-this diff trick, testing
// this[i] & other[i] for non-zero, like the seven-word
// ?test@?$BitFlags@$0EF@@@QBE_NPBX@Z at 0x002615C0 (BitFlags69Test.cpp).
// Evidence: eight callers pass mask pairs (e.g. 0x00245AE5 pushes saved
// mask and calls on virtual-return mask); prev row is sibling
// ?any@?$BitFlags@$0L@@@QBE_NXZ at 0x0023C58B. Flags from that sibling.

template <int N>
class BitFlags
{
public:
	bool test(const void *other) const;

private:
	unsigned m_words[1];
};

template <>
bool BitFlags<11>::test(const void *other) const
{
	const unsigned *mine = m_words;
	const unsigned *theirs = (const unsigned *)other;
	for (unsigned i = 0; i < 1; i++) {
		if (mine[i] & theirs[i])
			return true;
	}
	return false;
}
