// cl: /Ireference/shims/moduledata /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
//
// ??0GroupOrder@@QAE@ABV0@@Z at retail 0x005488E9 (95B, not 92:
// the body ends leave plus ret-4). The intermediate GroupOrder
// base is 0x18 bytes: vtable 0xC6A520 at +0, a vector member at +4 copied
// through the rowed vector<ScienceType> copy at 0x54878E, and generated id
// words at +0x10/+0x14 fed from the absolute counter at 0x00E05F74 (fresh
// nonzero id, skipping zero). The member element type is proven by the copy
// call: a trivial 4-byte element folds to the rowed ScienceType spelling.
// Snapshot supplies the native base lifetime and the compiler installs
// GroupOrder's vptr, matching the destructor's proven Snapshot lineage.
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

enum ScienceType
{
	SCIENCE_NONE = 0
};
// Native scalar-vector cleanup uses the rowed game-memory free wrapper.
// Keep the first compatible ScienceType destructor's allocator identity.
void __cdecl Rva00030830GameFree(void *);
namespace _STL {
template <> inline _Vector_base<ScienceType, allocator<ScienceType> >::~_Vector_base()
{ if (_M_start) Rva00030830GameFree(_M_start); }
}


// Absolute counter at 0x00E05F74; the copy hands out a fresh nonzero id.
extern int g_Va00E05F74;
// g_Va00E05F74: matched references place it at VA 0xe05f74 (zero-filled .bss).
int g_Va00E05F74;

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

// ??0GroupOrder@@QAE@ABV0@@Z @0x5488E9
GroupOrder::GroupOrder(const GroupOrder &other)
	: m_list(other.m_list)
{
	m_10 = ++g_Va00E05F74;
	m_14 = 0;
	if (m_10 == 0)
		m_10 = ++g_Va00E05F74;
}
// bfme link decl-only begin
namespace _STL { template <> ScienceType * allocator<ScienceType>::allocate(unsigned int,void const *) const; }
// bfme link decl-only end
