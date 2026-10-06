// cl: /DNDEBUG /MD
//
// ??0Rva0028F633@@QAE@HH@Z -- retail 0x0028F633, 47 bytes.
// Fixed 128-byte (1024-bit) bitset two-argument constructor: zeroes the whole
// object with memset through the CRT memset import thunk at 0x6291AE and
// sets a single bit. Retail reads only the second parameter; the first is
// never read. Twin of the landed Rva0028F59A ctor at 0x0028F59A (44B with
// 0x4C bytes); the 3 extra bytes are the 5-byte push of 0x80 versus the
// 2-byte push of 0x4C. Plain-extern memset keeps the E8-to-thunk shape.

extern "C" void *memset(void *dst, int val, unsigned size);

struct Rva0028F633
{
	unsigned m_bits[32];

	Rva0028F633(int unused, int bit);
};

Rva0028F633::Rva0028F633(int /*unused*/, int bit)
{
	memset(this, 0, 0x80);
	m_bits[(unsigned)bit >> 5] |= 1u << (bit & 31);
}
