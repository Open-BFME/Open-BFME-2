// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /O1 /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// ?reset@LocomotorStore@@UAEXXZ retail 0x001E681D (66 bytes), from the
// WorldBuilder lead (LocomotorStore::reset in Locomotor.cpp) and Zero Hour's
// Locomotor.cpp: drop each template's overrides and erase the entries whose
// template goes away with them (erase(it++)).
//
// Target facts: m_locomotorTemplates sits at +0xC (as in the sibling
// LocomotorStoreFindTemplate.cpp view); the member is spelled map<int, void*>
// so the emitted erase names the rowed int/void* tree erase 0x005530A8
// (identical tree mechanics), and the stored pointer is the template's
// Overridable base (deleteOverrides 0x001E35ED).

#include <map>

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

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

#include "../../../Include/Common/Overridable.h"

#include "../../../../Libraries/Source/subsystem/SubsystemInterface.h"

class LocomotorStore : public SubsystemInterface
{
public:
	virtual void init();
	virtual void reset();

private:
	_STL::map<int, void *> m_locomotorTemplates;
};

void LocomotorStore::reset()
{
	_STL::map<int, void *>::iterator it;
	for (it = m_locomotorTemplates.begin(); it != m_locomotorTemplates.end(); ) {
		Overridable *locoTemp = ((Overridable *)(*it).second)->deleteOverrides();
		if (!locoTemp)
			m_locomotorTemplates.erase(it++);
		else
			++it;
	}
}
