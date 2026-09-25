// cl: /O1 /DNDEBUG /MD
//
// ?test@?$BitFlags@$0EF@@@QBE_NPBX@Z @0x002615C0
// KindOf-mask intersection over seven dwords, called by the rowed
// Thing::isAnyKindOf in ThingIsAnyKindOf.cpp (which must stay on the
// base flags, so this body lives here). The 69-bit instantiation still
// walks seven words in retail; the bound is retail's, not (69+31)/32.
// Unsigned loop index: retail keeps the top-tested loop with jb, which
// signed int lowers as jl.

template <int N>
class BitFlags
{
public:
	bool test(const void *other) const;

private:
	unsigned m_words[7];
};

// ?test@?$BitFlags@$0EF@@@QBE_NPBX@Z
template <>
bool BitFlags<69>::test(const void *other) const
{
	const unsigned *mine = m_words;
	const unsigned *theirs = (const unsigned *)other;
	for (unsigned i = 0; i < 7; i++) {
		if (mine[i] & theirs[i])
			return true;
	}
	return false;
}
