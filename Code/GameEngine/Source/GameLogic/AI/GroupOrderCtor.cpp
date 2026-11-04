// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
//
// ??0GroupOrder@@QAE@XZ at retail 0x005488C5 (36B). The
// intermediate GroupOrder base is 0x18 bytes: vtable 0xC6A520
// at +0, a vector member at +4 built through the ICF-folded empty
// _Vector_base at 0x211E58, and nulls at +0x10/+0x14. Its only callers are
// the six group orders the factory 0x00354EFC creates (formerly rowed as
// SpecialPowerModuleData; the real SpecialPower base is 0x004930A0). The
// name GroupOrder is inferred from those six class names. The vector
// element type is established by the copy constructor at 0x005488E9,
// which calls the verified vector<ScienceType> copy. Six derived group-order
// ctors call this base (see ChangeStanceGroupOrderCtor.cpp).
#include "Common/Snapshot.h"

#include <vector>

// __malloc_alloc<0> allocate/deallocate otherwise instantiate per-TU
// COMDATs (one byte shape per TU malloc/free wiring); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void *__malloc_alloc<0>::allocate(size_t __n)
{ void *__r = malloc(__n); if (!__r) __r = _S_oom_malloc(__n); return __r; }
template <> __declspec(dllimport) __forceinline
void __malloc_alloc<0>::deallocate(void *__p, size_t)
{ free((char *)__p); }
}

enum ScienceType { SCIENCE_NONE = 0 };

class Rva0036E346;

class GroupOrder : public Snapshot
{
public:
	GroupOrder();
	GroupOrder(const GroupOrder &other);
	GroupOrder(Rva0036E346 *holder);
	virtual ~GroupOrder();
	virtual void xfer(Xfer *xfer); // slot 3 of 0x0086A520

private:
	_STL::vector<ScienceType> m_list; // +4
	unsigned int m_10; // +0x10 fresh nonzero id (copy and holder ctors)
	unsigned int m_14; // +0x14
};

// ??0GroupOrder@@QAE@XZ @0x5488C5
GroupOrder::GroupOrder()
{
	m_10 = 0;
	m_14 = 0;
}
