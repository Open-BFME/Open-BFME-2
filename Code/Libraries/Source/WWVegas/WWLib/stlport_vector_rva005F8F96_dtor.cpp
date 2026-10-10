// cl: /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1?$vector@URva005F8F96@@V?$allocator@URva005F8F96@@@_STL@@@_STL@@QAE@XZ, retail 0x001536EA, 63 bytes.
// ?_M_clear@?$vector@URva005F8F96@@V?$allocator@URva005F8F96@@@_STL@@@_STL@@IAEXXZ, retail 0x0015373C, 30 bytes.
// Vector<Rva005F8F96> dtor (EH) plus _M_clear via rowed _Destroy 0x00153470 and _free 0x30830.
// Same 63B+30B pair shape as Owner900 vector dtor+clear; /EHs provides the or [ebp-4],-1 state.
// Only the two members rowed from this file are instantiated here; whole-class
// instantiation emitted a non-retail COMDAT copy of operator=.
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its vector bodies.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>
struct TargetRef00217D4C { virtual void *destroy(unsigned int flags); int references; };
struct Rva005F8F96
{
	~Rva005F8F96();
	TargetRef00217D4C *m_00;
	int m_04;
};

template _STL::vector<Rva005F8F96, _STL::allocator<Rva005F8F96> >::~vector();
template void _STL::vector<Rva005F8F96, _STL::allocator<Rva005F8F96> >::_M_clear();
