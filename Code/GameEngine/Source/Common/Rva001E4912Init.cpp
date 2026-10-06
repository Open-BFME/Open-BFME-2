// cl: /MD
// ?rva001E4912@Rva001E4912@@QAEPAV1@HII@Z @0x001E4912 66B: memset 0x4c-bitfield init plus two bit sets.
// Evidence: 24 callers pushing (0 bit1 bit2) e.g. 0x001E5E7E (0 0x8a 0x86) 0x001E5E93 (0 0x89 0x85) 0x001E5FA5 (0 0xf0 0xef) 0x00275DBA (0 0x43 0x45); returns this.
#pragma function(memset)
extern "C" void *memset(void *dst, int value, unsigned int size);

class Rva001E4912
{
public:
	Rva001E4912 *rva001E4912(int a, unsigned int b, unsigned int c);
	unsigned m_bits[19];
};

Rva001E4912 *Rva001E4912::rva001E4912(int a, unsigned int b, unsigned int c)
{
	memset(this, 0, 0x4c);
	m_bits[b >> 5] |= 1u << (b & 31);
	m_bits[c >> 5] |= 1u << (c & 31);
	return this;
}
