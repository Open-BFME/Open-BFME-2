// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// vector<AutoPickUpEatObjectEntry> growth path, STLport 4.5.3:
//   push_back            retail 0x004964BB, 52 bytes
//   _M_insert_overflow   retail 0x0049639F, 193 bytes
//
// Target evidence: AutoPickUpUpdateModuleData::iniParseEatObjectEntry
// 0x004964EF calls 0x004964BB with the store vector in ecx and the local
// entry; 0x004964BB copies the 12-byte entry in place (three movsd) or
// calls 0x0049639F, which calls the shared 12-byte allocate 0x00395928,
// copy 0x000766F5 and fill_n 0x002A73C0 (ICF bodies rowed under the
// BfmeE12 stand-in, pinned here under this TU's element) and the vector's
// own clear 0x004962EA (range destroy through the entry destructor, then
// free), proving the element is non-trivially destructible. Entry layout
// (filter handle, MyHealth, TargetHealth) is the BFME 1 donor's
// AutoPickUpEatObjectEntry; see AutoPickUpUpdateParseEatObjectEntry.cpp.
// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit's
// flags (/G7) compile a different copy, and retail kept another unit's. This unit-local
// overload keeps the inlined code and offers the link no second copy.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

class Rva00360D26Member
{
public:
	Rva00360D26Member();
	~Rva00360D26Member();

private:
	unsigned int m_handle;
};

struct AutoPickUpEatObjectEntry
{
	Rva00360D26Member m_filter;
	float m_myHealth;
	float m_targetHealth;
};

#include <vector>
template void _STL::vector<AutoPickUpEatObjectEntry>::_M_insert_overflow(
	AutoPickUpEatObjectEntry *,
	const AutoPickUpEatObjectEntry &,
	const _STL::__false_type &,
	unsigned int,
	bool);
template void _STL::vector<AutoPickUpEatObjectEntry>::push_back(
	const AutoPickUpEatObjectEntry &);
