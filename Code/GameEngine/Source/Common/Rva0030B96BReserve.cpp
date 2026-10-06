// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva0030B96B@Rva0030B96B@@QAEXH@Z, retail 0x0030B96B, 21 bytes.
// Holder ensure via rowed vector E8 reserve 0x0030B876 with clamp to 2.
// Evidence: caller 0x0030B9B4 with ecx this plus int arg; prev reserve same flags next clear same flags.
#include <vector>
struct BfmeE8 { int a[2]; };

struct Rva0030B96B
{
	void rva0030B96B(int n);
	_STL::vector<BfmeE8, _STL::allocator<BfmeE8> > m_vec;
};

void Rva0030B96B::rva0030B96B(int n)
{
	if (n < 2)
		n = 2;
	m_vec.reserve(n);
}
