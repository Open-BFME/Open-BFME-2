// cl: /DNDEBUG /MD /GX
//
// ??0ObjectWeaponStatusHelper@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x0028CB45, 81 bytes.
// ObjectWeaponStatusHelper behavior ctor over the rowed ObjectHelper base
// (0x28C8DF, thing plus data): stores the class's three vftables (0x00BFBE48
// at +0, the UpdateModule family's 0x00BEFF90 at +0x0C, 0x00BFBE3C at +0x10),
// then setWakeFrame(getObject(), UPDATE_SLEEP_NONE) (0x44DF71). The EH frame
// unwinds the constructed ObjectHelper base through ~ObjectHelper 0x004DF7C2.
// BFME1 donor is ObjectWeaponStatusHelperCtorThunk.cpp; unlike the other
// helpers this one wakes immediately since it runs every frame. The rowed
// factory 0x299806 (news 0x20, no new members) is the sole raw caller, and
// the ObjectWeaponStatusHelper pool key at 0x28CB96 immediately follows.
//
// Retail 0x00BFBE48 (13 slots): deleting dtor 0x0028CBE1, loadPostProcess
// 0x00483CEF (`jmp 0x00497805`), the name getter 0x0028CBDB, xfer 0x004DF87C,
// getModuleNameKey 0x0028CB96, then UpdateModule's slots up to slot 12,
// getUpdatePhase 0x0044827C (`push 3; pop eax; ret`, a body retail folds
// with ATL's _AtlGetThreadACPReal). 0x00BFBE3C: update 0x0028F976,
// getDisabledTypesToProcess 0x004DF8C2 (bits 3 and 8), then UpdateModule's
// wake slot.

class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
class Coord3DBase;
struct ICoord3D;
struct Region3D;
struct IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
class RealRange;
struct RGBColor;
class RGBAColorReal;
class RGBAColorInt;
struct XferUnknown11;
#include "../../../../Include/Common/BfmeXfer.h"

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

#include "../../../../Include/GameLogic/Module/UpdateModule.h"
#include "../../../../Include/GameLogic/Module/ObjectHelper.h"

class ObjectWeaponStatusHelper : public ObjectHelper
{
public:
	ObjectWeaponStatusHelper(Thing *thing, const ModuleData *moduleData);
	virtual ~ObjectWeaponStatusHelper();

	virtual NameKeyType getModuleNameKey() const;
	virtual UpdateSleepTime update();
	virtual DisabledMaskType getDisabledTypesToProcess() const;

protected:
	virtual void loadPostProcess();
	virtual const char *GetSnapshotName() const;
	virtual void xfer(Xfer *xfer);
	virtual SleepyUpdatePhase getUpdatePhase() const;
};

// ??0ObjectWeaponStatusHelper@@QAE@PAVThing@@PBVModuleData@@@Z @0x28CB45
ObjectWeaponStatusHelper::ObjectWeaponStatusHelper(Thing *thing, const ModuleData *moduleData)
	: ObjectHelper(thing, moduleData)
{
	setWakeFrame(getObject(), UPDATE_SLEEP_NONE);
}

// Slot 1 of 0x00BFBE48: 0x00483CEF, `jmp 0x00497805` to ObjectHelper's; the
// body the other helpers' tables share.
void ObjectWeaponStatusHelper::loadPostProcess()
{
	ObjectHelper::loadPostProcess();
}

// ObjectHelper's xfer, 0x004DF81B, is still rowed under its placeholder class.
#include "../../../../Include/Common/Rva004DF81B.h"

// Slot 3 of 0x00BFBE48: 0x004DF87C, version 1 then ObjectHelper's xfer; the
// body ObjectRecoveryHelper and ObjectRepulsorHelper share.
void ObjectWeaponStatusHelper::xfer(Xfer *xfer)
{
	xfer->Version1();
	((Rva004DF81B *)this)->xfer(xfer);
}

// Slot 12 of 0x00BFBE48: 0x0044827C. UpdateModule's own (0x0022C4CB) returns
// phase 2; this helper's returns phase 3. The phase's enumerator name is not
// recovered.
SleepyUpdatePhase ObjectWeaponStatusHelper::getUpdatePhase() const
{
	return (SleepyUpdatePhase)3;
}
