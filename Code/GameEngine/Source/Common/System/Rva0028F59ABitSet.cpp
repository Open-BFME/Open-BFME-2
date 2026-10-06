// cl: /DNDEBUG /MD
//
// ??0Rva0028F59A@@QAE@HH@Z -- retail 0x0028F59A, 44 bytes.
// Fixed 76-byte (608-bit) bitset two-argument constructor: zeroes the whole
// object with memset through the CRT memset import thunk at 0x6291AE and
// sets a single bit. Retail reads only the second parameter (callers push 0
// first: 0x45 at 0x00298540 and variable bit at 0x0044EE62); the first is
// never read. Shape matches the landed one-bit Rva00045411BitSet at
// 0x00045411 (44B, 0x1C bytes) with 19 dwords instead of 7. Stack temporaries
// of 0x4C bytes constructed via lea ecx at both callers prove the size.
// Plain-extern memset keeps the retail E8-to-thunk call shape.

extern "C" void *memset(void *dst, int val, unsigned size);

struct Rva0028F59A
{
	unsigned m_bits[19];

	Rva0028F59A(int unused, int bit);
};

Rva0028F59A::Rva0028F59A(int /*unused*/, int bit)
{
	memset(this, 0, 0x4C);
	m_bits[(unsigned)bit >> 5] |= 1u << (bit & 31);
}
