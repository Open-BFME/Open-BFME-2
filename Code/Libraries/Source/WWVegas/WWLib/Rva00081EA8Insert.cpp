// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva00081EA8@Rva00081EA8@@QAEXPAURva001408C0Target@@@Z 0x00081EA8 25B: set-insert wrapper at +0x58; evidence caller 0x000D1108, callee rowed set::insert 0x00080691
#include <set>
struct Rva001408C0Target { int x; };
typedef _STL::set<Rva001408C0Target *, _STL::less<Rva001408C0Target *>, _STL::allocator<Rva001408C0Target *> > PtrSet001408C0;
class Rva00081EA8
{
public:
	void rva00081EA8(Rva001408C0Target *p);
private:
	char m_pad[0x58];
	PtrSet001408C0 m_set;
};
void Rva00081EA8::rva00081EA8(Rva001408C0Target *p)
{
	m_set.insert(p);
}
