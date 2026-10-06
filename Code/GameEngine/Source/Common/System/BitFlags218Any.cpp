// cl: /DNDEBUG /MD
//
// ?any@?$BitFlags@$0NK@@@QBE_NXZ @0x002C7501, 20B.
// BitFlags<218>::any() (KindOfMaskType::any). Retail loops seven dwords and
// returns true when any word is non-zero, false otherwise.
// Evidence: callers in 0x002C7D03 pass WeaponTemplateSet masks at +0xEC and
// +0x44 (slot*0x1C = 7 words) then call Thing::isAnyKindOf at 0x0030ADC7.
// Donor: ZH BitFlags::any() via bitset plus BFME2 KindOf 218-entry layout
// (KindOfGetSingleBitFromName.cpp proves BitFlags<218>, 0xDA names).
// Sibling shape: BitFlags11Any.cpp one-word any() at 0x0023C58B.

template <int N>
class BitFlags
{
public:
	bool any() const;

private:
	unsigned m_words[7];
};

template <>
bool BitFlags<218>::any() const
{
	const unsigned *mine = m_words;
	for (unsigned i = 0; i < 7; i++) {
		if (mine[i] != 0)
			return true;
	}
	return false;
}
