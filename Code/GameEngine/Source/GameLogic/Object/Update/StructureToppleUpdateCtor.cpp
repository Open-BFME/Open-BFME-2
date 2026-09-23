// cl: /O1 /DNDEBUG /MD /GX /arch:SSE
//
// ??0StructureToppleUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail
// 0x004A5556, 182 bytes. Behavior-side ctor completing the
// StructureToppleUpdate file-unit (ModuleData proc/factory rowed at
// 0x4A651B/0x257BE7; behavior factory rowed at 0x24EE07 news 0x58 with this
// pinned 2-arg ctor; poolkey rowed at 0x4A5511).
//
// Donor: Zero Hour StructureToppleUpdate.cpp ctor verbatim
// (reference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/StructureToppleUpdate.cpp:
// delay-burst zero, structural zero, direction zero, frame/state/velocity
// zeros, 0.001 nudge, crushed zero, burst -1, setWakeFrame forever,
// building height from the geometry). BFME2 repairs, all retail-measured:
// - UpdateModule is 0x20 (BehaviorModule pair plus UpdateModuleInterface
//   plus three ints, per UpdateModuleCtor.cpp); DieModuleInterface base at
//   +0x20 (inline empty ctor, virtual onDie) carries the fourth vtable slot.
// - GeometryInfo member at Object+0xA8 (not the ZH +0xAC); the
//   getMaxHeightAbovePosition call resolves via its row at 0x006BD7C0.
// - setWakeFrame resolves via the established UpdateModule pin at
//   0x0044DF71; base UpdateModule ctor via its row at 0x00253390.
// Shape mirrors PoisonedBehaviorCtor.cpp (same bases, /GX, /arch:SSE for the
// xorps float zeros).

class Thing;
class ModuleData;
class Object;
class DamageInfo;

struct Coord2D
{
	float x;
	float y;
};

struct Coord3D
{
	float x;
	float y;
	float z;

	void zero()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}
};

class GeometryInfo
{
public:
	float getMaxHeightAbovePosition() const;
};

class Object
{
public:
	const GeometryInfo &getGeometryInfo(void) const
	{
		return *(const GeometryInfo *)((const char *)this + 0xA8);
	}
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

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

class UpdateModuleInterface
{
public:
	virtual void update();
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
protected:
	void setWakeFrame(Object *obj, unsigned int frame);
	Object *getObject(void) const { return m_object; }
private:
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;
};

class DieModuleInterface
{
public:
	DieModuleInterface() {}
	virtual void onDie(DamageInfo *damageInfo);
};

enum StructureToppleStateType
{
	TOPPLESTATE_STANDING,
	TOPPLESTATE_WAITINGFORTOPPLESTART,
	TOPPLESTATE_TOPPLING,
	TOPPLESTATE_WAITINGFORDONE,
	TOPPLESTATE_DONE
};

class StructureToppleUpdate : public UpdateModule, public DieModuleInterface
{
public:
	StructureToppleUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~StructureToppleUpdate();
private:
	const Object *getObject(void) const { return m_object; }
	unsigned int m_toppleFrame;
	Coord2D m_toppleDirection;
	int m_toppleState;
	float m_toppleVelocity;
	float m_accumulatedAngle;
	float m_structuralIntegrity;
	float m_lastCrushedLocation;
	int m_nextBurstFrame;
	Coord3D m_delayBurstLocation;
	float m_buildingHeight;
};

// ??0StructureToppleUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x004A5556
StructureToppleUpdate::StructureToppleUpdate(Thing *thing, const ModuleData *moduleData) :
	UpdateModule(thing, moduleData),
	m_nextBurstFrame(-1)
{
	m_toppleFrame = 0;
	m_toppleState = TOPPLESTATE_STANDING;
	m_toppleVelocity = 0.0f;
	m_accumulatedAngle = 0.001f;
	m_structuralIntegrity = 0.0f;
	m_lastCrushedLocation = 0.0f;
	m_delayBurstLocation.zero();
	m_toppleDirection.x = m_toppleDirection.y = 0;
	setWakeFrame(const_cast<Object*>(getObject()), UPDATE_SLEEP_FOREVER);
	Object *building = const_cast<Object*>(getObject());
	m_buildingHeight = building->getGeometryInfo().getMaxHeightAbovePosition();
}
