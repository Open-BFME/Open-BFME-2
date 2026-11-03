// cl: /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /DNDEBUG /DWIN32 /D_WINDOWS
// stlport
//
// ??0AutoPickUpUpdateModuleData@@QAE@XZ, retail 0x00496308, 151 bytes.
// Auto-pickup behavior data: the own table at 0x00C4F4B8 carries
// ScanDelayTime at +8, PickUpFilter at +0xC, ScanDistance at +0x10,
// EatObjectEntry at +0x14, AutoThrowObject at +0x20, RunFromButton at
// +0x21, RunFromButtonNumber at +0x24 and CanScanWhileAttackingOrMoving at
// +0x28, matching every store below; the ModuleData factory at 0x24E099
// news 0x2C and the pool key at 0x495CEC ends where the parse proc begins.
// Shape follows EnragedUpdateModuleDataCtor (empty UpdateModuleData base
// with inline-empty ctor plus declared-only dtor arms the EH states with
// no code, explicit vtable assigned from the mem-init so the store leads)
// plus RespawnUpdateModuleDataCtor (two 28B FixedStorage temps
// copy-constructed in place from the prototype at 0x00DFEFA4 through the
// rowed copy ctor, consumed by value through the 0x362087 pin). The
// EatObjectEntry vector at +0x14 builds through the 0x211E58 fold; its
// element type is unproven, so the TU keeps the BfmeE16 stand-in
// (fold-equivalent and byte-correct, BattlePlanUpdate precedent) and the
// row carries the identity.

// Vtable 0x00C4F108: the table whose slot 0 is ??_GAutoPickUpUpdateModuleData (vftable_map); bound to the ??_7 the ledger's deleting-dtor unit emits.
extern "C" const void *__identifier("??_7AutoPickUpUpdateModuleData@@6B@")[];

extern int BfmeLogicFramesPerSecond;

#include <vector>

#include "../../../../../Libraries/Include/Lib/BfmeE16.h"
// bfme link decl-only BfmeE16
namespace _STL { template <> vector<BfmeE16, allocator<BfmeE16> >::~vector(); }

template <int N> class BitFlags;
extern BitFlags<116> KINDOFMASK_NONE;

#include "../../../../Include/Common/BfmeFixedStorage0004543D.h"

#include "../../../../Include/GameLogic/Module/Rva003623E5Member.h"

#define LogicFramesPerSecond BfmeLogicFramesPerSecond

class UpdateModuleData
{
public:
	__declspec(dllimport) __forceinline UpdateModuleData() {}
	~UpdateModuleData();

private:
};

class AutoPickUpUpdateModuleData : public UpdateModuleData
{
public:
	AutoPickUpUpdateModuleData();

private:
	const void *m_vtable; // +0
	int m_unused04; // +4
	int m_scanDelayTime; // +8
	Rva003623E5Member m_pickUpFilter; // +0xC
	float m_scanDistance; // +0x10
	_STL::vector<BfmeE16> m_eatObjectEntries; // +0x14, element unproven
	unsigned char m_autoThrowObject; // +0x20
	unsigned char m_runFromButton; // +0x21
	unsigned char m_pad22[2]; // +0x22
	int m_runFromButtonNumber; // +0x24
	unsigned char m_canScanWhileAttackingOrMoving; // +0x28
	unsigned char m_tail[3]; // +0x29..+0x2B, factory news 0x2C
};

// ??0AutoPickUpUpdateModuleData@@QAE@XZ @0x496308
AutoPickUpUpdateModuleData::AutoPickUpUpdateModuleData()
	: m_vtable(reinterpret_cast<const void *>(__identifier("??_7AutoPickUpUpdateModuleData@@6B@")))
	, m_scanDelayTime(LogicFramesPerSecond)
	, m_scanDistance(300.0f)
{
	m_runFromButtonNumber = 0;
	m_autoThrowObject = 0;
	m_runFromButton = 0;
	m_canScanWhileAttackingOrMoving = 0;
	m_pickUpFilter.initFromStorages(
		BfmeFixedStorage0004543D(*reinterpret_cast<const BfmeFixedStorage0004543D *>(&KINDOFMASK_NONE)),
		BfmeFixedStorage0004543D(*reinterpret_cast<const BfmeFixedStorage0004543D *>(&KINDOFMASK_NONE)));
}
