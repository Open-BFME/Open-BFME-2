// cl: /Ireference/shims/bfmelist /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?Rva002AAC9EEqual@@YAHPBURva002AAC9ERange@@0@Z @0x002AAC9E 61B: float-range equal via size xor plus Rva002AA32FEqual; caller 0x002ADC03 pushes 2 ptrs; unblocks 0x002ADC03.
struct Rva002AAC9ERange
{
	float const* m_begin;
	float const* m_end;
};

bool __cdecl Rva002AA32FEqual(float const* first, float const* last, float const* other);

int __cdecl Rva002AAC9EEqual(Rva002AAC9ERange const* a, Rva002AAC9ERange const* b)
{
	int aSize = (char const*)a->m_end - (char const*)a->m_begin;
	int bSize = (char const*)b->m_end - (char const*)b->m_begin;
	if ((((aSize ^ bSize) & -4) == 0) && Rva002AA32FEqual(a->m_begin, a->m_end, b->m_begin))
		return 1;
	return 0;
}
