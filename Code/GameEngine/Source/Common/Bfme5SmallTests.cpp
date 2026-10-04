// Four more small ones (trimmed to the placed push body; the other three are
// declared-only here).

class Gen_0015A260
{
public:
	void bfmePush(int value);

private:
	int m_bfmeCount;					// +0x00
	int m_bfmeItems[6];					// +0x04
};

// ?bfmePush@Gen_0015A260@@QAEXH@Z
void Gen_0015A260::bfmePush(int value)
{
	int count = m_bfmeCount;

	if (count < 6)
	{
		m_bfmeItems[count] = value;

		++m_bfmeCount;
	}
}

class Gen_0015E750
{
public:
	bool bfmeIsAlone(void) const;
};

class Gen_001604C0
{
public:
	unsigned char bfmeHasRoom(void) const;
};

void __cdecl bfmeMarkDirty(int bits);

// Native 222435/11 and its adjacent 222440/13 use the same 32-bit storage.
// The preceding body ends with ret4 at222432; these leaves end at22243F and
// 22244C, immediately before the next Ghidra start22244D. Original function
// and global names are unknown. The unsigned words preserve only their bits.
// VA E02FC0 is in .data's loader-zero tail: section RVA9A4000, relative5EFC0
// exceeds raw_size3A008. This is its actual zero-initialized storage provider.
unsigned int g_rva00E02FC0Bits = 0;

// Semantic lead: complete BFME1 Bfme5SmallTests.cpp blob1b4b62701b06e1ef5ea774e495711a32f8a688c8
// at5cc75ddda6455c338a5068307e587a793f96d6b3, compiled /O1 /Ob1. Its dirty
// label is donor evidence only. Keep the existing push body's compiler flags.
#pragma optimize("s", on)
void __cdecl rva00222435(unsigned int bits)
{
    g_rva00E02FC0Bits |= bits;
}

// The native adjacent leaf complements its stack word, then ANDs this same
// storage; no original enum, registration, or caller identity is asserted.
void __cdecl rva00222440(unsigned int bits)
{
    g_rva00E02FC0Bits &= ~bits;
}
#pragma optimize("", on)

// Whole donor ConditionalPointerStoreThunk.cpp at5cc75ddda6455c338a5068307e587a793f96d6b3
// emitted this sole new body under O1/Ob1. Native Ghidra133E/34 ends with
// ret8 at135D, so1360 follows at a true boundary; next Ghidra1368 follows
// its own ret at1367. Only the read/zero word at+8 is established. Native
// return use, original owner, pointee type, and complete layout are unknown.
struct Rva00001360Bits
{
    unsigned int m_unobserved00[2];
    unsigned int m_bits08;
    unsigned int takeBits();
};
#pragma optimize("s", on)
unsigned int Rva00001360Bits::takeBits()
{
    unsigned int result = m_bits08;
    m_bits08 = 0;
    return result;
}
#pragma optimize("", on)

// Primary semantic lead: whole BFME1 Dict_getAsciiString.cpp at5cc75ddda6455c338a5068307e587a793f96d6b3
// under O1/Ob1 emitted DictPair::getTypeFromKey. Native306B19/108 ends
// ret8 at306B82; this leaf306B85/10 ends ret306B8E before another distinct
// stack-word shift leaf306B8F. The bits and cdecl ABI are target facts;
// donor Dict names, key enum, and DataType identity remain unproven here.
#pragma optimize("s", on)
unsigned int __cdecl rva00306B85(unsigned int bits)
{
    return bits & 0xff;
}
#pragma optimize("", on)
