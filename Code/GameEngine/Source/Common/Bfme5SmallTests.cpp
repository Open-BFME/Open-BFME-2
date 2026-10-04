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

// The shipped VS2003 WinBase.h declares VOID WINAPI LeaveCriticalSection
// (LPCRITICAL_SECTION). This opaque tag preserves that actual import ABI
// without claiming any CRITICAL_SECTION fields or receiver lifetime.
struct _RTL_CRITICAL_SECTION;
extern "C" __declspec(dllimport) void __stdcall
LeaveCriticalSection(_RTL_CRITICAL_SECTION *section);

// Three whole BFME1 donor units at5cc75ddda6455c338a5068307e587a793f96d6b3
// place their differently named cleanup members at native Ghidra1DBA9B/9:
// Bfme/Glo00EF3330_h004893E0.cpp, Watchdog.cpp, GameResultsCounterDestructor.cpp.
// Their owner/lifetime labels remain donor facts. Native only pushes receiver
// word0 to the real LeaveCriticalSection IATBBA204 and returns. No virtual
// table, constructor, destructor, or original class identity is claimed.
struct Rva001DBA9BSectionView
{
    _RTL_CRITICAL_SECTION *m_section00;
    void leave();
};
#pragma optimize("s", on)
void Rva001DBA9BSectionView::leave()
{
    LeaveCriticalSection(m_section00);
}
#pragma optimize("", on)

// Whole BFME1 SmallLeafBodies.cpp at5cc75ddda6455c338a5068307e587a793f96d6b3
// compiled O1/Ob1 supplies the same byte-store pattern at two offsets.
// Target45311A/10 follows the prior ret453119 and ends ret4 at453121 before
// Ghidra453124; target330CD3/10 follows Ghidra330CC2/17's ret4 at330CD0
// and ends ret4 at330CDA before Ghidra330CDD. Each native body independently
// proves its offset and low-eight stack bits. Owner, purpose, padding types,
// original signedness, and complete class size remain unknown.
class Rva0045311AByteView
{
public:
    unsigned char m_unobserved00[0x32];
    unsigned char m_bits32;
    void setBits(unsigned char bits);
};
class Rva00330CD3ByteView
{
public:
    unsigned char m_unobserved00[0x64];
    unsigned char m_bits64;
    void setBits(unsigned char bits);
};
#pragma optimize("s", on)
void Rva0045311AByteView::setBits(unsigned char bits)
{
    m_bits32 = bits;
}
void Rva00330CD3ByteView::setBits(unsigned char bits)
{
    m_bits64 = bits;
}
#pragma optimize("", on)

// The same whole SmallLeafBodies donor labels this shape a constructor.
// Target preceding Ghidra360BB8/70 endsret360BFD, this body360BFE/8 ends
// ret4 at360C03, and the distinct next body begins360C06. Native stores all
// one bits to receiverword0, returns the receiver inEAX, and ignores one
// cleanup word. No target lifetime evidence establishes a constructor or
// argument type; use a plain address-qualified raw-word reset ABI view.
class Rva00360BFEWordView
{
public:
    unsigned int m_bits00;
    Rva00360BFEWordView *resetBits(unsigned int ignored);
};
#pragma optimize("s", on)
Rva00360BFEWordView *Rva00360BFEWordView::resetBits(unsigned int)
{
    m_bits00 = ~0u;
    return this;
}
#pragma optimize("", on)

// Primary semantic lead: complete BFME1 PackedByteExtractThunk.cpp
// at5cc75ddda6455c338a5068307e587a793f96d6b3 (no header dependencies),
// compiled O1/Ob1. Target established GdiplusStartupInput115D/32 ends
// ret12 at117A. Three distinct cdecl leaves follow:117D/6 returns stack
// bits8..15,1183/11 returns bit16,118E/11 returns bit18; their own returns
// are at1182/118D/1198, before the next distinct body1199. Native behavior,
// 32-bit stack words and boundaries are facts; donor names and the original
// bitfield owner/type are not. Byte access spells the proven x86 object
// representation without assigning a target structure or semantic flag name.
#pragma optimize("s", on)
unsigned long rva0000117D(unsigned long bits)
{
    return reinterpret_cast<const unsigned char *>(&bits)[1];
}
unsigned long rva00001183(unsigned long bits)
{
    return (bits >> 16) & 1;
}
unsigned long rva0000118E(unsigned long bits)
{
    return (bits >> 18) & 1;
}
#pragma optimize("", on)
