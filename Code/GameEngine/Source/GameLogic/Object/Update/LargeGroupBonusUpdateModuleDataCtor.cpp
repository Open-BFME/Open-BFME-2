// cl: /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /Ow
// stlport
// ??0LargeGroupBonusUpdateModuleData@@QAE@XZ, retail 0x004901BD, 104 bytes.
//
// Constructor of the module data (companion of the dtor TU
// LargeGroupBonusUpdateModuleDataDtor.cpp, which keeps the dtor-ful member
// declarations; this TU keeps dtor-less ones for retail's single-state frame).
// /Ow (assume no aliasing across calls) lets the update-rate global load
// (0x00A03994, frame-rate init) float above the vtable and state stores as in
// retail; the barrier at the end keeps the EH-chain restore behind the last
// member store.
#include <vector>
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
#include "ascii_string.h"
#include "../../../../Include/Common/BfmeModuleData.h"
// bfme link decl-only begin
namespace _STL { template <> void _Destroy<AsciiString *>(AsciiString *, AsciiString *); }
namespace _STL { template <> void _Destroy<AsciiString>(AsciiString *); }
namespace _STL { template <> vector<AsciiString, allocator<AsciiString> >::~vector(); }
// bfme link decl-only end
// Keep vector<AsciiString>'s storage release inline-only: nothing here calls it
// out of line, and this TU's COMDAT copies are not the bodies retail kept.
namespace _STL {
template <> __declspec(dllimport) __declspec(nothrow) __forceinline
void allocator<AsciiString>::deallocate(AsciiString *__p, size_t) const { if (__p != 0) ::free((void*)__p); }
template <> __declspec(dllimport) __declspec(nothrow) __forceinline
void _STLP_alloc_proxy<AsciiString*, AsciiString, allocator<AsciiString> >::deallocate(AsciiString *__p, size_t __n)
{ allocator<AsciiString>::deallocate(__p, __n); }
template <> __declspec(dllimport) __declspec(nothrow) __forceinline
_Vector_base<AsciiString, allocator<AsciiString> >::~_Vector_base()
{ if (_M_start != 0) _M_end_of_storage.deallocate(_M_start, _M_end_of_storage._M_data - _M_start); }
}
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@VAsciiString@@@_STL@@QBEXPAVAsciiString@@I@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class AsciiString;
namespace _STL { template <> void allocator<AsciiString>::deallocate(AsciiString *, size_t) const; }
#include "../../../../Include/GameLogic/Module/Rva003623E5Filter.h"
// The native C4D2A8 table shares ModuleData slots 1-30 unchanged.
class __declspec(novtable) UpdateModuleData : public ModuleData
{
public:
	// Retail expands the empty base constructor; emit no competing COMDAT.
	__declspec(dllimport) __forceinline UpdateModuleData() {}
	virtual ~UpdateModuleData();
};
extern int g_00E03994;	// owned by Rva007ABC6FFrameRateInits.cpp (frame-rate inits)
class LargeGroupBonusUpdateModuleData : public UpdateModuleData
{
public:
	LargeGroupBonusUpdateModuleData();
	virtual ~LargeGroupBonusUpdateModuleData();
private:
	int m_unused04;
	int m_updateRate;
	Rva003623E5Filter m_hordeMemberFilter;
	int m_count;
	float m_radius;
	bool m_alliesOnly;
	float m_rubOffRadius;
	_STL::vector<AsciiString> m_flagSubObjectNames;
	AsciiString m_attributeModifier;
};
// ??0LargeGroupBonusUpdateModuleData@@QAE@XZ @0x004901BD
LargeGroupBonusUpdateModuleData::LargeGroupBonusUpdateModuleData() :
	m_updateRate(g_00E03994),
	m_count(0),
	m_radius(0.0f),
	m_alliesOnly(true),
	m_rubOffRadius(20.0f)
{
	_ReadWriteBarrier();
}
