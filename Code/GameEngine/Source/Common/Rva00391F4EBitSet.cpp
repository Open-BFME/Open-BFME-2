// cl: /MD
//
// ??0Rva00391F4E@@QAE@HHH@Z 66B @0x00391F4E: fixed 16-byte (128-bit) bitset
// two-bit constructor: memsets this with 0 over 0x10 bytes through the CRT
// memset import thunk at 0x006291AE and sets two bits. Retail reads only the
// second and third parameters; the first is never read (kInit=0 BogusInitType
// sugar in BitFlags<N>, as in the landed Rva0006EE7A ctor at 0x0006EE7A).
// Shape matches that 66B two-bit ctor (/O1 /MD, plain-extern memset,
// E8-to-thunk) with 4 dwords instead of 7. Evidence: push 0x10/0/esi
// plus E8 to 0x6291AE, two (shr 5 / and 31 / shl / or) sequences, ret 0xC,
// callers at 0x003942CE 0x00451026 0x0045AB95 0x004833C1 0x004838E4 0x00489FAE
// 0x0048A32E. Plain-extern memset keeps the retail E8-to-thunk call shape.

extern "C" void *memset(void *dst, int val, unsigned size);

struct Rva00391F4E
{
	unsigned m_bits[4];

	Rva00391F4E(int unused, int b1, int b2);
};

// ??0Rva00391F4E@@QAE@HHH@Z
Rva00391F4E::Rva00391F4E(int /*unused*/, int b1, int b2)
{
	memset(this, 0, 0x10);
	m_bits[(unsigned)b1 >> 5] |= 1u << (b1 & 31);
	m_bits[(unsigned)b2 >> 5] |= 1u << (b2 & 31);
}
