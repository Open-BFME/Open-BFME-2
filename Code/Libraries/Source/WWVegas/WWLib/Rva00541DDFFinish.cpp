// ?insert@?$vector@VRva0054103E@@V?$allocator@VRva0054103E@@@_STL@@@_STL@@QAEPAVRva0054103E@@PAV3@ABV3@@Z
// partial score=0.97 date=2026-10-02
// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// stlport
//
// ?insert@?$vector@VRva0054103E@@V?$allocator@VRva0054103E@@@_STL@@@_STL@@QAEPAVRva0054103E@@PAV3@ABV3@@Z @0x00541DDF 152B.
// STLport 4.5.3 vector<Rva0054103E>::insert single-element insert via the
// pristine vendor _vector.h/_algobase.h. The reference/shims/bfmealloc
// _algobase.h marks __copy_backward_ptrs __forceinline, so it inlines the
// 5-arg __copy_backward; retail keeps the 4-arg wrapper call at 0x005412C5,
// so this TU must build against the unshimmed vendor header. Element 0x14
// bytes with Region2D at +4 proven by rowed copy ctor 0x0054103E. Calls rowed
// Construct 0x0054106D plus copy ctor 0x0054103E plus copy_backward_ptrs
// 0x005412C5 plus overflow 0x005417C6.
// The trailing line is the vendored `*__position = __x_copy`: the emitted
// ??4Rva0054103E assignment is ICF-folded onto the identical memberwise copy
// ctor at 0x0054103E (retail's REL32 at 0x00541E4F reads 0x0054103E), pinned
// in reverse/symbols.csv like the existing ??4PlaneClass/??4SphereClass folds
// at 0x004254E.
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

#include <vector>
struct Region2D
{
	Region2D(const Region2D &that);
	float x_min;
	float y_min;
	float x_max;
	float y_max;
};
class Rva0054103E
{
public:
	Rva0054103E();
	Rva0054103E(const Rva0054103E &that);
	Rva0054103E &operator=(const Rva0054103E &that);
private:
	int m_00;
	Region2D m_04;
};
template _STL::vector<Rva0054103E>::iterator _STL::vector<Rva0054103E>::insert(Rva0054103E *, const Rva0054103E &);
