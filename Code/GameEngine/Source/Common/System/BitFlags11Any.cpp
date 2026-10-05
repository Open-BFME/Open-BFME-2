// cl: /O1 /DNDEBUG /MD
//
// ?any@?$BitFlags@$0L@@@QBE_NXZ @0x0023C58B, 20B.
// BitFlags<11>::any() (DisabledMaskType::any). Retail loops one dword and
// returns true when the word is non-zero, false otherwise.
// Evidence: callers pass Object+0x1C8 (the disabled mask): 0x0027532F
// lea esi,[eax+0x1C8], 0x005891A3 add ecx,0x1C8, 0x00245ACB lea ecx,[eax+0x1C8].
// Donor: ZH BitFlags::any() via bitset plus BFME2 BitFlags<11> one-word layout
// (BitFlags11DisabilityCtors.cpp proves DISABLED_COUNT 11). Sibling shape:
// BitFlags69Test.cpp test() over seven words; this is the one-word any().

template <int N>
class BitFlags
{
public:
	bool any() const;
	unsigned int m_words[(N + 31) / 32];
};

// VA 0x00E030CC: memset clear by the dynamic initializer at 0x007B00F1;
// read (DIR32) by the rowed UpdateModule::getDisabledTypesToProcess.
BitFlags<11> DISABLEDMASK_NONE = { { 0 } };
// VA 0x00E030D0: memset clear at 0x007B0103; the rowed 0x00419CC8 sets every
// bit at runtime; read (DIR32) by the rowed Rva004DF396 override.
BitFlags<11> DISABLEDMASK_ALL = { { 0 } };

template <>
bool BitFlags<11>::any() const
{
	const unsigned *mine = m_words;
	for (unsigned i = 0; i < 1; i++) {
		if (mine[i] != 0)
			return true;
	}
	return false;
}

namespace _STL
{
template<class _Dummy>
class _Bs_G
{
public:
	static unsigned char _S_bit_count[256];
	static unsigned char _S_first_one[256];
};

// placement unverified: no rowed DIR32 site yet; values copied from vendored STLport _bitset.c.
template<>
unsigned char _Bs_G<bool>::_S_bit_count[256] = {
	0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4,
	1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
	1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
	2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
	1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
	2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
	2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
	3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
	1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
	2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
	2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
	3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
	2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
	3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
	3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
	4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8
};
}
