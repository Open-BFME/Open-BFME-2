// cl: /MD
//
// ??0Rva0045D887@@QAE@HHHHHH@Z @ 0x0045D887 (129B): 16-byte bitset ctor.
// memset(this 0 0x10) then sets five bits. First param unread at all call
// sites (caller 0x0045E293 passes 0 0x1F 0x20 0x21 0x22 0x23). Shape follows
// Rva00045411BitSet 2-arg ctor precedent. Unsigned shift gives shr.
extern "C" void *memset(void *dst, int val, unsigned size);

struct Rva0045D887
{
	unsigned m_bits[4];

	Rva0045D887(int unused, int b1, int b2, int b3, int b4, int b5);
};

Rva0045D887::Rva0045D887(int /*unused*/, int b1, int b2, int b3, int b4, int b5)
{
	memset(this, 0, 0x10);
	m_bits[(unsigned)b1 >> 5] |= 1u << (b1 & 31);
	m_bits[(unsigned)b2 >> 5] |= 1u << (b2 & 31);
	m_bits[(unsigned)b3 >> 5] |= 1u << (b3 & 31);
	m_bits[(unsigned)b4 >> 5] |= 1u << (b4 & 31);
	m_bits[(unsigned)b5 >> 5] |= 1u << (b5 & 31);
}
