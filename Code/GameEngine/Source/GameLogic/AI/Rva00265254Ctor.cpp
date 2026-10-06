// cl: /DNDEBUG /MD
// ??0Rva00265254@@QAE@IIII@Z retail 0x00265254 88B.
// Unlock lane: memset 0x4c plus three bit sets; callers pass 0 plus three ids.
// Evidence: callers at 0x00265B39 0x002671F1 pass 0 0x7b-0x7d 0x151-0x153.
// ??0Rva00265254@@QAE@IIIIIIIII@Z retail 0x002652AC 186B.
// Unlock lane: memset 0x4c plus eight bit sets; first arg ignored like sibling.
// Evidence: callers at 0x00267E46 0x0044F0B3 pass 0 plus eight ids.
// ??0Rva00265254@@QAE@IIIIIIIIIIII@Z retail 0x00265366 243B.
// Leaf: memset 0x4c plus eleven bit sets; first arg ignored like siblings.

void *__cdecl ji_006291ae(void *dest, int val, unsigned int count);
#pragma comment(linker, "/alternatename:?ji_006291ae@@YAPAXPAXHI@Z=?ji_006291ae@@YAXXZ")

class Rva00265254
{
public:
	Rva00265254(unsigned int a1, unsigned int a2, unsigned int a3, unsigned int a4);
	Rva00265254(unsigned int a1, unsigned int a2, unsigned int a3, unsigned int a4, unsigned int a5, unsigned int a6, unsigned int a7, unsigned int a8, unsigned int a9);
	Rva00265254(unsigned int a1, unsigned int a2, unsigned int a3, unsigned int a4, unsigned int a5, unsigned int a6, unsigned int a7, unsigned int a8, unsigned int a9, unsigned int a10, unsigned int a11, unsigned int a12);
private:
	unsigned int m_bits[19];
};

Rva00265254::Rva00265254(unsigned int a1, unsigned int a2, unsigned int a3, unsigned int a4)
{
	ji_006291ae(this, 0, 0x4c);
	m_bits[a2 >> 5] |= 1u << (a2 & 31);
	m_bits[a3 >> 5] |= 1u << (a3 & 31);
	m_bits[a4 >> 5] |= 1u << (a4 & 31);
}

Rva00265254::Rva00265254(unsigned int a1, unsigned int a2, unsigned int a3, unsigned int a4, unsigned int a5, unsigned int a6, unsigned int a7, unsigned int a8, unsigned int a9)
{
	ji_006291ae(this, 0, 0x4c);
	m_bits[a2 >> 5] |= 1u << (a2 & 31);
	m_bits[a3 >> 5] |= 1u << (a3 & 31);
	m_bits[a4 >> 5] |= 1u << (a4 & 31);
	m_bits[a5 >> 5] |= 1u << (a5 & 31);
	m_bits[a6 >> 5] |= 1u << (a6 & 31);
	m_bits[a7 >> 5] |= 1u << (a7 & 31);
	m_bits[a8 >> 5] |= 1u << (a8 & 31);
	m_bits[a9 >> 5] |= 1u << (a9 & 31);
}

Rva00265254::Rva00265254(unsigned int a1, unsigned int a2, unsigned int a3, unsigned int a4, unsigned int a5, unsigned int a6, unsigned int a7, unsigned int a8, unsigned int a9, unsigned int a10, unsigned int a11, unsigned int a12)
{
	ji_006291ae(this, 0, 0x4c);
	m_bits[a2 >> 5] |= 1u << (a2 & 31);
	m_bits[a3 >> 5] |= 1u << (a3 & 31);
	m_bits[a4 >> 5] |= 1u << (a4 & 31);
	m_bits[a5 >> 5] |= 1u << (a5 & 31);
	m_bits[a6 >> 5] |= 1u << (a6 & 31);
	m_bits[a7 >> 5] |= 1u << (a7 & 31);
	m_bits[a8 >> 5] |= 1u << (a8 & 31);
	m_bits[a9 >> 5] |= 1u << (a9 & 31);
	m_bits[a10 >> 5] |= 1u << (a10 & 31);
	m_bits[a11 >> 5] |= 1u << (a11 & 31);
	m_bits[a12 >> 5] |= 1u << (a12 & 31);
}
