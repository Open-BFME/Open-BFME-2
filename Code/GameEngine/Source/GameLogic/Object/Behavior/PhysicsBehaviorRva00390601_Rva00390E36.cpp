// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Split from PhysicsBehaviorRva00390601.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
// ?rva00390601@PhysicsBehavior@@QAE?AW4UpdateSleepTime@@XZ @0x00390601 40B. Identity: PhysicsBehavior sleep select via 12B vector at +0x20 size vs +0x5C/+0x58; returns NONE(1) when vector nonempty or flags pass else FOREVER.
// Evidence: caller 0x3913DA; neighbours 0x3901C9/0x390729; same +0x20/+0x58/+0x5C layout as PhysicsBehaviorCtor.
#include <vector>
#include <math.h>

struct Gen_p12pod
{
	int a[3];
};

// Coord3D: shared header/view; no private copy.
#define COORD3D_VIEW_INLINE
#include "../../../../../Libraries/Include/Lib/Coord3DCtorView.h"

// Existing retail callee name; this is the PhysicsBehavior receiver at
// 003909FA. Its original method identity is still unresolved.
class Rva003909FAObj
{
public:
	void consume(void *force, int source, int weapon);
	void *m_vtbl;
	const struct Rva003909FAModuleData *m_moduleData;
	class Object *m_object;
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
class Rva00390533Conditions {
public: unsigned char test(unsigned bit) const { return (words[bit>>5] >> (bit&31))&1; }
unsigned words[19];
};
enum ObjectStatusTypes { OBJECT_STATUS_RVA_46 = 0x46 };
enum CommandSourceType { CMD_FROM_RVA_2 = 2 };
enum PathfindLayerEnum { LAYER_INVALID = 0, LAYER_GROUND = 1 };

class AICommandInterface
{
public:
	void aiIdle(CommandSourceType cmdSource);	// row 0x001E8A38
};

// Native 003909FA calls vtable slot 91 (+0x16C) on Object+0x258 and then the
// AICommandInterface at +0x20 of the same object.
template<int N> struct Rva003909FASlotTag {};
template<int N> class Rva003909FASlots : public Rva003909FASlots<N - 1>
{
public:
	virtual void unknownSlot(Rva003909FASlotTag<N> *);
};
template<> class Rva003909FASlots<0> {};
class AIUpdateInterface : public Rva003909FASlots<91>
{
public:
	virtual bool slot16C();
	void rva0026331C();	// row 0x0026331C
	unsigned char m_pad04[0x20 - 4];
	AICommandInterface m_commands;
};

class Object
{
public:
	void rva0023D3AF(void *frame);
	bool testStatus(ObjectStatusTypes status) const;	// row 0x0004E536
	void rva00293105();	// row 0x00293105
	int rva0028B511() const;	// row 0x0028B511
	const Coord3D *getPosition() const { return &m_position; }
	unsigned char m_pad00[4];
	Rva00390557Template *m_template;
	unsigned char m_pad08[0x38 - 8];
	Coord3D m_position;
	unsigned char m_pad44[0x10C - 0x44];
 Rva00390533Conditions m_conditions;
 unsigned char m_pad158[0x258-0x158];
	AIUpdateInterface *m_ai258;
	unsigned char m_pad25C[0x274-0x25C];
	Object *m_holder274;
};

class TerrainLogic
{
public:
	virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0C();
	virtual void s10(); virtual void s14(); virtual void s18();
	virtual float getLayerHeight(float x, float y, PathfindLayerEnum layer, Coord3D *normal, bool clip);
	PathfindLayerEnum getLayerForDestination(Object *obj, const Coord3D *pos);	// row 0x002802FE
};
extern TerrainLogic *TheTerrainLogic;
class GlobalData;
extern GlobalData *TheWritableGlobalData;
struct Rva003909FAGlobalDataView { unsigned char m_pad[0xC4]; float m_gravity; };
extern int BfmeLogicFramesPerSecond;
class Pathfinder
{
public:
	void AdjustFlingDestination(Object *obj, const Coord3D *from, Coord3D *to);	// row 0x002EE4DE
};
class AI;
extern AI *TheAI;
struct Rva003909FAAIView { unsigned char m_pad[0x10]; Pathfinder *m_pathfinder; };
struct Rva003909FAModuleData { unsigned char m_pad[0x4C]; float m_factor; };

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
	friend class Rva003909FAObj;
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
	bool calcFlightPath(bool option, float strength);	// row 0x003901DA
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


// Retail 0x00003571 (coord3d.cpp): visible here so the compiler knows
// length() keeps no pointer to its object.
inline __declspec(noinline) float Coord3D::length() const
{
	return (float)sqrt(x * x + y * y + z * z);
}

void Rva003909FAObj::consume(void *forceArg, int source, int weapon)
{
	const Coord3D *force = (const Coord3D *)forceArg;
	const Rva003909FAModuleData *moduleData = m_moduleData;
	Object *obj = m_object;
	if (obj->m_holder274 && !(obj->m_holder274->m_template->m_flags115 & 0x20))
	{
		((UpdateModule *)this)->setWakeFrame(obj, UPDATE_SLEEP_FOREVER);
		return;
	}
	if (obj->testStatus(OBJECT_STATUS_RVA_46))
		obj->rva00293105();
	AIUpdateInterface *ai = obj->m_ai258;
	if (ai && !ai->slot16C())
	{
		ai->rva0026331C();
		ai->m_commands.aiIdle(CMD_FROM_RVA_2);
	}
	((UpdateModule *)this)->setWakeFrame(obj, UPDATE_SLEEP_NONE);

	Coord3D pos = *obj->getPosition();
	float height = pos.z - TheTerrainLogic->getLayerHeight(pos.x, pos.y,
		(PathfindLayerEnum)obj->rva0028B511(), 0, true);
	if (height < 0.0f)
		height = 0.0f;
	int maxFrames = 3 * BfmeLogicFramesPerSecond;
	float sim = height;
	int i;
	for (i = 0; i < maxFrames && sim > 0.0f; ++i)
		sim += moduleData->m_factor * ((Rva003909FAGlobalDataView *)TheWritableGlobalData)->m_gravity * i;
	float vz = force->z;
	if (force->length() * 0.25f > vz && i < 2)
		vz = force->length() * 0.25f;
	unsigned duration = (unsigned)fabs(2.0f * vz /
		(moduleData->m_factor * ((Rva003909FAGlobalDataView *)TheWritableGlobalData)->m_gravity));
	if (duration < 1)
		duration = 1;
	duration += i;
	float peak = (vz * 0.5f) * ((float)duration * 0.5f);
	if (peak < 0.0f)
		peak = 0.0f;
	Coord3D delta = *force;
	delta.z = 0.0f;
	delta.scaleInlined((float)duration);
	Coord3D dest;
	dest = *obj->getPosition();
	dest.add(&delta);
	((Rva003909FAAIView *)TheAI)->m_pathfinder->AdjustFlingDestination(obj, obj->getPosition(), &dest);
	dest.z += 10.0f;
	dest.z = TheTerrainLogic->getLayerHeight(dest.x, dest.y,
		TheTerrainLogic->getLayerForDestination(0, &dest), 0, true);
	float speed = (delta.length() + 2.0f * peak + height) / (float)duration;
	float minSpeed = -((Rva003909FAGlobalDataView *)TheWritableGlobalData)->m_gravity;
	if (speed < minSpeed)
		speed = minSpeed;
	((PhysicsBehavior *)this)->rva00390557(&dest, peak, speed, source, weapon);
}

// Receiver comes from Object+25C; native 390533..390557 reads its Object+8.
// Condition-array base10C is established independently by rowed setters.
// BFME1 c1f3b5af79 clean29A7D0 accessor supplies the unsigned-shift shape.
class Rva00390533 { public: bool rva00390533(); char pad[8];Object *m_object; };

