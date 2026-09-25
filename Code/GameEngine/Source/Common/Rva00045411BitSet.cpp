// cl: /O1 /MD /DNDEBUG
//
// Fixed 28-byte (224-bit) bitset. The two-argument constructor zeroes the
// whole object with memset and then sets a single bit; retail reads only the
// second parameter (all bit indices witnessed at call sites are below 224)
// while the first is never read (callers pass 0 or an ignored value).
// Plain-extern memset keeps the retail E8-to-thunk call shape.

extern "C" void *memset(void *dst, int val, unsigned size);

struct Rva00045411BitSet
{
	unsigned m_bits[7];

	Rva00045411BitSet(int unused, int bit);
};

// ??0Rva00045411BitSet@@QAE@HH@Z -- retail 0x00045411, 44 bytes.
// Called from GarrisonContainModuleData ctor 0x47978F (bit 8) and ten other
// sites; retail shr (unsigned index) not sar.
Rva00045411BitSet::Rva00045411BitSet(int /*unused*/, int bit)
{
	memset(this, 0, 0x1C);
	m_bits[(unsigned)bit >> 5] |= 1u << (bit & 31);
}
