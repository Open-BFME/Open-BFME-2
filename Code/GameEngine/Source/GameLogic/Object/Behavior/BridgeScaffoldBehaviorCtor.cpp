// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// ??0BridgeScaffoldBehavior@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x0045831C,
// 141 bytes. Behavior-side ctor (called by the rowed friend_newModuleInstance
// 0x24AC90; class from the ModuleFactory registration literal).
//
// True hierarchy from the ZH header (BridgeScaffoldBehavior.h):
// BridgeScaffoldBehavior : public UpdateModule,
// 			    public BridgeScaffoldBehaviorInterface.
// UpdateModule is 0x20 (sibling UpdateModuleCtor/StructureTopple solution:
// BehaviorModule pair plus UpdateModuleInterface plus three ints); the
// interface subobject carries the fourth vtable slot at +0x20. Its implicit
// inline ctor stores the interface vtable first, then the body assigns the
// target motion (a plain `= STM_STILL` emits the `and [mem],0` idiom, proven
// by probe), stores the derived vtable plus its three shared
// member-subobject vtables explicitly (no virtuals are declared on the
// derived class itself so nothing is auto-emitted; the immediates are
// DIR32-masked in comparison), and assigns the positions and speeds in ZH
// donor order. BFME2 repair: lateral/vertical speeds are copied from a shared
// float global instead of the ZH 1.0f literals. /arch:SSE for the xorps float
// zeros; frameless so no /GX. Zero new pins (base resolves via its row;
// interface so small it inlines).

class Thing;
class ModuleData;
class Object;

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

enum ScaffoldTargetMotion
{
	STM_STILL,
	STM_RISE,
	STM_BUILD_ACROSS,
	STM_TEAR_DOWN_ACROSS,
	STM_SINK,
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
private:
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;
};

class BridgeScaffoldBehaviorInterface
{
public:
	BridgeScaffoldBehaviorInterface() {}
	virtual void setPositions(const Coord3D *createPos, const Coord3D *riseToPos, const Coord3D *buildPos);
	virtual void setMotion(ScaffoldTargetMotion targetMotion);
	virtual ScaffoldTargetMotion getCurrentMotion(void);
	virtual void reverseMotion(void);
	virtual void setLateralSpeed(float lateralSpeed);
	virtual void setVerticalSpeed(float verticalSpeed);
};

class BridgeScaffoldBehavior : public UpdateModule,
			       public BridgeScaffoldBehaviorInterface
{
public:
	BridgeScaffoldBehavior(Thing *thing, const ModuleData *moduleData);

private:
	ScaffoldTargetMotion m_targetMotion;	// +0x24
	Coord3D m_createPos;			// +0x28
	Coord3D m_riseToPos;			// +0x34
	Coord3D m_buildPos;			// +0x40
	float m_lateralSpeed;			// +0x4C
	float m_verticalSpeed;			// +0x50
	Coord3D m_targetPos;			// +0x54
};

// Shared speed default both speeds are copied from. Nothing in the image
// names it; it is reached by what this body reads from it.
extern float TheBridgeScaffoldSpeedDefault;	// 0x00BBB8D8

// ??0BridgeScaffoldBehavior@@QAE@PAVThing@@PBVModuleData@@@Z @0x0045831C
BridgeScaffoldBehavior::BridgeScaffoldBehavior(Thing *thing, const ModuleData *moduleData) :
	UpdateModule(thing, moduleData)
{
	m_targetMotion = STM_STILL;
	*(unsigned int *)this = 0x00C40C54;
	*(unsigned int *)((char *)this + 0x0C) = 0x00C40B98;
	*(unsigned int *)((char *)this + 0x10) = 0x00C40B88;
	*(unsigned int *)((char *)this + 0x20) = 0x00C40B70;
	m_createPos.zero();
	m_riseToPos.zero();
	m_buildPos.zero();
	m_targetPos.zero();
	float defaultSpeed = TheBridgeScaffoldSpeedDefault;
	m_lateralSpeed = defaultSpeed;
	m_verticalSpeed = defaultSpeed;
}
