// cl: /DNDEBUG /MD
//
// ?xfer@PartTheHeavensUpdate@@MAEXPAVXfer@@@Z, retail 0x004ACAAA, 48 bytes.
// Slot 3 (offset 0x0C) of vtable 0x00854DA4 (PartTheHeavensUpdate, same
// primary as rowed ctor 0x004AC998 and dtor 0x004AC8EF); ICF twin slot 3 of
// 0x0084F55C (Rva0049669A opaque). Base UpdateModule xfer via rowed
// 0x0044DF9F, IsLightCRC early-out via Xfer slot 0x10, Version1 via rowed
// 0x000053EE, then uint at +0x20 via Xfer slot 0x78. Layout is the rowed
// 0x28-byte class (UpdateModule base 0x20 plus frame at +0x20 plus pointee
// at +0x24, see ctor 0x004AC998 and dtor 0x004AC8EF); only the frame is
// xferred. Recipe is the DestroyEnvironmentUpdateXfer slot-3 pattern
// without the ObjectID tail.

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;
class Thing;
class ModuleData;
class Object;

#include "../../../../Include/Common/BfmeXfer.h"

#include "../../../../Include/Common/ObjectModule.h"

#include "../../../Common/GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

enum NameKeyType
{
	NK_UNKNOWN = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class BehaviorModuleInterface
{
public:
	virtual void behaviorSlot();
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};

class UpdateModule : public ObjectModule,
	public BehaviorModuleInterface, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
	void xfer(Xfer *xfer);

protected:
	virtual void loadPostProcess();

private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_updateState;
};

class PartTheHeavensUpdatePointee
{
public:
	virtual void pointeeSlot0();
	virtual void pointeeSlot1();
	virtual void releasePointee();
};

class PartTheHeavensUpdate : public UpdateModule
{
public:
	PartTheHeavensUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~PartTheHeavensUpdate();
	virtual NameKeyType getModuleNameKey() const;
	virtual UpdateSleepTime update();

protected:
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess();

private:
	void rva004AC9FA(int elapsed);
	void rva004ACADA();

	unsigned int m_startFrame;	// +0x20
	PartTheHeavensUpdatePointee *m_pointee;	// +0x24
};

void PartTheHeavensUpdate::xfer(Xfer *xfer)
{
	UpdateModule::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	xfer->Version1();
	*xfer == m_startFrame;
}
