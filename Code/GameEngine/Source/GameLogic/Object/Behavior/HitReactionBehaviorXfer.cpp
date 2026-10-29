// cl: /DNDEBUG /MD /GX
//
// ?xfer@HitReactionBehavior@@MAEXPAVXfer@@@Z, retail 0x00459173, 50 bytes.
// Slot 3 (offset 0x0C) of vtable 0x00841004: Version1 via rowed 0x000053EE,
// base UpdateModule xfer via rowed 0x0044DF9F, then float at +0x24 via Xfer
// slot 0x70 plus int at +0x20 via Xfer slot 0x7C. Layout is the rowed
// HitReactionBehavior class (int m_framesLeft plus float m_lastHealth); donor is BFME1
// HitReactionBehavior ctor (m_field20 plus m_field24).

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

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

#include "../../../../Include/Common/ObjectModule.h"

class BehaviorModuleInterface { public: virtual void behaviorSlot(); };

class UpdateModuleInterface { public: virtual UpdateSleepTime update(); };

// UpdateModule base; ctor and xfer resolve to their rows. The update()
// override runs on the UpdateModuleInterface subobject at +0x10.
class UpdateModule : public ObjectModule,
	public BehaviorModuleInterface, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *data);
	virtual ~UpdateModule();
	void xfer(Xfer *xfer);

protected:
	void setWakeFrame(Object *obj, UpdateSleepTime frame);
	Object *getObject() const { return m_object; }
	const ModuleData *getModuleData() const { return m_moduleData; }

private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_updateState;
};

class HitReactionBehavior : public UpdateModule
{
public:
	HitReactionBehavior(Thing *thing, const ModuleData *moduleData);
	virtual ~HitReactionBehavior();
	virtual NameKeyType getModuleNameKey() const;
	virtual UpdateSleepTime update();

protected:
	virtual void xfer(Xfer *xfer);

private:
	int m_framesLeft; // +0x20
	float m_lastHealth; // +0x24
};

void HitReactionBehavior::xfer(Xfer *xfer)
{
	xfer->Version1();
	UpdateModule::xfer(xfer);
	*xfer == m_lastHealth;
	*xfer == m_framesLeft;
}
