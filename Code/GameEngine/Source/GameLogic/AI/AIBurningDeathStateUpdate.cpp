// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// AIBurningDeathState::update, retail 0x0035025B (111B), slot 6 of the state
// vtable whose slot 4 is the sibling onEnter 0x0035017B.
//
// Target facts: fail without an owner or one without an AI (Object +0x258);
// once the death frame (+0x4C, set by onEnter from TheGameLogic's frame) is
// reached call Object 0x00298893 (rowed) and succeed; otherwise run the
// pinned base AIInternalMoveToState::update (0x00347460) and, when that stops
// continuing, take a new goal from 0x003469F5 into +0x20/+0x24 and re-enter
// the base move (pinned AIInternalMoveToState::onEnter, 0x0034C146).
// 0x003469F5 has exactly two callers, this update and the onEnter above, so it
// is placed on AIBurningDeathState under an address-derived name.
//
// Lead facts: the class and method names come from the WorldBuilder lead
// (AIStates.cpp); StateReturnType values follow Zero Hour (CONTINUE 0,
// SUCCESS -1, FAILURE -2). Structural inference: +0x20/+0x24 are the base
// move's goal x/y.

typedef unsigned int UnsignedInt;

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

enum StateExitType
{
	EXIT_NORMAL = 0
};

#include "../../../../Libraries/Include/Lib/Coord3DCtorView.h"
#include "../../Common/GameLogicObjectLookupView.h"

class BfmeSubBGB
{
public:
	bool rva00298893();
};

enum DisabledType { DISABLED_NATIVE_1 = 1 };
class Rva00346BC0 { public: unsigned int words[4]; };
extern unsigned g_Va00E01E08;
#include "../../../Include/GameClient/DrawableBFME2.h"
class Rva262FF8PtrChaseField { public: int get() const; };
template<int N> class BurningNativeSlots : public BurningNativeSlots<N-1> { public: virtual void gap(char (*)[N])=0; };
template<> class BurningNativeSlots<0> {};
class BurningAIView : public BurningNativeSlots<142> { public: virtual void slot142(int)=0; };

class Rva0010CBits
{
public:
	unsigned int testIndex(unsigned int bit) const { return m_words[bit >> 5] & (1U << (bit & 0x1f)); }
	void setIndex(unsigned int bit) { m_words[bit >> 5] |= 1U << (bit & 0x1f); }
private:
	unsigned int m_words[20];
};
class Object
{
public:
	void *getAI() const { return m_ai; }
	const Coord3D *getPosition() const { return &m_position; }
	bool clearDisabled(DisabledType);
	void rva0028AE6D();
	void rva0028CDEB(const Rva00346BC0 &,bool);
	__forceinline void setConditionIndex(unsigned int mc) { if (m_conditionBits.testIndex(mc) == 0) { m_conditionBits.setIndex(mc); rva0028AE6D(); } }

private:
	unsigned char m_pad000[0x38];
	Coord3D m_position;
	unsigned char m_pad044[0x10C-0x44];
	Rva0010CBits m_conditionBits;
	unsigned char m_pad15C[0x258-0x15C];
	void *m_ai; // +0x258
};

class StateMachine
{
public:
	Object *getOwner() const { return m_owner; }

private:
	unsigned char m_pad00[0x14];
	Object *m_owner; // +0x14
};

extern GameLogic *TheGameLogic;

class State
{
public:
	virtual ~State();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();

protected:
	Object *getMachineOwner() const { return m_machine->getOwner(); }

	unsigned char m_pad04[0x18 - 0x04];
	StateMachine *m_machine; // +0x18
};

class AIInternalMoveToState : public State
{
public:
	virtual StateReturnType onEnter();
	virtual StateReturnType update();

protected:
	unsigned char m_pad1C[0x20 - 0x1C];
	Coord3D m_goalPosition; // +0x20
	unsigned char m_pad2C[0x4C - 0x2C];
};

class AIBurningDeathState : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
	virtual StateReturnType update();
	Coord3D rva003469F5();

private:
	UnsignedInt m_deathFrame; // +0x4C
	Coord3D m_deathPosition; // +0x50
};

StateReturnType AIBurningDeathState::update()
{
	Object *obj = getMachineOwner();
	if (obj == 0)
		return STATE_FAILURE;
	if (obj->getAI() == 0)
		return STATE_FAILURE;
	if (m_deathFrame <= TheGameLogic->getFrame())
	{
		((BfmeSubBGB *)obj)->rva00298893();
		return STATE_SUCCESS;
	}
	if (AIInternalMoveToState::update())
	{
		Coord3D goal = rva003469F5();
		m_goalPosition.x = goal.x;
		m_goalPosition.y = goal.y;
		AIInternalMoveToState::onEnter();
	}
	return STATE_CONTINUE;
}

// Native35017B..35025B RET0 and the same state vtable's onEnter slot.
// Owner, AI, frame, initial position and condition word are native accesses;
// goal-picker and base-entry ABIs are independently used by update above.
// The unlabelled slot142 argument and condition word retain native identities.
// The condition is bit 544 of the model-condition bits at +0x10C (word
// +0x150), set once and notified through the rowed Object::rva0028AE6D; the
// bitset spelling of ObjectConditionAndPassengerWeaponSet.cpp keeps retail's
// direct [obj+0x150] operands (a raw word field CSEs the address into a LEA).
StateReturnType AIBurningDeathState::onEnter()
{
    Object *obj = getMachineOwner();
    if (!obj || !obj->getAI())
        return STATE_FAILURE;
    m_deathFrame = TheGameLogic->getFrame() +
        ((Rva262FF8PtrChaseField *)obj->getAI())->get();
    m_deathPosition = *getMachineOwner()->getPosition();
    obj->clearDisabled(DISABLED_NATIVE_1);
    obj->setConditionIndex(544);
    obj->rva0028CDEB(*(const Rva00346BC0 *)&g_Va00E01E08, true);
    TheGameLogic->deselectObject(obj, 0xfffff, true);
    ((BurningAIView *)obj->getAI())->slot142(16);
    Drawable *drawable = ((Thing *)obj)->getDrawable();
    if (drawable)
        drawable->rva00272BE7();
    Coord3D goal = rva003469F5();
    m_goalPosition.x = goal.x;
    m_goalPosition.y = goal.y;
    return AIInternalMoveToState::onEnter();
}

// 0x003469F5 (376 bytes, RET4 with the hidden Coord3D result): the burning
// unit's next wander goal around its death position. Target facts: the
// owner's AI (+0x258) current locomotor (+0x1F0) template (+4) radius (+0xFC)
// and circular flag (+0x100); circular rotates (radius, 0, 0) by a random
// angle in [0, 2pi), otherwise a +-REAL_TO_INT_FLOOR(radius / 10 + 0.5)
// (default 3) cell offset of 10 units; the z of that offset is never set.
// Lead facts: WorldBuilder twin 0xE33D80 (AIStates.cpp lines 0x4535..0x4542)
// shows a Vector3 rotated by Vector3::Rotate_Z(angle) (sin then cos as
// statements, then the two-argument rotate) and the result built from the
// rotated vector and the death position. Member names are structural.
#include <math.h>
float GetGameLogicRandomValueReal(float lo, float hi, char *file, int line);
int GetGameLogicRandomValue(int lo, int hi, char *file, int line);
static __forceinline float burningFloorf(float x) { return (float)floor((double)x); }
static __forceinline long fast_float2long_round(float f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}
#define REAL_TO_INT_FLOOR(x) (fast_float2long_round(burningFloorf(x)))

struct BurningVector3
{
	float X, Y, Z;
	BurningVector3() {}
	BurningVector3(float x, float y, float z) : X(x), Y(y), Z(z) {}
	__forceinline void Rotate_Z(float angle)
	{
		float s = sinf(angle);
		float c = cosf(angle);
		Rotate_Z(s, c);
	}
	__forceinline void Rotate_Z(float s_angle, float c_angle)
	{
		float tmp_x = X;
		float tmp_y = Y;
		X = c_angle * tmp_x - s_angle * tmp_y;
		Y = s_angle * tmp_x + c_angle * tmp_y;
	}
};
struct BurningLocomotorTemplate { char m_pad00[0xFC]; float m_radius; bool m_circular; };
struct BurningLocomotor { char m_pad00[4]; const BurningLocomotorTemplate *m_template; };
struct BurningAI { char m_pad000[0x1F0]; BurningLocomotor *m_curLocomotor; };

Coord3D AIBurningDeathState::rva003469F5()
{
	BurningAI *ai = (BurningAI *)getMachineOwner()->getAI();
	int delta = 3;
	if (ai->m_curLocomotor)
	{
		float radius = ai->m_curLocomotor->m_template->m_radius;
		if (ai->m_curLocomotor->m_template->m_circular)
		{
			BurningVector3 pivot(radius, 0.0f, 0.0f);
			pivot.Rotate_Z(GetGameLogicRandomValueReal(0.0f, 6.2831855f, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\AI\\AIStates.cpp", 0x4535));
			Coord3D result;
			result.x = m_deathPosition.x + pivot.X;
			result.y = m_deathPosition.y + pivot.Y;
			result.z = m_deathPosition.z;
			return result;
		}
		delta = REAL_TO_INT_FLOOR(radius / 10.0f + 0.5f);
	}
	BurningVector3 offset;
	offset.X = GetGameLogicRandomValue(-delta, delta, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\AI\\AIStates.cpp", 0x4541) * 10 + m_deathPosition.x;
	offset.Y = GetGameLogicRandomValue(-delta, delta, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\AI\\AIStates.cpp", 0x4542) * 10 + m_deathPosition.y;
	return Coord3D(offset.X, offset.Y, offset.Z);
}
