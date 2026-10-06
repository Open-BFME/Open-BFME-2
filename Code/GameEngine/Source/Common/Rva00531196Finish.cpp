// cl: /MD
// ?rva00531196@Rva00531196@@QAEXPAI@Z @ 0x00531196 (159B): __thiscall.
// Zeroes 4 bytes then inserts seven bit-fields of m_val from the packed dword
// p[3]: masks 7, 0x1f8, 0x7e00, 0x8000, 0x10000, 0x60000, 0x80000 taken from
// p[3]>>0, >>1, >>1, and byte extractions at >>17/>>18/>>22. Each field uses
// the (m_val & ~mask) | (value & mask) insert idiom, which MSVC 7.1 lowers to
// the xor-into-memory form at retail. Caller 0x005329C8; owner unknown, so an
// honest address-derived name.
extern "C" void __cdecl memset(void *, int, unsigned int);
class Rva00531196
{
public:
	void rva00531196(unsigned int *p);
	unsigned int m_val;
};
void Rva00531196::rva00531196(unsigned int *p)
{
	memset((void *)this, 0, 4);
	m_val = (m_val & ~7u) | (p[3] & 7u);
	m_val = (m_val & ~0x1f8u) | ((p[3] >> 1) & 0x1f8u);
	m_val = (m_val & ~0x7e00u) | ((p[3] >> 1) & 0x7e00u);
	unsigned char c1 = (unsigned char)(p[3] >> 17);
	m_val = (m_val & ~0x8000u) | ((c1 << 15) & 0x8000u);
	unsigned char c2 = (unsigned char)(p[3] >> 18);
	m_val = (m_val & ~0x10000u) | ((c2 << 16) & 0x10000u);
	m_val = (m_val & ~0x60000u) | ((p[3] >> 2) & 0x60000u);
	unsigned char c3 = (unsigned char)(p[3] >> 22);
	m_val = (m_val & ~0x80000u) | ((c3 << 19) & 0x80000u);
}
