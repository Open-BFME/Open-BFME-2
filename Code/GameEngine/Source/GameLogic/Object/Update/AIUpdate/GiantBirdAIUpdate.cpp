// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /MD /EHsc /DNDEBUG /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// platformsdk
//
// ?update@GiantBirdAIUpdate@@UAE?AW4UpdateSleepTime@@XZ, retail
// 0x0036B103..0x0036B567 (1124 bytes). WB 0x00F38A40 is the same body, the
// only WB caller of the grab toss below. Object::GetRelativeAngle is
// written inline in the class with its full body (WB: Object.h inline);
// cl still calls 0x000B4542 but knows &prev is not captured, and the
// emitted COMDAT is the matched 273-byte body, select-any like the copy in
// ObjectGetRelativeAngle.cpp. prev is copied member-wise, and the unit
// direction pos lives in its own block that ends after normalize() (WB
// copy-constructs pos and prev; retail drops WB's scale of pos).
//
// ?rva0036AE79@GiantBirdAIUpdate@@QAEXXZ, retail 0x0036AE79..0x0036B103
// (650 bytes, EH): the grab toss of the giant bird, called only from the
// GiantBirdAIUpdate::update body below (call at 0x0036B1A9).
//
// Target facts: this is the GiantBirdAIUpdate primary (+0x4B8 flag word
// whose bit 6 onCollide also tests, +0x4BC timer, +0x4C0 and +0x4C4 words
// the constructor zeroes, +0x538 real, +0x30 state machine, +0x1F0 pointer).
// While bit 6 is set and the Object's contain module (+0x250) holds riders
// (slot 69, getContainCount), the timer advances by 1 / logic frame rate.
// When GrabTossTimeTrigger (module data +0x6C) is positive and exceeded,
// or GrabTossHeightTrigger (+0x70, compared as a double) is positive and
// the height above terrain exceeds it, bit 6 is cleared and the contained
// list (slot 70 by value, then the rowed 0x0036AE51) is searched for the
// rider whose Object +0x74 word equals +0x4C4. That rider is removed from
// the container (slot 41, false) and turned to the bird's Z rotation; the
// state machine's slot 14 gets 0. With a rider physics module (+0x25C) and
// a +0x1F0 pointer, the bird's unit direction scaled by half +0x538, with z
// -6, goes to the pinned 0x003909FA (vector, 0, 0) and the rowed
// PhysicsBehavior::rva00390629(true); TossFX (+0x80) plays on the rider and
// the bird, and with bit 8 the pinned 0x00294D61 reports the rider and sets
// physics byte +0x5F. Then model condition bit 72 (the Object +0x10C
// words; notifier 0x0028AE6D), setStatus(0x3C, false), and unless the
// rider's template has KindOf bit 0x5A its body (+0x254) slot 33
// (setIndestructible) gets false.
// The timer otherwise resets when no riders remain.
//
// Identity: the module data field names come from the GiantBirdAIUpdate
// field parse table 0x00C178D8; the function name is address-derived (WB
// 0x00F3B0A0 is the same body, unnamed). The other field names and the
// slot meanings are structural inferences.
#include <math.h>
#include "../../../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../../../Include/GameLogic/ContainmentListView.h"
#include "../../../../../Include/GameLogic/BfmeStoredAICommandView.h"

namespace _STL {template<> _List_base<Rva0036ADF9Element,allocator<Rva0036ADF9Element> >::~_List_base();}

typedef bool Bool;
typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;

extern int BfmeLogicFramesPerSecond;

#include <windows.h>
// Retail update uses a direct free call; the /MD CRT declaration changes it
// to an indirect IAT call and grows the matched body by one byte.
extern "C" void __cdecl free(void *p);

inline void scaleCoord(Coord3D &c, Real s)
{
	c.x *= s;
	c.y *= s;
	c.z *= s;
}

inline void setCoord(Coord3D &c, const Coord3D &a)
{
	c.x = a.x;
	c.y = a.y;
	c.z = a.z;
}

inline void addCoord(Coord3D &c, const Coord3D &a)
{
	c.x += a.x;
	c.y += a.y;
	c.z += a.z;
}

inline void subCoord(Coord3D &c, const Coord3D &a)
{
	c.x -= a.x;
	c.y -= a.y;
	c.z -= a.z;
}

inline void zeroCoord(Coord3D &c)
{
	c.x = 0.0f;
	c.y = 0.0f;
	c.z = 0.0f;
}

Real normalizeAngle(Real angle);

// The scratch mask the GiantBird movement helpers pass along (data row).
extern unsigned char g_00E01EC4[4];

enum ObjectStatusTypes
{
	OBJECT_STATUS_BFME_06 = 0x06,
	OBJECT_STATUS_BFME_3C = 0x3C,
	OBJECT_STATUS_BFME_48 = 0x48
};
enum { BFME_MODELCONDITION_72 = 2 * 32 + 8, BFME_MODELCONDITION_103 = 3 * 32 + 7 };

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

enum AICommandType { AICMD_NO_COMMAND = -1 };
enum CommandSourceType { CMD_FROM_AI = 2 };

#define INVALID_STATE_ID 999999

class FXList;
class Object;

class FXList
{
public:
	static void doFXObj(const FXList *fx, const Object *primary, const Object *secondary);
};

class Matrix3D
{
public:
	Real Get_Z_Rotation() const;
private:
	Real Row[3][4];
};

class ThingTemplateView
{
public:
	Bool isKindOf5A() const { return (m_kindOf[0x5A >> 3] & (1 << (0x5A & 7))) != 0; }
private:
	unsigned char m_pad000[0x108];
	unsigned char m_kindOf[0x20]; // +0x108
};

extern Real ACos(Real);
class Thing
{
public:
	Bool isAboveTerrain() const;
	Real getHeightAboveTerrain() const;
	void setOrientation(Real angle);
	void getUnitDirectionVector3D(Coord3D &dir) const;
	const Coord3D *getUnitDirectionVector2D() const;
	void setPositionZ(Real z);
	const ThingTemplateView *getTemplate() const { return m_template; }
	const Matrix3D *getTransformMatrix() const { return &m_transform; }
	const Coord3D *getPosition() const { return &m_cachedPos; }
	Real getOrientation() const { return m_cachedAngle; }
private:
	void *m_vptr;
	const ThingTemplateView *m_template; // +0x04
	Matrix3D m_transform; // +0x08
	Coord3D m_cachedPos; // +0x38
	Real m_cachedAngle; // +0x44
};

class BodyModuleInterface
{
public:
	virtual void gap00(); virtual void gap01(); virtual void gap02(); virtual void gap03();
	virtual void gap04(); virtual void gap05(); virtual void gap06(); virtual void gap07();
	virtual void gap08(); virtual void gap09(); virtual void gap10(); virtual void gap11();
	virtual void gap12(); virtual void gap13(); virtual void gap14(); virtual void gap15();
	virtual void gap16(); virtual void gap17(); virtual void gap18(); virtual void gap19();
	virtual void gap20(); virtual void gap21(); virtual void gap22(); virtual void gap23();
	virtual void gap24(); virtual void gap25(); virtual void gap26(); virtual void gap27();
	virtual void gap28(); virtual void gap29(); virtual void gap30(); virtual void gap31();
	virtual void gap32();
	virtual void setIndestructible(Bool indestructible) = 0; // +0x84
};

class ContainModuleInterface
{
public:
	virtual void gap00(); virtual void gap01(); virtual void gap02(); virtual void gap03();
	virtual void gap04(); virtual void gap05(); virtual void gap06(); virtual void gap07();
	virtual void gap08(); virtual void gap09(); virtual void gap10(); virtual void gap11();
	virtual void gap12(); virtual void gap13(); virtual void gap14(); virtual void gap15();
	virtual void gap16(); virtual void gap17(); virtual void gap18(); virtual void gap19();
	virtual void gap20(); virtual void gap21(); virtual void gap22(); virtual void gap23();
	virtual void gap24(); virtual void gap25(); virtual void gap26(); virtual void gap27();
	virtual void gap28(); virtual void gap29(); virtual void gap30(); virtual void gap31();
	virtual void gap32(); virtual void gap33(); virtual void gap34(); virtual void gap35();
	virtual void gap36(); virtual void gap37(); virtual void gap38(); virtual void gap39();
	virtual void gap40();
	virtual void removeFromContain(Object *obj, Bool exposeStealthUnits) = 0; // +0xA4
	virtual void gap42(); virtual void gap43(); virtual void gap44(); virtual void gap45();
	virtual void gap46(); virtual void gap47(); virtual void gap48(); virtual void gap49();
	virtual void gap50(); virtual void gap51(); virtual void gap52(); virtual void gap53();
	virtual void gap54(); virtual void gap55(); virtual void gap56(); virtual void gap57();
	virtual void gap58(); virtual void gap59(); virtual void gap60(); virtual void gap61();
	virtual void gap62(); virtual void gap63(); virtual void gap64(); virtual void gap65();
	virtual void gap66(); virtual void gap67(); virtual void gap68();
	virtual UnsignedInt getContainCount(Int unused) const = 0; // +0x114
	virtual Rva0036AE51ListView getContainedItemsView() = 0; // +0x118
};

class PhysicsBehavior
{
public:
	void rva00390629(Bool flag);
	void setFlag5F() { m_5F = true; }
private:
	unsigned char m_pad00[0x5F];
	Bool m_5F; // +0x5F
};

// The pinned owner names of 0x003909FA and 0x00294D61.
class Rva003909FAObj { public: void consume(void *force, Int a, Int b); };
class Rva00294D61 { public: void report(Object *victim, Int flag); };

class ModelConditionFlags
{
public:
	unsigned int test(unsigned int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void set(unsigned int bit)
	{
		m_words[bit >> 5] |= 1U << (bit & 0x1f);
	}
private:
	unsigned int m_words[19];
};

class Object : public Thing
{
public:
	UnsignedInt getID() const { return m_id; }
	void rva0028AE6D();
	__forceinline void setModelConditionState(unsigned int bit)
	{
		if (!m_modelConditionFlags.test(bit))
		{
			m_modelConditionFlags.set(bit);
			rva0028AE6D();
		}
	}
	void setStatus(ObjectStatusTypes status, Bool set);
	Real GetRelativeAngle(const Coord3D *pos) const
	{
		Coord3D delta;
		delta.x = pos->x - getPosition()->x;
		delta.y = pos->y - getPosition()->y;
		Real distance = (Real)sqrt(delta.x * delta.x + delta.y * delta.y);
		if (distance == 0.0f)
			return 0.0f;
		Coord3D *dir = &delta;
		Real scale = 1.0f / distance;
		dir->x *= scale;
		dir->y *= scale;
		const Coord3D *facing = getUnitDirectionVector2D();
		Real cosine = delta.x * facing->x;
		cosine += delta.y * facing->y;
		if (cosine < -1.0)
			cosine = -1.0f;
		else if (cosine > 1.0)
			cosine = 1.0f;
		Real angle = ACos(cosine);
		if (delta.y * facing->x - delta.x * facing->y < 0.0f)
			angle = -angle;
		return angle;
	}
	Bool isEffectivelyDead() const { return (m_privateStatus & 1) != 0; }
	ContainModuleInterface *getContain() const { return m_contain; }
	BodyModuleInterface *getBodyModule() const { return m_body; }
	PhysicsBehavior *getPhysics() const { return m_physics; }
private:
	unsigned char m_pad048[0x74 - 0x48];
	UnsignedInt m_id; // +0x74
	unsigned char m_pad078[0x10C - 0x78];
	ModelConditionFlags m_modelConditionFlags; // +0x10C
	unsigned char m_pad158[0x250 - 0x158];
	ContainModuleInterface *m_contain; // +0x250
	BodyModuleInterface *m_body; // +0x254
	void *m_ai; // +0x258
	PhysicsBehavior *m_physics; // +0x25C
	unsigned char m_pad260[0x438 - 0x260];
	unsigned char m_privateStatus; // +0x438
};

// Sets a status on the Object for the lifetime of the scope (WB 0x00E414C0
// and 0x00E41500, inlined in retail); the name is a structural inference.
class ObjectStatusScope
{
public:
	__forceinline ObjectStatusScope(Object *obj, ObjectStatusTypes status) : m_obj(obj), m_status(status)
	{
		m_obj->setStatus(m_status, true);
	}
	__forceinline ~ObjectStatusScope()
	{
		m_obj->setStatus(m_status, false);
	}
private:
	Object *m_obj;
	ObjectStatusTypes m_status;
};

class AiOrdersManager
{
public:
	void rva003551D3(int value);
};
extern AiOrdersManager *TheAiOrdersManager;

struct AICommandParms
{
	AICommandParms(AICommandType cmd, CommandSourceType cmdSource); // 0x00351BD0
	~AICommandParms() { if (m_coordsStart) free(m_coordsStart); }

	AICommandType m_cmd; // +0x00
	CommandSourceType m_cmdSource; // +0x04
	Coord3D m_pos; // +0x08
	Object *m_obj; // +0x14
	Object *m_otherObj; // +0x18
	const void *m_team; // +0x1C
	void *m_coordsStart; // +0x20
	void *m_coordsFinish; // +0x24
	void *m_coordsEnd; // +0x28
	char m_tail[0xC0 - 0x2C];
};

class Rva00368C7A
{
public:
	void rva003681F2(const Coord3D *pos, const unsigned char *mask, const Coord3D *pos2, bool flag);
};

typedef UnsignedInt StateID;

class State
{
public:
	StateID getID() const { return m_ID; }
private:
	void *m_vptr;
	StateID m_ID; // +0x04
};

class StateMachine
{
public:
	virtual void gap00(); virtual void gap01(); virtual void gap02(); virtual void gap03();
	virtual Int updateStateMachine() = 0; // +0x10
	virtual void gap05(); virtual void gap06(); virtual void gap07();
	virtual void gap08(); virtual void gap09(); virtual void gap10(); virtual void gap11();
	virtual void gap12(); virtual void gap13();
	virtual void slot14(void *arg) = 0; // +0x38
	// Inlined at every call; dllimport keeps this view from emitting its own copy.
	__declspec(dllimport) __forceinline StateID getCurrentStateID() const { return m_currentState ? m_currentState->getID() : INVALID_STATE_ID; }
private:
	State *m_currentState; // +0x04
};

struct GiantBirdAIUpdateModuleData
{
	unsigned char m_pad00[0x6C];
	Real m_grabTossTimeTrigger; // +0x6C GrabTossTimeTrigger
	Real m_grabTossHeightTrigger; // +0x70 GrabTossHeightTrigger
	unsigned char m_pad74[0x80 - 0x74];
	const FXList *m_tossFX; // +0x80 TossFX
};

struct GiantBirdHeightView
{
	unsigned char m_pad00[0xC0];
	Int m_C0; // +0xC0
};

struct GiantBirdLocomotorView
{
	void *m_00;
	const GiantBirdHeightView *m_04; // +0x04
	Int getC0() const { return m_04->m_C0; }
};

class BehaviorModuleBase
{
public:
	virtual void behaviorModuleBaseAnchor();
	const void *m_moduleData; // +0x04
	Object *m_object; // +0x08
};

class BehaviorModuleOther
{
public:
	virtual void behaviorModuleOtherAnchor();
};

class BehaviorModule : public BehaviorModuleBase, public BehaviorModuleOther
{
public:
	Object *getObject() const { return m_object; }
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
protected:
	UnsignedInt m_nextCallFrameAndPhase; // +0x14
	Int m_indexInLogic; // +0x18
	Int m_bfmeReserved; // +0x1C
};

class AICommandInterface
{
public:
	virtual void aiDoCommand(const AICommandParms *parms) = 0;
};

#define GB_GAP10(n) virtual void aigap##n##0(); virtual void aigap##n##1(); virtual void aigap##n##2(); virtual void aigap##n##3(); virtual void aigap##n##4(); \
	virtual void aigap##n##5(); virtual void aigap##n##6(); virtual void aigap##n##7(); virtual void aigap##n##8(); virtual void aigap##n##9();

class AIUpdateInterface : public UpdateModule, public AICommandInterface
{
public:
	// Primary vtable slots 1..148 (slot 0 is BehaviorModuleBase's).
	GB_GAP10(0) GB_GAP10(1) GB_GAP10(2) GB_GAP10(3) GB_GAP10(4) GB_GAP10(5) GB_GAP10(6)
	GB_GAP10(7) GB_GAP10(8) GB_GAP10(9) GB_GAP10(10) GB_GAP10(11) GB_GAP10(12) GB_GAP10(13)
	virtual void aigap140(); virtual void aigap141(); virtual void aigap142(); virtual void aigap143();
	virtual void aigap144(); virtual void aigap145(); virtual void aigap146(); virtual void aigap147();
	virtual UpdateSleepTime slot149(); // +0x254, where Zero Hour calls doLocomotor
	StateMachine *getStateMachine() const { return m_stateMachine; }
protected:
	unsigned char m_pad24[0x30 - 0x24];
	StateMachine *m_stateMachine; // +0x30
	StateMachine *m_34; // +0x34 the machine waiting to replace +0x30
	unsigned char m_pad38[0x1F0 - 0x38];
	const GiantBirdLocomotorView *m_1F0; // +0x1F0
	unsigned char m_pad1F4[0x3E0 - 0x1F4];
	Bool m_3E0; // +0x3E0 set while +0x30 updates
	unsigned char m_pad3E1[0x3F0 - 0x3E1];
};

class GiantBirdAIUpdate : public AIUpdateInterface
{
public:
	Bool isCommandPending() const { return m_commandPending; }
	virtual UpdateSleepTime update();
	void rva0036AE79();
	const GiantBirdAIUpdateModuleData *getGiantBirdAIUpdateModuleData() const { return (const GiantBirdAIUpdateModuleData *)m_moduleData; }
	Bool testFlag(Int bit) const { return (m_4B8 >> bit) & 1; }
	void clearFlag(Int bit) { m_4B8 &= ~(1 << bit); }
private:
	Rva00351570 m_storedCommand; // +0x3F0
	unsigned char m_pad4B4[0x4B8 - 0x3F0 - sizeof(Rva00351570)];
	UnsignedInt m_4B8; // +0x4B8
	Real m_4BC; // +0x4BC
	Int m_4C0; // +0x4C0
	UnsignedInt m_4C4; // +0x4C4
	unsigned char m_pad4C8[0x528 - 0x4C8];
	Int m_528; // +0x528
	unsigned char m_pad52C[0x538 - 0x52C];
	Real m_538; // +0x538
	Real m_53C; // +0x53C
	unsigned char m_pad540[0x544 - 0x540];
	Coord3D m_544; // +0x544
	unsigned char m_pad550[0x558 - 0x550];
	Bool m_commandPending; // +0x558
	unsigned char m_pad559[0x560 - 0x559];
	Coord3D m_560; // +0x560
	Coord3D m_56C; // +0x56C
	Bool m_578; // +0x578
};

void GiantBirdAIUpdate::rva0036AE79()
{
	if (!testFlag(6))
		return;
	Object *obj = getObject();
	Real height = obj->isAboveTerrain() ? obj->getHeightAboveTerrain() : 0.0f;
	ContainModuleInterface *contain = obj->getContain();
	if (contain && contain->getContainCount(0) > 0)
	{
		m_4BC += 1.0f / (Real)BfmeLogicFramesPerSecond;
		const GiantBirdAIUpdateModuleData *data = getGiantBirdAIUpdateModuleData();
		if ((data->m_grabTossTimeTrigger > 0.0f && m_4BC > data->m_grabTossTimeTrigger)
			|| (data->m_grabTossHeightTrigger > 0.0 && height > data->m_grabTossHeightTrigger))
		{
			clearFlag(6);
			ContainmentList riders = contain->getContainedItemsView().rva0036AE51();
			for (ContainmentList::iterator it = riders.begin(); it._M_node != riders.end()._M_node; )
			{
				Object *rider = (Object *)containmentFirstWord(*it);
				++it;
				if (rider->getID() == m_4C4)
				{
					m_4C4 = 0;
					contain->removeFromContain(rider, false);
					rider->setOrientation(obj->getTransformMatrix()->Get_Z_Rotation());
					getStateMachine()->slot14(0);
					const void *p1F0 = m_1F0;
					PhysicsBehavior *phys = rider->getPhysics();
					if (phys && p1F0)
					{
						Coord3D dir;
						obj->getUnitDirectionVector3D(dir);
						scaleCoord(dir, m_538 / 2.0f);
						Coord3D force;
						force.x = dir.x;
						force.y = dir.y;
						force.z = -6.0f;
						((Rva003909FAObj *)phys)->consume(&force, 0, 0);
						phys->rva00390629(true);
						if (data->m_tossFX)
							FXList::doFXObj(data->m_tossFX, rider, obj);
						if (testFlag(8))
						{
							((Rva00294D61 *)obj)->report(rider, 1);
							phys->setFlag5F();
						}
					}
					rider->setModelConditionState(BFME_MODELCONDITION_72);
					rider->setStatus(OBJECT_STATUS_BFME_3C, false);
					if (!rider->getTemplate()->isKindOf5A())
					{
						BodyModuleInterface *body = rider->getBodyModule();
						if (body)
							body->setIndestructible(false);
					}
					m_4C0 = 0;
					m_4BC = 0.0f;
					break;
				}
			}
		}
	}
	else
	{
		m_4BC = 0.0f;
	}
}

UpdateSleepTime GiantBirdAIUpdate::update()
{
	Object *obj = getObject();
	TheAiOrdersManager->rva003551D3(obj->getID());
	ObjectStatusScope scope(obj, OBJECT_STATUS_BFME_48);
	if (!isCommandPending() && m_storedCommand.m_00 != -1)
	{
		AICommandParms parms(AICMD_NO_COMMAND, CMD_FROM_AI);
		m_storedCommand.reconstitute(*(Rva00351570Src *)&parms);
		aiDoCommand(&parms);
		m_storedCommand.m_00 = -1;
	}
	rva0036AE79();
	m_53C *= 0.8f;
	m_538 *= 0.9f;
	if (m_1F0 && getObject()->getHeightAboveTerrain() > m_1F0->getC0())
		getObject()->setStatus(OBJECT_STATUS_BFME_06, true);
	else
		getObject()->setStatus(OBJECT_STATUS_BFME_06, false);
	UpdateSleepTime sleep = (UpdateSleepTime)2;
	m_3E0 = m_34 != NULL;
	Int stRet = getStateMachine()->updateStateMachine();
	m_3E0 = FALSE;
	if (stRet > 0)
	{
		Int frames = stRet;
		if (frames < sleep)
			sleep = (UpdateSleepTime)frames;
	}
	else
	{
		sleep = UPDATE_SLEEP_NONE;
	}
	if (getObject()->isEffectivelyDead())
		return UPDATE_SLEEP_NONE;
	if (m_56C.GetLengthEstimate() > 0.0f)
	{
		m_56C.normalize();
		Coord3D sum;
		setCoord(sum, *getObject()->getPosition());
		Coord3D prev;
		setCoord(prev, m_560);
		addCoord(sum, m_56C);
		subCoord(sum, prev);
		{
			Coord3D pos;
			setCoord(pos, sum);
			pos.normalize();
		}
		prev.z += 4.0f;
		getObject()->setModelConditionState(BFME_MODELCONDITION_103);
		Real cur = getObject()->getOrientation();
		Real rel = getObject()->GetRelativeAngle(&prev);
		Real turn = min(-0.2f, max(0.2f, normalizeAngle(rel - cur)));
		Real angle = normalizeAngle(cur + turn);
		getObject()->setOrientation(angle);
		getObject()->setPositionZ(prev.z);
		zeroCoord(m_56C);
		m_560 = *getObject()->getPosition();
		m_538 *= 0.5f;
		m_578 = TRUE;
		return UPDATE_SLEEP_NONE;
	}
	if (m_578)
	{
		m_578 = FALSE;
		((Rva00368C7A *)this)->rva003681F2(&m_544, g_00E01EC4, NULL, FALSE);
	}
	m_560 = *getObject()->getPosition();
	switch (getStateMachine()->getCurrentStateID())
	{
		case 0x3E9: case 0x3EA: case 0x3EB: case 0x3EC:
		case 0x3EE: case 0x3EF: case 0x3F1: case 0x3F2: case 0x3F3:
		case 0x3F5: case 0x3F6: case 0x3FB: case 0x3FD: case 0x400:
		{
			UpdateSleepTime tmp = slot149();
			if (tmp < sleep)
				sleep = tmp;
			break;
		}
		case 0x3FC: case 0x3FF:
		{
			m_528 = 2;
			UpdateSleepTime tmp = slot149();
			if (tmp < sleep)
				sleep = tmp;
			break;
		}
		case 0x10: case 0x11: case 0x17: case 0x1F:
		case 0x3F7: case 0x3F8: case 0x3F9: case 0x3FA:
		{
			m_528 = 1;
			UpdateSleepTime tmp = slot149();
			if (tmp < sleep)
				sleep = tmp;
			break;
		}
		case 0x3ED: case 0x3F4:
			sleep = UPDATE_SLEEP_NONE;
			break;
		case 0:
		{
			m_528 = 3;
			UpdateSleepTime tmp = slot149();
			if (tmp < sleep)
				sleep = tmp;
			break;
		}
	}
	return sleep;
}
