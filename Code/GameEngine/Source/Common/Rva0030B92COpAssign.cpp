// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??4Rva0030B92C@@QAEAAU0@ABU0@@Z @0x0030B92C 63B
// operator= via rowed vector Pod8 0x001D9BEE then byte 0x24 gate then 24B at 0x0C.
// Evidence: calls rowed Pod8 vector op=; cmp [ebx+0x24]; callers 0x00330B59; unblocks 0x00330B50.
#include <vector>
struct BfmePod8 { int a[2]; };
struct Mid16 { int a[4]; };
struct Rva0030B92C
{
	_STL::vector<BfmePod8, _STL::allocator<BfmePod8> > m_vec;
	Mid16 m_mid;
	int m_1c;
	int m_20;
	unsigned char m_24;
	Rva0030B92C &operator=(const Rva0030B92C &o);
};
Rva0030B92C &Rva0030B92C::operator=(const Rva0030B92C &o)
{
	if (this != &o) {
		m_vec = o.m_vec;
		m_24 = o.m_24;
		if (o.m_24 == 0) {
			m_mid = o.m_mid;
			m_1c = o.m_1c;
			m_20 = o.m_20;
		}
	}
	return *this;
}
