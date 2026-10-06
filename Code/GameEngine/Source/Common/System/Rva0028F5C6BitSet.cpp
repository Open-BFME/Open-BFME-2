// cl: /DNDEBUG /MD
// ??0Rva0028F5C6@@QAE@HHHHH@Z @ 0x0028F5C6 109B: fixed 76-byte (19-dword)
// bitset five-argument constructor, twin of Rva0028F59A at 0x0028F59A (44B,
// 0x4C bytes, one bit) and Rva0028F633 at 0x0028F633. Zeroes the object via
// CRT memset import thunk 0x006291AE then sets four bits; first parameter
// never read. Callers at 0x0028FE3E and 0x004A4996. Prev/next same dir.
extern "C" void *memset(void *dst, int val, unsigned size);

struct Rva0028F5C6
{
	unsigned m_bits[19];

	Rva0028F5C6(int unused, int b1, int b2, int b3, int b4);
};

Rva0028F5C6::Rva0028F5C6(int /*unused*/, int b1, int b2, int b3, int b4)
{
	memset(this, 0, 0x4C);
	m_bits[(unsigned)b1 >> 5] |= 1u << (b1 & 31);
	m_bits[(unsigned)b2 >> 5] |= 1u << (b2 & 31);
	m_bits[(unsigned)b3 >> 5] |= 1u << (b3 & 31);
	m_bits[(unsigned)b4 >> 5] |= 1u << (b4 & 31);
}
