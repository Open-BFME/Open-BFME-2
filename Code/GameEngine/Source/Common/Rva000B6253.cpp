// cl: /MD
// ?rva000B6253@Rva000B6253@@QAEPAV1@HIIIII@Z @0x000B6253 129B memset 0x4c plus five bit sets.
// First arg ignored (callers pass 0) then five ids set via m_bits[id>>5] |= 1u<<(id&31). Returns this.
// Evidence: caller 0x002C8B9B pushes 0 0x90 0x91 0x92 0x93 0x94 via local 0x4c buffer.
// Siblings Rva001E4912Init plus Rva00265254Ctor same 0x4c family same callee 0x006291AE.
// Unblocks 7 free functions. Prev 0x000B49C5 Next 0x000B6371.
void *__cdecl ji_006291ae(void *dest, int val, unsigned int count);
#pragma comment(linker, "/alternatename:?ji_006291ae@@YAPAXPAXHI@Z=?ji_006291ae@@YAXXZ")

class Rva000B6253
{
public:
	Rva000B6253 *rva000B6253(int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e, unsigned int f);
	unsigned m_bits[19];
};

Rva000B6253 *Rva000B6253::rva000B6253(int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e, unsigned int f)
{
	ji_006291ae(this, 0, 0x4c);
	m_bits[b >> 5] |= 1u << (b & 31);
	m_bits[c >> 5] |= 1u << (c & 31);
	m_bits[d >> 5] |= 1u << (d & 31);
	m_bits[e >> 5] |= 1u << (e & 31);
	m_bits[f >> 5] |= 1u << (f & 31);
	return this;
}
