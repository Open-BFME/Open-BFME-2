// cl: /MD /EHsc /DNDEBUG /D_STLP_USE_STATIC_LIB
// stlport
//
// ??1SpecialAbilityUpdate@@UAE@XZ, retail 0x00451F45, 93 bytes.
// Target evidence: the audited scalar deleting dtor 0x004522F0 (class-name
// string "SpecialAbilityUpdate" via slot 4) calls this body; derived module
// dtors (MissileLauncherBuildingUpdate 0x004CD9C0 and others) call it at the
// base position. Body: compiler vptr restores (+0 +0x0C +0x10 +0x20), a
// thiscall (1, 1) to 0x004502CE, destruction of the list<int> at +0x64
// (0x004EC395), then the base dtor 0x0024A797 (UpdateModule).
// Donor-carried: the BFME1 SpecialAbilityUpdateDestructor.cpp body
// `onExit(true, true)` supplies the callee name; the BFME1 layout (inline
// UpdateModule, AudioEventRTS member) does not apply here.
#include <list>

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> void _List_base<int, allocator<int> >::clear();
}

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> _List_base<int, allocator<int> >::~_List_base();
}

// list<int> destruction otherwise instantiates per-TU deallocate
// COMDATs (one byte shape per TU flags); explicit dllimport+forceinline
// specializations take those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void allocator<_List_node<int> >::deallocate(_List_node<int>* __p, size_t __n) const {
  _STLP_ASSERT( (__p == 0) == (__n == 0) )
    if (__p != 0) __sgi_alloc::deallocate((void*)__p, __n * sizeof(value_type));
}
template <> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<_List_node<int> *, _List_node<int>, allocator<_List_node<int> > >::deallocate(_List_node<int> *__p, size_t __n) {
  allocator<_List_node<int> >().deallocate(__p, __n);
}
}

#include "../../../../Include/GameLogic/Module/SpecialAbilityUpdate.h"

SpecialAbilityUpdate::~SpecialAbilityUpdate()
{
	SpecialAbilityUpdate::onExit(true, true);
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??1Rva00451F45@@UAE@XZ=??1SpecialAbilityUpdate@@UAE@XZ")

// The rowed constructor and its derived callers use this opaque base spelling.
// Native calls and the shared vtable identify the same complete destructor.
#pragma comment(linker, "/alternatename:??1Rva0044EF5E@@UAE@XZ=??1SpecialAbilityUpdate@@UAE@XZ")
