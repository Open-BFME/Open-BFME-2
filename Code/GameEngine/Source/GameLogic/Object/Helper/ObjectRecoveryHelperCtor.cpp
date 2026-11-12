// cl: /DNDEBUG /MD /GX
//
// ??0ObjectRecoveryHelper@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x0028C9F9, 84 bytes.
// ObjectRecoveryHelper behavior ctor over the rowed ObjectHelper base
// (0x28C8DF, thing plus data): stores the class's three vftables (0x00BFBD98
// at +0, the UpdateModule family's 0x00BEFF90 at +0x0C, 0x00BFBD8C at +0x10),
// then setWakeFrame(getObject(), UPDATE_SLEEP_FOREVER) (0x44DF71). The EH frame
// unwinds the constructed ObjectHelper base through ~ObjectHelper 0x004DF7C2.
// BFME1 donor is ObjectRecoveryHelperCtor.cpp; BFME2 keeps the shape. The
// rowed factory 0x29955B (news 0x20, no new members) is the sole raw caller,
// and the ObjectRecoveryHelper pool key at 0x28CA4D immediately follows.
//
// Retail 0x00BFBD98 (13 slots): deleting dtor 0x0028CA98, loadPostProcess
// 0x00483CEF (`jmp 0x00497805`), the name getter 0x0028CA92, xfer 0x004DF87C,
// getModuleNameKey 0x0028CA4D, then UpdateModule's slots. 0x00BFBD8C: update
// 0x004DF84F, then UpdateModule's getDisabledTypesToProcess and wake slots.

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
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

#include "../../../../Include/GameLogic/Module/UpdateModule.h"
#include "../../../../Include/GameLogic/Module/ObjectHelper.h"

class ObjectRecoveryHelper : public ObjectHelper
{
public:
	ObjectRecoveryHelper(Thing *thing, const ModuleData *moduleData);
	virtual ~ObjectRecoveryHelper();

	virtual NameKeyType getModuleNameKey() const;
	virtual UpdateSleepTime update();

protected:
	virtual void loadPostProcess();
	virtual const char *GetSnapshotName() const;
	virtual void xfer(Xfer *xfer);
};

// ??0ObjectRecoveryHelper@@QAE@PAVThing@@PBVModuleData@@@Z @0x28C9F9
ObjectRecoveryHelper::ObjectRecoveryHelper(Thing *thing, const ModuleData *moduleData)
	: ObjectHelper(thing, moduleData)
{
	setWakeFrame(getObject(), UPDATE_SLEEP_FOREVER);
}

// Slot 1 of 0x00BFBD98: 0x00483CEF, `jmp 0x00497805` to ObjectHelper's; the
// body the other helpers' tables share.
void ObjectRecoveryHelper::loadPostProcess()
{
	ObjectHelper::loadPostProcess();
}

// ObjectHelper's xfer, 0x004DF81B, is still rowed under its placeholder class.
#include "../../../../Include/Common/Rva004DF81B.h"

// Slot 3 of 0x00BFBD98: 0x004DF87C, version 1 then ObjectHelper's xfer; the
// body ObjectRepulsorHelper and ObjectWeaponStatusHelper share.
void ObjectRecoveryHelper::xfer(Xfer *xfer)
{
	xfer->Version1();
	((Rva004DF81B *)this)->xfer(xfer);
}
