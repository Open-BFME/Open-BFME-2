// cl: /GX /MD /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0GiveUpgradeUpdateModuleData@@QAE@XZ, retail 0x0049C4D2 (72 bytes).
// Frameless derived ctor over the pinned SpecialAbilityUpdateModuleData intermediate base
// (0x0044EB54, size 0xC8): the base holds the vptr (vtable slot 0 is the
// deleting destructor 0x0049C624, so both declare virtual destructors;
// the +0xC8 member offset proves it, identity unknown) so the derived
// shares it without shifting, the compiler installs vtable 0x00C51280
// before the +0xC8 vector member constructs through the ICF-folded
// Vector_base at 0x00211E58 (allocator temp on esp), then the body clears
// two int slots and a flag byte and loads the +0xDC float slot from an
// extern 0.025 global (DIR32-masked like the retail global; a literal would
// emit an integer mov-imm instead of the retail literal load). No EH: every
// subobject is trivially destructible, so the throwing vector-base call
// needs no unwind. Element type int is a stand-in (trivial plus resolving
// through the ICF-folded int row; AsciiString is refuted by the missing EH
// frame; the true element is unproven). Identity is the ModuleFactory
// registration under "GiveUpgradeUpdate" (sole-caller data factory per the
// superseded ctor pin).

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

#include "../../../../Include/GameLogic/Module/SpecialAbilityUpdateModuleData.h"

extern float g_bfmeGiveUpgrade0025;	// 0.025 at retail 0xC5127C (DIR32-masked)
// g_bfmeGiveUpgrade0025: matched references place it at VA 0xc5127c (retail .rdata value 0.025f).
float g_bfmeGiveUpgrade0025 = 0.025f;

class GiveUpgradeUpdateModuleData : public SpecialAbilityUpdateModuleData
{
public:
	GiveUpgradeUpdateModuleData();
	virtual ~GiveUpgradeUpdateModuleData();

private:
	_STL::vector<int> m_vecC8;	// +0xC8, element stand-in
	int m_intD4;	// +0xD4
	int m_intD8;	// +0xD8
	float m_floatDC;	// +0xDC
	bool m_flagE0;	// +0xE0
};

GiveUpgradeUpdateModuleData::GiveUpgradeUpdateModuleData()
	: SpecialAbilityUpdateModuleData()
{
	m_floatDC = g_bfmeGiveUpgrade0025;
	m_intD4 = 0;
	m_intD8 = 0;
	m_flagE0 = false;
}

// ??_GGiveUpgradeUpdateModuleData@@UAEPAXI@Z @0x0049C624 (28 B): slot 0 of
// vtable 0x00C51280, compiler-emitted here with the vtable; calls the rowed
// dtor at 0x0049C640, then operator delete at 0x0002FD60.
