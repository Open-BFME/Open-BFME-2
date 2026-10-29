// cl: /DNDEBUG /MD /GX
// ?getModuleNameKey@HitReactionBehavior@@UBE?AW4NameKeyType@@XZ @0x4591a5
// (69B): cached pool-name key for HitReactionBehavior. The class
// identity comes from the pool-name string the body pushes
// ("HitReactionBehavior"); the body guards a function-local static
// key fetched once through TheNameKeyGenerator. It is NOT getClassMemoryPool:
// retail stores nameToKey's return (a key, not a pool pointer) and returns it,
// and the address carries no getClassMemoryPool row anywhere. /EHsc for the
// static-guard EH prologue; globals are TU-local externs (DIR32 slots patch
// from retail, no pins; nameToKey resolves via its matched row).

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

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

// ?getModuleNameKey@HitReactionBehavior@@UBE?AW4NameKeyType@@XZ
NameKeyType HitReactionBehavior::getModuleNameKey() const
{
	static NameKeyType TheHitReactionBehaviorPoolKey =
		TheNameKeyGenerator->nameToKey("HitReactionBehavior");
	return TheHitReactionBehaviorPoolKey;
}

