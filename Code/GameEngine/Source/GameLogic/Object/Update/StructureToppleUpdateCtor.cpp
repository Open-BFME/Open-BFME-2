// cl: /DNDEBUG /MD /GX /Ireference/shims/update_modules_bfme2
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

#include "../../../../../Libraries/Include/Lib/Coord2D.h"

#include "../../../../../Libraries/Include/Lib/Coord3D.h"

// Retail inlines these three zero stores; the canonical Coord3D::zero is the out-of-line owner.
static inline void zeroInline(Coord3D &c) { c.x = 0.0f; c.y = 0.0f; c.z = 0.0f; }

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

#include "../../../../Include/GameLogic/Module/UpdateModule.h"
#include "../../../../Include/GameLogic/Module/DieModuleInterface.h"

#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_REFERENCE_XFER
#define BFME_SNAPSHOT_NONCONST_NAME_SLOT
#include "../../../../Include/Common/Geometry.h"

class Object
{
public:
	const GeometryInfo &getGeometryInfo(void) const
	{
		return *(const GeometryInfo *)((const char *)this + 0xA8);
	}
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
	// Retail's dtor 0x004A54A8 stores the four vptrs this ctor installs
	// and tail-jumps UpdateModule::~UpdateModule.
	virtual ~StructureToppleUpdate();
	virtual void onDie(const DamageInfo *damageInfo);
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
public:
	// retail slot 4: the rowed ?getModuleNameKey@StructureToppleUpdate@@UBE?AW4NameKeyType@@XZ
	virtual NameKeyType getModuleNameKey() const;
protected:
	virtual void loadPostProcess();	// primary slot 1 (0x00497805; StructureToppleUpdate.cpp)
	// retail vftable slot: the rowed override
	virtual const char * GetSnapshotName() const;
protected:
	// retail vftable slot: the rowed override
	virtual void xfer(Xfer *);
public:
	// retail vftable slot: the rowed override
	virtual UpdateSleepTime update();
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
	zeroInline(m_delayBurstLocation);
	m_toppleDirection.x = m_toppleDirection.y = 0;
	setWakeFrame(const_cast<Object*>(getObject()), (UpdateSleepTime)UPDATE_SLEEP_FOREVER);
	Object *building = const_cast<Object*>(getObject());
	m_buildingHeight = building->getGeometryInfo().getMaxHeightAbovePosition();
}
