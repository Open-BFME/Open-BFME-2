// cl: /DNDEBUG /MD
//
// ??0AODCrushCollide@@QAE@PAVThing@@PBVModuleData@@@Z, retail
// 0x004BC00D, 67 bytes. AODCrushCollide behavior ctor over the rowed
// UpdateModule base (0x253390, thing plus data): initializes the
// CrushCollide-interface slot at +0x20 and zeroes +0x24/+0x28/+0x2C, then
// re-stores the primary vtable slot (the behavior vtable 0x00C5A31C) and
// the +0x0C/+0x10/+0x20 secondary slots.
//
// Donor: BFME1 AODCrushCollideConstructor.cpp (three inline-ctor levels;
// the CrushCollide level adds the +0x20 interface slot with +0x24/+0x28/+0x2C
// fields, and AODCrushCollide overwrites all four vtable slots).
// Class identity is the AODCrush retail cluster (pool key rowed at
// 0x004BBF44, name getter at 0x004BBEFD pushing AODCrushCollide, vtable
// 0x00C5A31C installed here and in the thunk at 0x004BBEDD, the instance
// factory at 0x0025101E is the sole raw caller).

static int s_crush20;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

enum NameKeyType
{
	NK_UNKNOWN = 0
};
enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};
enum ObjectID;
class Thing;
class ModuleData;
class Xfer;
class Object;
struct Coord3D;
#include "../../../../Include/GameLogic/Module/BehaviorModule.h"
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

private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_updateState;
};
class __declspec(novtable) CollideModuleInterface
{
public:
	virtual void onCollide(Object *, const Coord3D *, const Coord3D *) = 0;
};
class __declspec(novtable) CrushCollide : public UpdateModule, public CollideModuleInterface
{
public:
	__forceinline CrushCollide(Thing *thing, const ModuleData *moduleData)
		: UpdateModule(thing, moduleData)
	{
		*(const void **)((char *)this + 0x20) = &s_crush20;
		_ReadWriteBarrier();
		m_24 = 0;
		m_28 = (ObjectID)0;
		m_2C = false;
	}

protected:
	unsigned int m_24;
	ObjectID m_28;
	bool m_2C;
};
class AODCrushCollide : public CrushCollide
{
public:
	AODCrushCollide(Thing *thing, const ModuleData *moduleData);
	virtual ~AODCrushCollide();
	virtual NameKeyType getModuleNameKey() const;
	virtual CollideModuleInterface *getCollide() { return this; }
	virtual UpdateSleepTime update();
	virtual void onCollide(Object *, const Coord3D *, const Coord3D *);

protected:
	virtual void xfer(Xfer *xfer);
};

// ??0AODCrushCollide@@QAE@PAVThing@@PBVModuleData@@@Z
AODCrushCollide::AODCrushCollide(Thing *thing, const ModuleData *moduleData)
	: CrushCollide(thing, moduleData)
{
}
