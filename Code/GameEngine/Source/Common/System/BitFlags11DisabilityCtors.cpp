// cl: /O1 /DNDEBUG /MD
// DisabledMaskType is BitFlags<11> (BFME DISABLED_COUNT is 11: the shim at
// reference/shims/bfmeobject/GameLogic/Object.h documents the 0xb
// range-check; BitFlags11DisabilityGetSingleBitFromName.cpp already rows
// the BitFlags<11> name lookup). MAKE_DISABLED_MASK(k) builds
// DisabledMaskType(kInit, k), so the single-index constructor below is the
// callee retail invokes as `lea ecx,[tmp]; push HELD(3); push kInit(0);
// call` in ProductionUpdateModuleData's constructor (0x0049F853) and as the
// per-global dynamic initializers at 0x007B496B+ (bits 0..3 at 0xE0660C+).
// The class is one 32-bit word: callers space instances 4 bytes apart and
// the body memsets exactly 4 bytes, then sets bit (idx & 31) of word
// (idx >> 5) with unsigned shifts.

typedef int Int;
typedef unsigned int UnsignedInt;

extern "C" void *memset(void *dst, int val, unsigned int n);

template <int NUM_BITS>
class BitFlags
{
public:
	enum BogusInitType
	{
		kInit = 0
	};

	BitFlags(BogusInitType init, Int bit);
	BitFlags(BogusInitType init, Int b0, Int b1, Int b2, Int b3);
	BitFlags();

private:
	UnsignedInt m_words[1];
};

template <int NUM_BITS>
BitFlags<NUM_BITS>::BitFlags(BogusInitType, Int bit)
{
	memset(m_words, 0, sizeof(m_words));
	m_words[(UnsignedInt)bit >> 5] |= (1u << (bit & 31));
}

template <int NUM_BITS>
BitFlags<NUM_BITS>::BitFlags(BogusInitType, Int b0, Int b1, Int b2, Int b3)
{
	memset(m_words, 0, sizeof(m_words));
	m_words[(UnsignedInt)b0 >> 5] |= (1u << (b0 & 31));
	m_words[(UnsignedInt)b1 >> 5] |= (1u << (b1 & 31));
	m_words[(UnsignedInt)b2 >> 5] |= (1u << (b2 & 31));
	m_words[(UnsignedInt)b3 >> 5] |= (1u << (b3 & 31));
}

template <int NUM_BITS>
BitFlags<NUM_BITS>::BitFlags()
{
	memset(m_words, 0, sizeof(m_words));
}

// ??0?$BitFlags@$0L@@@QAE@W4BogusInitType@0@H@Z
template BitFlags<11>::BitFlags(BitFlags<11>::BogusInitType, Int);

// ??0?$BitFlags@$0L@@@QAE@W4BogusInitType@0@HHHH@Z
template BitFlags<11>::BitFlags(BitFlags<11>::BogusInitType, Int, Int, Int, Int);

// ??0?$BitFlags@$0L@@@QAE@XZ
template BitFlags<11>::BitFlags();
