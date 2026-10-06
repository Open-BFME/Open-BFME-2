// cl: /DNDEBUG /MD
// ?rva0044E9C7@Rva0044E9C7@@QAEPAV1@HIIIIIIIIIIIIII@Z @0x0044E9C7 300B
// Bitfield init with memset 0x4c plus fourteen bit sets; returns this.
// Evidence: unlock lane; caller at 0x0044EE41 in 0x0044EE07 pushes fifteen
// values with this in ecx; shape mirrors matched Rva0044EAF3Init (memset
// plus bit sets returning this); first stack arg unused as in precedent.
#pragma function(memset)
extern "C" void *memset(void *dst, int value, unsigned int size);

class Rva0044E9C7
{
public:
	Rva0044E9C7 *rva0044E9C7(int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e, unsigned int f, unsigned int g, unsigned int h, unsigned int i, unsigned int j, unsigned int k, unsigned int l, unsigned int m, unsigned int n, unsigned int o);
	unsigned int m_bits[19];
};

Rva0044E9C7 *Rva0044E9C7::rva0044E9C7(int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e, unsigned int f, unsigned int g, unsigned int h, unsigned int i, unsigned int j, unsigned int k, unsigned int l, unsigned int m, unsigned int n, unsigned int o)
{
	(void)a;
	memset(this, 0, 0x4c);
	m_bits[b >> 5] |= 1u << (b & 31);
	m_bits[c >> 5] |= 1u << (c & 31);
	m_bits[d >> 5] |= 1u << (d & 31);
	m_bits[e >> 5] |= 1u << (e & 31);
	m_bits[f >> 5] |= 1u << (f & 31);
	m_bits[g >> 5] |= 1u << (g & 31);
	m_bits[h >> 5] |= 1u << (h & 31);
	m_bits[i >> 5] |= 1u << (i & 31);
	m_bits[j >> 5] |= 1u << (j & 31);
	m_bits[k >> 5] |= 1u << (k & 31);
	m_bits[l >> 5] |= 1u << (l & 31);
	m_bits[m >> 5] |= 1u << (m & 31);
	m_bits[n >> 5] |= 1u << (n & 31);
	m_bits[o >> 5] |= 1u << (o & 31);
	return this;
}
