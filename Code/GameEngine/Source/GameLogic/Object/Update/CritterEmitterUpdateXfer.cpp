// cl: /DNDEBUG /MD
//
// ?xfer@CritterEmitterUpdate@@MAEXPAVXfer@@@Z, retail 0x004C8E42, 65 bytes.
// CritterEmitterUpdate xfer (slot 3 offset 0x0C of vtable 0x0085E8E8, same
// primary as rowed ctor 0x004C8D86 and dtor 0x004C8D1B with ??_G 0x004C8DC6):
// base UpdateModule xfer via rowed 0x0044DF9F, IsLightCRC early-out via Xfer
// slot 0x10, Version1 via rowed 0x000053EE, then two bool runs at +0x24/+0x25
// via Xfer slot 0x90. Layout is the rowed dtor TU (real UpdateModule base
// 0x20 plus trailing iface at +0x20 giving +0x24 start) plus the ctor TU's
// m_24/m_25 bytes as bool; donor is BFME1 CritterEmitterUpdateDestructor
// (protected MAE) plus SlowDeathBehaviorXfer slot-3 pattern (Version1 plus
// bool runs, no Version gating).


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

enum NameKeyType
{
	NK_UNKNOWN = 0
};

class Coord3D;

class BehaviorModuleBase
{
public:
	virtual void behaviorModuleBaseAnchor();
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleOther
{
public:
	virtual void behaviorModuleOtherAnchor();
};

class BehaviorModule : public BehaviorModuleBase, public BehaviorModuleOther
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData);
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
	void xfer(Xfer *xfer);
protected:
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;
};

class CritterEmitterUpdateIface
{
public:
	virtual void onCollide(Object *other, const Coord3D *loc, const Coord3D *normal) = 0;
};

class CritterEmitterUpdate : public UpdateModule, public CritterEmitterUpdateIface
{
public:
	CritterEmitterUpdate(Thing *thing, const ModuleData *moduleData);
	virtual NameKeyType getModuleNameKey() const;
	virtual UpdateSleepTime update();
	virtual void onCollide(Object *other, const Coord3D *loc, const Coord3D *normal);
protected:
	virtual ~CritterEmitterUpdate();
	virtual void xfer(Xfer *xfer);
private:
	bool m_24;
	bool m_25;
};

void CritterEmitterUpdate::xfer(Xfer *xfer)
{
	UpdateModule::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	xfer->Version1();
	*xfer == m_24;
	*xfer == m_25;
}
