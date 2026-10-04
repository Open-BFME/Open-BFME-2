// cl: /O1 /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva00390601@PhysicsBehavior@@QAE?AW4UpdateSleepTime@@XZ @0x00390601 40B. Identity: PhysicsBehavior sleep select via 12B vector at +0x20 size vs +0x5C/+0x58; returns NONE(1) when vector nonempty or flags pass else FOREVER.
// Evidence: caller 0x3913DA; neighbours 0x3901C9/0x390729; same +0x20/+0x58/+0x5C layout as PhysicsBehaviorCtor.
#include <vector>

struct Gen_p12pod
{
	int a[3];
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

class Thing;
class ModuleData;
class Object;

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
private:
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;
};

class PhysicsBehavior : public UpdateModule
{
public:
	PhysicsBehavior(Thing *thing, const ModuleData *moduleData);
	virtual ~PhysicsBehavior();
	UpdateSleepTime rva00390601();
	bool rva0039051E() const;
private:
	_STL::vector<Gen_p12pod> m_elements;
	Coord3D m_bfme2C;
	Coord3D m_bfme38;
	float m_bfme44;
	float m_bfme48;
	int m_bfme4C;
	int m_bfme50;
	int m_bfme54;
	int m_bfme58;
	bool m_bfme5C;
	unsigned char m_bfme5D;
	bool m_bfme5E;
	bool m_bfme5F;
	int m_bfme60;
	int m_bfme64;
};

UpdateSleepTime PhysicsBehavior::rva00390601()
{
	if (m_elements.size() > 0)
		return UPDATE_SLEEP_NONE;
	if (m_bfme5C && m_bfme58 > 0)
		return UPDATE_SLEEP_NONE;
	return UPDATE_SLEEP_FOREVER;
}

// BFME1 donor1281192f68 Bfme5TinyTwentyFive.cpp /O1 supplies the unsigned
// size comparison. Target Ghidra0039051E/21B proves the +20/+24 pointer
// difference divided by12. Retail caller0045DD60 obtains this from Object
// +25C and tests AL, supporting the existing PhysicsBehavior view and a
// bool result. Constness is a donor/source inference; the method name is
// unknown. The old int-return bank missed this compiler shape.
bool PhysicsBehavior::rva0039051E() const
{
	return m_elements.size() > 0;
}
