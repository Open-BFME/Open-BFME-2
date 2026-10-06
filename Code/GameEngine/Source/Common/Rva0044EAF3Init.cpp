// cl: /DNDEBUG /MD
// ?rva0044EAF3@Rva0044EAF3@@QAEPAV1@HIII@Z @0x0044EAF3 88B
// Bitfield init with memset 0x10 plus three bit sets; returns this.
// Evidence: unlock lane; callee memset import 0x006291AE rowed; callers at
// 0x004502F9 0x004BFFC8; prev Rva0044E6AEVirtForward and next Rva0044ECCE;
// shape mirrors matched Rva001E4912Init (memset plus bit sets returning this).
#pragma function(memset)
extern "C" void *memset(void *dst, int value, unsigned int size);

class Rva0044EAF3
{
public:
	Rva0044EAF3 *rva0044EAF3(int a, unsigned int b, unsigned int c, unsigned int d);
	unsigned m_bits[4];
};

Rva0044EAF3 *Rva0044EAF3::rva0044EAF3(int a, unsigned int b, unsigned int c, unsigned int d)
{
	memset(this, 0, 0x10);
	m_bits[b >> 5] |= 1u << (b & 31);
	m_bits[c >> 5] |= 1u << (c & 31);
	m_bits[d >> 5] |= 1u << (d & 31);
	return this;
}
