// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/open-bfme-1/Code/GameEngine/Source/Common/System /Ireference/open-bfme-1/Code/GameEngine/Include /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib

// Module-constructor family shape: an out-of-line ObjectModule base call
// (pinned at 0x000170E4), then UpdateModule's constructor inlined -- its two
// vtables at 0x0c and 0x10 then its three members -- then this class's own
// three vtables.
//
// Here every member store precedes the vtable stores, so the members are plain
// and the vptr stores sink past the whole run. MSVC groups by value: the zeros
// at 0x14, 0x25, 0x20 and 0x24 first, then the two -1s at 0x18 and 0x1c. The
// derived stores are written in retail's order, which is not offset order.

class Thing;
class ModuleData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
#define BFME_SNAPSHOT_NAME_SLOT
#include "../../../../Include/Common/ObjectModule.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
#include "../../../../Include/GameLogic/Module/UpdateModule.h"

// Target table at RVA 0x00851A0C has 13 primary slots: RadarUpdate owns
// GetSnapshotName (0x004A0C27), xfer (0x004A0CC3), and getModuleNameKey
// (0x004A0C2D). Its +0x10 interface table at 0x00851A00 owns update
// (0x004A0D5F). The getter owner is still rowed under a placeholder name, so
// the constructor stores retail's tables itself.
// Retail's tables, each slot the ledger row at the native address.




class __declspec(novtable) RadarUpdate : public UpdateModule
{
public:
	RadarUpdate(Thing *, const ModuleData *);

	virtual NameKeyType getModuleNameKey() const;
	virtual UpdateSleepTime update();
protected:
	virtual const char *GetSnapshotName() const;
	virtual void xfer(Xfer *xfer);
public:

	int m_value20;							///< 0x20
	bool m_flag24;							///< 0x24
	bool m_flag25;							///< 0x25
};

// The constructor stores compiler tables the data ledger binds at retail's
// addresses: Rva004A0C0E's (RadarUpdate's placeholder, Rva0024A797Derived.cpp) at
// +0 and +0x10, and the 47-slot BehaviorModuleInterface table folded across the
// module family at +0x0C, by the name its definer AttributeModifierPoolUpdate.cpp emits.
extern "C" const void *const __identifier("??_7Rva004A0C0E@@6BUpdateModule@@@")[];  // VA 0x00C51A0C
extern "C" const void *const __identifier("??_7AttributeModifierPoolUpdate@@6BBehaviorModuleInterface@@@")[];  // VA 0x00BEFF90
extern "C" const void *const __identifier("??_7Rva004A0C0E@@6BRva004A0C0E_B2@@@")[];  // VA 0x00C51A00

// ??0RadarUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
RadarUpdate::RadarUpdate( Thing *thing, const ModuleData *moduleData )
	: UpdateModule( thing, moduleData )
{
	m_flag25 = false;
	m_value20 = 0;
	m_flag24 = false;
	*(const void *const **)this = __identifier("??_7Rva004A0C0E@@6BUpdateModule@@@");
	*(const void *const **)((char *)this + 0x0C) = __identifier("??_7AttributeModifierPoolUpdate@@6BBehaviorModuleInterface@@@");
	*(const void *const **)((char *)this + 0x10) = __identifier("??_7Rva004A0C0E@@6BRva004A0C0E_B2@@@");
}
