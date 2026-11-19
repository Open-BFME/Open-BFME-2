// ?rva003F26AA@LivingWorldRegionConnection@@QAE_NPBVModuleData@@PAURva003F26AAPair@@@Z
// partial score=0.94 date=2026-09-30
// ?rva003F26AA@LivingWorldRegionConnection@@QAE_NPBVModuleData@@PAURva003F26AAPair@@@Z
// partial score=0.94 date=2026-09-30
// cl: /Ireference/shims/bfme2_ascii /Oy- /GX /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
// ?rva003F26AA@LivingWorldRegionConnection@@QAE_NPBVModuleData@@PAURva003F26AAPair@@@Z, retail 0x003F26AA 143B.
// Picks the slot tables by arg+0x18 StringBase<char>::isEmpty (rowed 0x00001E2F): a non-empty
// name takes the +0xe4/+0x180 tables, an empty name the +0xf0/+0x18c tables. Finds the first
// inner vector with room (byte-count mask spelling per retail: sub then test ~3, no shift),
// pushes the arg into it (rowed push_back 0x004DFCB0), copies the paired 8-byte entry to
// out, returns true; false when no slot has room.
// Evidence: neighbours LivingWorldRegionConnection dtor 0x003F2517 and filter TUs give the
// class and flags; callers 0x002B3CC5 0x002B670F 0x002B6749. The class really derives from
// Snapshot (see the dtor TU); modeled here as pads since this body never touches the vptr.
// The /Oy- keeps the EBP frame retail shows. /G7 fixes register allocation (ebx tab, ecx divisor).
// Fix from the banked attempt: the found branch copies a into a local before
// push_back; MSVC coalesces that local into the parameter home, emitting the
// retail self-store mov eax,[ebp+8] / mov [ebp+8],eax before the push.
// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit's
// flags (/G7) compile a different copy, and retail kept another unit's. This unit-local
// overload keeps the inlined code and offers the link no second copy.
#define _STLP_BFME_COPY_TRIVIAL_EXTERN  // call retail's one __copy_trivial (vendor/stlport/stl/_algobase.h)
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>
#include "ascii_string.h"
// Keep __node_alloc<true,0>::allocate inline-only: every call here is inlined,
// and this TU's COMDAT copy differs from the copy the link keeps.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void * _STLP_CALL __node_alloc<true, 0>::allocate(size_t __n)
{ return (__n > (size_t)_MAX_BYTES) ? __stl_new(__n) : _M_allocate(__n); }
}
// Keep __node_alloc<true,0>::deallocate inline-only: every call here is inlined,
// and this TU's /O1 COMDAT copy differs from the copy the link keeps.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_CALL __node_alloc<true, 0>::deallocate(void *__p, size_t __n)
{ if (__n > (size_t)_MAX_BYTES) __stl_delete(__p); else _M_deallocate(__p, __n); }
}
// Suppress this TU's non-retail copy of ??$_Construct@PBVModuleData@@PBV1@@_STL@@YAXPAPBVModuleData@@ABQBV1@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class ModuleData;
namespace _STL { template <> void _Construct<const ModuleData *, const ModuleData *>(const ModuleData **, const ModuleData *const &); }
// Suppress this TU's non-retail copy of ?_M_insert_overflow@?$vector@PBVModuleData@@V?$allocator@PBVModuleData@@@_STL@@@_STL@@IAEX:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> void vector<const ModuleData *, allocator<const ModuleData *> >::_M_insert_overflow(const ModuleData **, const ModuleData *const &, const __true_type &, size_t, bool); }
// Suppress this TU's non-retail copy of ?allocate@?$_STLP_alloc_proxy@PAPBVModuleData@@PBV1@V?$allocator@PBVModuleData@@@_STL@@@_S:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> const ModuleData **_STLP_alloc_proxy<const ModuleData **, const ModuleData *, allocator<const ModuleData *> >::allocate(size_t); }
// Suppress this TU's non-retail copy of ?allocate@?$allocator@PBVModuleData@@@_STL@@QBEPAPBVModuleData@@IPBX@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> const ModuleData **allocator<const ModuleData *>::allocate(size_t, const void *) const; }
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@PBVModuleData@@@_STL@@QBEXPAPBVModuleData@@I@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> void allocator<const ModuleData *>::deallocate(const ModuleData **, size_t) const; }
// Suppress this TU's non-retail copy of ?_M_clear@?$vector@PBVModuleData@@V?$allocator@PBVModuleData@@@_STL@@@_STL@@IAEXXZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> void vector<const ModuleData *, allocator<const ModuleData *> >::_M_clear(); }
// push_back is rowed at 0x004DFCB0 (kept copy). This unit's own copy, and the
// _Construct / placement-new copies it pulls in, differ from the kept ones.
// Declare it only, so the call binds to the kept copy.
namespace _STL { template <> void vector<const ModuleData *, allocator<const ModuleData *> >::push_back(const ModuleData *const &); }

class ModuleData
{
public:
	char _pad[0x18];
	StringBase<char> m_name; // +0x18
};

struct Rva003F26AAPair
{
	int m_a;
	int m_b;
};

class LivingWorldRegionConnection
{
public:
	bool rva003F26AA(const ModuleData *a, Rva003F26AAPair *out);

private:
	char _pad0[0xe4];
	Rva003F26AAPair *m_tabFull; // +0xe4
	char _pad1[0xf0 - 0xe8];
	Rva003F26AAPair *m_tabBlank; // +0xf0
	char _pad2[0x180 - 0xf4];
	_STL::vector<_STL::vector<const ModuleData *> > m_slotsFull; // +0x180
	_STL::vector<_STL::vector<const ModuleData *> > m_slotsBlank; // +0x18c
};

bool LivingWorldRegionConnection::rva003F26AA(const ModuleData *moduleData, Rva003F26AAPair *out)
{
	Rva003F26AAPair **tab;
	_STL::vector<_STL::vector<const ModuleData *> > *slots;
	if (!moduleData->m_name.isEmpty()) {
		tab = &m_tabFull;
		slots = &m_slotsFull;
	} else {
		tab = &m_tabBlank;
		slots = &m_slotsBlank;
	}
	unsigned n = slots->size();
	for (unsigned i = 0; i < n; ++i) {
		_STL::vector<const ModuleData *> &slot = (*slots)[i];
		if ((((char *)slot.end() - (char *)slot.begin()) & ~3) == 0) {
			const ModuleData *md = moduleData;
			(*slots)[i].push_back(md);
			*out = (*tab)[i];
			return true;
		}
	}
	return false;
}
