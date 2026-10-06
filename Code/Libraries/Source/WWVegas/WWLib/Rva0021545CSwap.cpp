// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva0021545C@Rva0021545C@@QAEXPAV1@@Z @0x0021545C 29B swap first word plus E12 vector.
// Evidence: thiscall ret 4 with ecx read then written; dword exchange at +0
// plus rowed vector BfmeE12 swap 0x00567ECD at +4; callers 0x00215BB8 0x00215C17;
// prev/next share WWLib vector stlport flags.
#include <vector>
struct BfmeE12 { float x, y, z; };

class Rva0021545C
{
public:
	void rva0021545C(Rva0021545C *other);
private:
	void *m_00;
	_STL::vector<BfmeE12> m_04;
};

void Rva0021545C::rva0021545C(Rva0021545C *other)
{
	void *tmp = m_00;
	m_00 = other->m_00;
	other->m_00 = tmp;
	m_04.swap(other->m_04);
}
