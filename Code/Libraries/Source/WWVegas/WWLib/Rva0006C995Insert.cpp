// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva0006C995@Rva0006C995@@QAEPAV1@PAURva001408C0Target@@@Z, retail 0x0006C995, 58 bytes.
// Unlock wrapper: null-check, convert via rowed bfmeGoEMEb 0x0061F600, set insert via rowed 0x00080691, flag at +0x10 on success, return this.
// Evidence: callers 0x0006D9B5 0x00081DB3 0x00081DEC 0x000C1B9A 0x000C1BB6 0x00104C11 0x0012CF2C show __thiscall 1 arg ret 4; set type from callee 0x00080691.
#include <set>
struct Rva001408C0Target { int x; };
typedef _STL::set<Rva001408C0Target *, _STL::less<Rva001408C0Target *>, _STL::allocator<Rva001408C0Target *> > PtrSet001408C0;
void *bfmeGoEMEb(void *item);
class Rva0006C995
{
public:
	Rva0006C995 *rva0006C995(Rva001408C0Target *p);
private:
	PtrSet001408C0 m_set;
	char m_pad0C[4];
	unsigned char m_flag;
};
Rva0006C995 *Rva0006C995::rva0006C995(Rva001408C0Target *p)
{
	if (p) {
		p = (Rva001408C0Target *)bfmeGoEMEb(p);
		if (m_set.insert(p).second)
			m_flag = 1;
	}
	return this;
}
