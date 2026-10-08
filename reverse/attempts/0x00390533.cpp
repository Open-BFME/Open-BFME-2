// ?rva00390533@Rva00390533@@QAE_NXZ
// partial score=0.94 date=2026-10-08
// cl: /DNDEBUG /MD /arch:SSE /Oy- /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva00390601@PhysicsBehavior@@QAE?AW4UpdateSleepTime@@XZ @0x00390601 40B. Identity: PhysicsBehavior sleep select via 12B vector at +0x20 size vs +0x5C/+0x58; returns NONE(1) when vector nonempty or flags pass else FOREVER.
// Evidence: caller 0x3913DA; neighbours 0x3901C9/0x390729; same +0x20/+0x58/+0x5C layout as PhysicsBehaviorCtor.
#include <vector>
#include "../../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

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
// Target 00390557 reads the optional module at Object+274 and its data
// pointer at +4. Bit 5 of data+115 permits this transition. The meaning of
// that bit and the module's original type are not established by the donor.
struct Rva00390557ModuleData
{
	unsigned char m_pad00[0x115];
	unsigned char m_flags115;
};
struct Rva00390557Module
{
	void *m_vptr;
	Rva00390557ModuleData *m_data;
};
class Rva00390533Conditions
{
public:
	unsigned char test(unsigned int bit) const
	{
		return (m_words[bit >> 5] >> (bit & 31)) & 1;
	}
private:
	unsigned int m_words[19];
};
class Object
{
public:
	void rva0023D3AF(void *frame);
	unsigned char m_pad00[0x38];
	Coord3D m_position;
	unsigned char m_pad44[0x10C - 0x44];
	Rva00390533Conditions m_conditions;
	unsigned char m_pad158[0x274 - 0x158];
	Rva00390557Module *m_module274;
};

// Preserve the existing native callee pin's owner spelling. Retail callers
// obtain this receiver from Object+25C; native 00390533 reads its Object+8.
class Rva00390533
{
public:
	bool rva00390533();
private:
	unsigned char m_pad00[8];
	Object *m_object;
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
	void setWakeFrame(Object *object, UpdateSleepTime when);
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
	bool rva003901DA(bool option, float strength);
	void rva00390557(const Coord3D *where, float strength, float field44, int field60, int field64);
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

// BFME1 c1f3b5af79c6e982e4f2934bdb840a4483c59fa9's clean
// PhysicsBehaviorRva0029AB10.cpp is the semantic lead: target/original
// positions, flight helper, two interface calls around the frame snapshot,
// and wake setter. Retail 00390557..00390601 proves thiscall RET20, the
// existing +2C/+38/+44/+50 layout, and conditional stores to +60/+64.
// Its optional Object+274 module replaces the donor's contained-by test;
// 0023D3AF is the rowed Object snapshot, not the donor's Drawable spelling.
// Method and extra-field identities remain address-derived.
void PhysicsBehavior::rva00390557(const Coord3D *where, float strength, float field44, int field60, int field64)
{
	Object *object = m_object;
	Rva00390557Module *module = object->m_module274;
	if (module != 0 && (module->m_data->m_flags115 & 0x20) == 0)
	{
		setWakeFrame(object, UPDATE_SLEEP_FOREVER);
		return;
	}
	m_bfme38 = *where;
	m_bfme2C = object->m_position;
	m_bfme44 = field44;
	if (rva003901DA(true, strength))
	{
		m_bfme50 = 0;
		if (field60 != 0)
			m_bfme60 = field60;
		if (field64 != 0)
			m_bfme64 = field64;
		UpdateModuleInterface *interface = this;
		interface->update();
		m_object->rva0023D3AF(reinterpret_cast<void *>(TheGameLogic->getFrame()));
		interface->update();
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

// Native 00390533..00390557: bool thiscall, bit31 of Object+118 OR bit8
// of Object+114. The condition word base +10C is independently established
// by matched PhysicsBehavior flag setters. BFME1 c1f3b5af79's 29A7D0
// supplies the native STL bitset accessor shape; names of these bits remain
// unresolved. This replaces the old direct-mask attempt with that accessor.
// ?Rva00390533::rva00390533 present-unmatched
bool Rva00390533::rva00390533()
{
	return m_object->m_conditions.test(3 * 32 + 31) ||
		m_object->m_conditions.test(2 * 32 + 8);
}
