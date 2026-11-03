// cl: /GX /MD /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0InstantDeathBehaviorModuleData@@QAE@XZ, retail 0x0045D176 (71 bytes).
// Frameless derived ctor over the pinned DestroyDieModuleData intermediate base
// (0x00253510, size 0x38): the base holds the vptr (vtable slot 0 is the
// deleting destructor 0x0045D271, so both declare virtual destructors;
// the +0x38 member offset proves it, identity unknown) so the derived
// shares it without shifting, the compiler installs vtable 0x00C41F28
// before the four vector members construct through the ICF-folded
// Vector_base at 0x00211E58 (one-byte allocator temporaries on ebp). No EH:
// every subobject is trivially destructible, so the throwing base calls
// need no unwind. Element type int is a stand-in (trivial plus resolving
// through the ICF-folded int row; the ZH donor carries pointer vectors but
// the 29B body is T-independent per the folded rows; the true elements are
// unproven). Identity is the ModuleFactory registration under
// "InstantDeathBehavior" (sole-caller data factory per the superseded ctor
// pin).

#include <vector>

// vector<int>/char destruction otherwise instantiates per-TU allocator
// deallocate COMDATs (one byte shape per TU flags); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies. Bodies are verbatim primary.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void allocator<int>::deallocate(int* __p, size_t __n) const {
  _STLP_ASSERT( (__p == 0) == (__n == 0) )
    if (__p != 0) __sgi_alloc::deallocate((void*)__p, __n * sizeof(value_type));
}
template <> void _STLP_alloc_proxy<int*, int, allocator<int> >::deallocate(int*, size_t);
// Declaration-only: retail keeps one 14-byte copy of the vector<int> teardown
// (0x0007FAB3); this TU's flags would emit a private 24-byte one.
template <> vector<int, allocator<int> >::~vector();
template <> _Vector_base<int, allocator<int> >::~_Vector_base();
}

#include "../../../../Include/GameLogic/Module/DestroyDieModuleData.h"

class InstantDeathBehaviorModuleData : public DestroyDieModuleData
{
public:
	InstantDeathBehaviorModuleData();
	virtual ~InstantDeathBehaviorModuleData();

private:
	_STL::vector<int> m_vec38;	// +0x38, element stand-in
	_STL::vector<int> m_vec44;	// +0x44, element stand-in
	_STL::vector<int> m_vec50;	// +0x50, element stand-in
	_STL::vector<int> m_vec5C;	// +0x5C, element stand-in
};

InstantDeathBehaviorModuleData::InstantDeathBehaviorModuleData()
	: DestroyDieModuleData()
{
}

// ??_GInstantDeathBehaviorModuleData@@UAEPAXI@Z @0x0045D271 (28 B): slot 0 of
// vtable 0x00C41F28, compiler-emitted here with the vtable; calls the dtor at
// 0x0045D28D. Owner evidence (audited 2026-09-26): retail registration
// InstantDeathBehavior -> data factory 0x0024B213 -> ctor 0x0045D176, primary
// vptr store 0x0045D189.
