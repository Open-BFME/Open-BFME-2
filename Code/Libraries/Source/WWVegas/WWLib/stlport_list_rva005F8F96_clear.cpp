// cl: /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?clear@?$_List_base@URva005F8F96@@V?$allocator@URva005F8F96@@@_STL@@@_STL@@QAEXXZ, retail 0x005CCEFA, 49 bytes.
// List_base clear for 8-byte Rva005F8F96 holder via rowed dtor 0x005F8F96 and _free 0x30830.
// Same 49B shape as TreeHintOpaque list clear; value at node+8 proves list node layout.
// Chain from rowed dtor; unblocks List_base dtor 0x005CD032.
#include <list>
struct TargetRef00217D4C { virtual void *destroy(unsigned int flags); int references; };
struct Rva005F8F96
{
	~Rva005F8F96();
	TargetRef00217D4C *m_00;
	int m_04;
};
inline bool operator==(const Rva005F8F96 &x, const Rva005F8F96 &y) { return x.m_04 == y.m_04; }
inline bool operator<(const Rva005F8F96 &x, const Rva005F8F96 &y) { return x.m_04 < y.m_04; }
template class _STL::list<Rva005F8F96, _STL::allocator<Rva005F8F96> >;
