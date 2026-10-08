// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
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
	void zero() { x = 0.0f; y = 0.0f; z = 0.0f; }
};

// Existing retail callee name; this is the PhysicsBehavior receiver at
// 003909FA. Its original method identity is still unresolved.
class Rva003909FAObj
{
public:
	void consume(void *force, int source, int weapon);
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

class Thing;
class ModuleData;
class Rva00390557Template
{
public:
	unsigned char m_pad[0x115];
	unsigned char m_flags115;
};
class Object
{
public:
	void rva0023D3AF(void *frame);
	unsigned char m_pad00[4];
	Rva00390557Template *m_template;
	unsigned char m_pad08[0x38 - 8];
	Coord3D m_position;
	unsigned char m_pad44[0x274 - 0x44];
	Object *m_holder274;
};
#include "../../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

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
protected:
	void setWakeFrame(Object *object, UpdateSleepTime delay);
public:
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
	bool rva003901DA(int option, float strength);
	void rva00390557(const Coord3D *where, float strength, float value44, int value60, int value64);
	void rva00390E36(int source, int weapon);
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

// Native 0x00390557..0x00390601 RET20. BFME1 donor 34f59164f6d1
// PhysicsBehaviorRva0029AB10.cpp supplies the force/wake transition lead.
// Target proves Object holder +0x274, holder template +4 flag byte +0x115
// bit0x20, vectors +0x38/+0x2C, scalar +0x44 and optional +0x60/+0x64.
// The target drops the donor override walk and has two additional optional
// words. Slot0 at the UpdateModuleInterface subobject +0x10 is called twice;
// frame recording and wake use their existing byte-verified target providers.
// The method name, optional word meanings and template flag remain opaque.
void PhysicsBehavior::rva00390557(const Coord3D *where, float strength,
                                float value44, int value60, int value64)
{
	Object *object = m_object;
	Object *holder = object->m_holder274;
	if (holder && !(holder->m_template->m_flags115 & 0x20))
	{
		setWakeFrame(object, UPDATE_SLEEP_FOREVER);
		return;
	}
	m_bfme38 = *where;
	m_bfme2C = object->m_position;
	m_bfme44 = value44;
	if (rva003901DA(1, strength))
	{
		m_bfme50 = 0;
		if (value60) m_bfme60 = value60;
		if (value64) m_bfme64 = value64;
		static_cast<UpdateModuleInterface *>(this)->update();
		m_object->rva0023D3AF(reinterpret_cast<void *>(TheGameLogic->getFrame()));
		static_cast<UpdateModuleInterface *>(this)->update();
		setWakeFrame(m_object, UPDATE_SLEEP_NONE);
	}
}

// BFME1 c1f3b5af79's PhysicsBehaviorApplyZeroMotiveForce.cpp supplies the
// zero-vector wrapper as a semantic lead. BFME2's native 00390E36..00390E61
// instead forwards two stack arguments (RET8) to the existing 003909FA pin.
// The target proves a zero Coord3D and unchanged this, but not the old name.
void PhysicsBehavior::rva00390E36(int source, int weapon)
{
	Coord3D force;
	force.zero();
	reinterpret_cast<Rva003909FAObj *>(this)->consume(&force, source, weapon);
}
