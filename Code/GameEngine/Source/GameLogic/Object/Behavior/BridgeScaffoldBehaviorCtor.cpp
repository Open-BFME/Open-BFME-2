// cl: /DNDEBUG /MD
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

extern "C" const void *const vtbl_00C40B70[];  // ??_7Rva00458402@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C40B70=??_7Rva00458402@@6B@")
extern "C" const void *const vtbl_00C40B88[];  // ??_7Rva00458402@@6BRva0024A797_B2@@@
#pragma comment(linker, "/alternatename:_vtbl_00C40B88=??_7Rva00458402@@6BRva0024A797_B2@@@")
extern "C" const void *const vtbl_00C40B98[];  // ??_7Rva00458402@@6BRva0024A797_Mid@@@
#pragma comment(linker, "/alternatename:_vtbl_00C40B98=??_7Rva00458402@@6BRva0024A797_Mid@@@")
extern "C" const void *const vtbl_00C40C54[];  // ??_7Rva00458402@@6BRva0024A797_Root@@@
#pragma comment(linker, "/alternatename:_vtbl_00C40C54=??_7Rva00458402@@6BRva0024A797_Root@@@")

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
	virtual void setPositions(const Coord3D *createPos, const Coord3D *riseToPos, const Coord3D *buildPos) = 0;
	virtual void setMotion(ScaffoldTargetMotion targetMotion) = 0;
	virtual ScaffoldTargetMotion getCurrentMotion(void) = 0;
	virtual void reverseMotion(void) = 0;
	virtual void setLateralSpeed(float lateralSpeed) = 0;
	virtual void setVerticalSpeed(float verticalSpeed) = 0;
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

// ??0BridgeScaffoldBehavior@@QAE@PAVThing@@PBVModuleData@@@Z @0x0045831C
BridgeScaffoldBehavior::BridgeScaffoldBehavior(Thing *thing, const ModuleData *moduleData) :
	UpdateModule(thing, moduleData)
{
	m_targetMotion = STM_STILL;
	*(unsigned int *)this = ((unsigned int)vtbl_00C40C54);
	*(unsigned int *)((char *)this + 0x0C) = ((unsigned int)vtbl_00C40B98);
	*(unsigned int *)((char *)this + 0x10) = ((unsigned int)vtbl_00C40B88);
	*(unsigned int *)((char *)this + 0x20) = ((unsigned int)vtbl_00C40B70);
	m_createPos.zero();
	m_riseToPos.zero();
	m_buildPos.zero();
	m_targetPos.zero();
	float defaultSpeed = 1.0f;
	m_lateralSpeed = defaultSpeed;
	m_verticalSpeed = defaultSpeed;
}
