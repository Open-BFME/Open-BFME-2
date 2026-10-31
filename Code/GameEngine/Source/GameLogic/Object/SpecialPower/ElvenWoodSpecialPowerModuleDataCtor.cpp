// cl: /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
// stlport
//
// ??0ElvenWoodSpecialPowerModuleData@@QAE@XZ, retail 0x004C3DA9, 75 bytes.
// Elven-wood data: the own table at 0x00C5D018 carries ElvenGroveObject at
// +0x88, ElvenNumObjects at +0x8C, ElvenWoodRadius at +0x90 (10.0f),
// ElvenWoodFX at +0x94 and ElvenWoodOCL at +0x98, matching every store
// below; the ModuleData factory at 0x251CB4 news 0x9C and the pool key at
// 0x4C3943 proves the class. Shape follows RousingSpeechUpdateModuleDataCtor
// (opaque 0x7C virtual base through the 0x4930A0 pin, derived vtable,
// BfmeE16 vector member through the 0x211E58 fold, /arch:SSE float).
// Retail runs base-call, vtable, vector-call, zeros and the 10.0f radius,
// which the init-list transcription reproduces: the vector element type is
// unproven, so the TU keeps the BfmeE16 stand-in (fold-equivalent and
// byte-correct, BattlePlanUpdate precedent) and the row carries the identity.

#include "../../../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include <vector>

#include "../../../../../Libraries/Include/Lib/BfmeE16.h"
// bfme link decl-only begin
namespace _STL { template <> __declspec(nothrow) _Vector_base<BfmeE16,_STL::allocator<BfmeE16> >::_Vector_base(const allocator<BfmeE16> &); }
namespace _STL { template <> _Vector_base<BfmeE16,_STL::allocator<BfmeE16> >::~_Vector_base(); }
// bfme link decl-only end
// bfme link decl-only BfmeE16
namespace _STL { template <> vector<BfmeE16, allocator<BfmeE16> >::~vector(); }
// Suppress this TU's non-retail BfmeE16 proxy deallocate copy (family2-LK3 row 34):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void _STLP_alloc_proxy<BfmeE16*, BfmeE16, allocator<BfmeE16> >::deallocate(BfmeE16*, size_t);
}

typedef float Real;
class FXList;
class ObjectCreationList;
class SpecialPowerModuleData
{
public:
	SpecialPowerModuleData();
	virtual ~SpecialPowerModuleData();

private:
	unsigned char m_pad[0x7C - 4];
};

class ElvenWoodSpecialPowerModuleData : public SpecialPowerModuleData
{
public:
	ElvenWoodSpecialPowerModuleData();
	virtual ~ElvenWoodSpecialPowerModuleData();

	_STL::vector<BfmeE16> m_elves; // +0x7C, element unproven
	AsciiString m_objectName; // +0x88
	int m_numObjects; // +0x8C
	Real m_radius; // +0x90
	FXList *m_fx; // +0x94
	ObjectCreationList *m_ocl; // +0x98
};

// ??0ElvenWoodSpecialPowerModuleData@@QAE@XZ @0x4C3DA9
ElvenWoodSpecialPowerModuleData::ElvenWoodSpecialPowerModuleData()
	: SpecialPowerModuleData()
	, m_numObjects(0)
	, m_radius(10.0f)
	, m_fx(0)
	, m_ocl(0)
{
}
