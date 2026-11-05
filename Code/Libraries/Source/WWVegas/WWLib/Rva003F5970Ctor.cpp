// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?rva003F5970@Rva003F5970@@QAE@HPBVModuleData@@@Z @0x003F5970 142B
// Evidence: caller 0x003F652E builds Pod48 temp via this; dtor Rva003F610FElement 0x003F535B; vectors ModuleData* + Pod104; base E16 via 0x00211E58
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

class ModuleData;

#include "../../../Include/Lib/BfmeE16.h"
// Suppress this TU's non-retail copy of ??$_Construct@UBfmePod104@@U1@@_STL@@YAXPAUBfmePod104@@ABU1@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod104;
namespace _STL { template <> void _Construct<BfmePod104,BfmePod104>(BfmePod104 *,BfmePod104 const &); }
// Suppress this TU's non-retail copy of ?push_back@?$vector@UBfmePod104@@V?$allocator@UBfmePod104@@@_STL@@@_STL@@QAEXABUBfmePod104:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod104;
namespace _STL { template <> void vector<BfmePod104,allocator<BfmePod104> >::push_back(BfmePod104 const &); }
// Suppress this TU's non-retail copy of ?_M_clear@?$vector@UBfmeAssignRecord104@@V?$allocator@UBfmeAssignRecord104@@@_STL@@@_STL@@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmeAssignRecord104;
namespace _STL { template <> void vector<BfmeAssignRecord104,allocator<BfmeAssignRecord104> >::_M_clear(); }
// Suppress this TU's non-retail copy of ?reserve@?$vector@UBfmeAssignRecord104@@V?$allocator@UBfmeAssignRecord104@@@_STL@@@_STL@@Q:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmeAssignRecord104;
namespace _STL { template <> void vector<BfmeAssignRecord104,allocator<BfmeAssignRecord104> >::reserve(unsigned int); }
// Suppress this TU's non-retail copy of ??$__uninitialized_copy@PAUBfmeAssignRecord104@@PAU1@@_STL@@YAPAUBfmeAssignRecord104@@PAU1:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmeAssignRecord104;
namespace _STL { template <> BfmeAssignRecord104 * __uninitialized_copy<BfmeAssignRecord104 *,BfmeAssignRecord104 *>(BfmeAssignRecord104 *,BfmeAssignRecord104 *,BfmeAssignRecord104 *,__false_type const &); }
// Suppress this TU's non-retail copy of ??$_Construct@UBfmeAssignRecord104@@U1@@_STL@@YAXPAUBfmeAssignRecord104@@ABU1@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmeAssignRecord104;
namespace _STL { template <> void _Construct<BfmeAssignRecord104,BfmeAssignRecord104>(BfmeAssignRecord104 *,BfmeAssignRecord104 const &); }
// bfme link decl-only BfmeE16
namespace _STL { template <> vector<BfmeE16, allocator<BfmeE16> >::~vector(); }

// The overflow body is supplied by StlportVectorInsertOverflowFamily.cpp.
struct BfmePod104;
namespace _STL {
template <> void vector<BfmePod104, allocator<BfmePod104> >::_M_insert_overflow(BfmePod104 *, const BfmePod104 &, const __false_type &, unsigned int, bool);
}

struct BfmePod104
{
	int a[26];
};

// The record reserve body is supplied by stlport_asciistring_record_bodies.cpp.
namespace _STL {
template <> void vector<BfmeAssignRecord104, allocator<BfmeAssignRecord104> >::reserve(unsigned int);
}

struct BfmeAssignRecord104
{
	int a[26];
};

#include "../../../../GameEngine/Include/Common/ModuleData.h"

// Opaque record offsets; keep the canonical ModuleData pointer in the ABI.
struct Rva003F5970RecordView
{
	char _pad[0x78];
	BfmePod104 *m_p78;
};

struct Rva003F5970
{
	int m_00;
	_STL::vector<BfmeE16> m_04;
	_STL::vector<BfmeE16> m_10;
	int m_1C[5];
	Rva003F5970(int a, const ModuleData *b);
};

Rva003F5970::Rva003F5970(int a, const ModuleData *moduleData)
	: m_00(a)
	, m_04(_STL::allocator<BfmeE16>())
	, m_10(_STL::allocator<BfmeE16>())
{
	m_1C[0] = a;
	m_1C[1] = 0;
	m_1C[2] = 0;
	m_1C[3] = 0;
	m_1C[4] = 0;
	((_STL::vector<const ModuleData *> *)&m_04)->reserve(4);
	const ModuleData *tmp = moduleData;
	((_STL::vector<const ModuleData *> *)&m_04)->push_back(tmp);
	((_STL::vector<BfmeAssignRecord104> *)&m_10)->reserve(4);
	((_STL::vector<BfmePod104> *)&m_10)->push_back(*reinterpret_cast<const Rva003F5970RecordView *>(moduleData)->m_p78);
}
