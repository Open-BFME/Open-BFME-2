// cl: /DNDEBUG /MD
//
// ??0ObjectRepulsorHelper@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x0028CAB4, 42 bytes.
// ObjectRepulsorHelper behavior ctor over the rowed ObjectHelper base
// (0x28C8DF, thing plus data): stores the class's three vftables (0x00BFBDF0
// at +0, the UpdateModule family's 0x00BEFF90 at +0x0C, 0x00BFBDE4 at +0x10)
// and nothing else. BFME1 donor is ObjectRepulsorHelper.cpp; BFME2 keeps the
// empty-body shape. The rowed factory 0x299613 (news 0x20, no new members) is
// the sole raw caller, and the ObjectRepulsorHelper pool key at 0x28CADE
// immediately follows.
//
// Retail 0x00BFBDF0 (13 slots): deleting dtor 0x0028CB29, loadPostProcess
// 0x00483CEF (`jmp 0x00497805`), the name getter 0x0028CB23, xfer 0x004DF87C,
// getModuleNameKey 0x0028CADE, then UpdateModule's slots. 0x00BFBDE4: update
// 0x004DF897, then UpdateModule's getDisabledTypesToProcess and wake slots.

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

#include "../../../../Include/GameLogic/Module/ObjectHelper.h"

class ObjectRepulsorHelper : public ObjectHelper
{
public:
	ObjectRepulsorHelper(Thing *thing, const ModuleData *moduleData);
	virtual ~ObjectRepulsorHelper();

	virtual NameKeyType getModuleNameKey() const;
	virtual UpdateSleepTime update();

protected:
	virtual void loadPostProcess();
	virtual const char *GetSnapshotName() const;
	virtual void xfer(Xfer *xfer);
};

// ??0ObjectRepulsorHelper@@QAE@PAVThing@@PBVModuleData@@@Z @0x28CAB4
ObjectRepulsorHelper::ObjectRepulsorHelper(Thing *thing, const ModuleData *moduleData)
	: ObjectHelper(thing, moduleData)
{
}

// Slot 1 of 0x00BFBDF0: 0x00483CEF, `jmp 0x00497805` to ObjectHelper's; the
// body ObjectDefectionHelper, ObjectRecoveryHelper and ObjectWeaponStatusHelper
// share.
void ObjectRepulsorHelper::loadPostProcess()
{
	ObjectHelper::loadPostProcess();
}

// ObjectHelper's xfer, 0x004DF81B, is still rowed under its placeholder class.
#include "../../../../Include/Common/Rva004DF81B.h"

// Slot 3 of 0x00BFBDF0: 0x004DF87C, version 1 then ObjectHelper's xfer; the
// body ObjectRecoveryHelper and ObjectWeaponStatusHelper share.
void ObjectRepulsorHelper::xfer(Xfer *xfer)
{
	xfer->Version1();
	((Rva004DF81B *)this)->xfer(xfer);
}
