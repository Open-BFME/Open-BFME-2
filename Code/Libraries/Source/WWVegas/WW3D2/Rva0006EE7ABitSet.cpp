// cl: /MD
//
// ??0Rva0006EE7A@@QAE@HHH@Z, retail 0x0006EE7A, 66 bytes. Fixed 28-byte
// (224-bit) bitset two-bit constructor: memsets this with 0 over 0x1C bytes
// through the CRT memset import thunk at 0x6291AE and sets two bits.
// Retail reads only the second and third parameters (all bit indices at the
// 23 call sites are below 224: e.g. 0x2F/0x59, 0x78/0xB5, 0x02/0x07); the
// first (kInit=0 BogusInitType sugar in BitFlags<N>) is never read.
// Shape matches the landed one-bit Rva00045411BitSet at 0x00045411 (44B)
// and the free four-bit body at 0x0006EEBC (109B). Callers pass the result
// to Thing::isAnyKindOf at 0x0030ADC7 and to the twin-memcpy ctor at
// 0x0004584D. Address-derived name stays honest pending a real BitFlags
// pin. Plain-extern memset keeps the retail E8-to-thunk call shape.

extern "C" void *memset(void *dst, int val, unsigned size);

struct Rva0006EE7A
{
	unsigned m_bits[7];

	Rva0006EE7A(int unused, int b1, int b2);
	Rva0006EE7A(int unused, int b1, int b2, int b3, int b4);
};

Rva0006EE7A::Rva0006EE7A(int /*unused*/, int b1, int b2)
{
	memset(this, 0, 0x1C);
	m_bits[(unsigned)b1 >> 5] |= 1u << (b1 & 31);
	m_bits[(unsigned)b2 >> 5] |= 1u << (b2 & 31);
}

Rva0006EE7A::Rva0006EE7A(int /*unused*/, int b1, int b2, int b3, int b4)
{
	memset(this, 0, 0x1C);
	m_bits[(unsigned)b1 >> 5] |= 1u << (b1 & 31);
	m_bits[(unsigned)b2 >> 5] |= 1u << (b2 & 31);
	m_bits[(unsigned)b3 >> 5] |= 1u << (b3 & 31);
	m_bits[(unsigned)b4 >> 5] |= 1u << (b4 & 31);
}
