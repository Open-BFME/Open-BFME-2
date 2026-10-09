// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// AIFearState: onEnter 0x00354D0D (419 bytes), update 0x00347CA3 (359 bytes)
// and onExit 0x00347E0A (66 bytes).
//
// Identity: the constructor 0x003428CC passes 0xE4366E82, zlib.crc32 of the
// debug name "AIFearState", and installs the vtable 0x00C125C8 whose slots
// 4, 5 and 6 are these bodies. Donor: BFME1 AIFearState_onEnter.cpp and
// AIFearState_update.cpp (CritterDesync strings 13 and 14). BFME2 target
// facts: update fails without an owner or AI; the fear animation is model
// condition bit 64 (set on enter, cleared on exit), the cower bit cleared in
// update is 61; onExit also clears the AI's flag at +0x3C4; the cower timeout
// reads the AI module data's +0x34/+0x30 (low/high) frame range. Layout as in
// AIStatesBfmeMoveOnEnters.cpp; m_isCowering +0x54, m_cowerTimeoutFrame +0x58.

#include "../../Common/GameLogicObjectLookupView.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"

typedef bool Bool;
typedef float Real;
typedef int Int;
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

enum LocomotorSetType
{
	LOCOMOTORSET_PANIC = 4
};

enum
{
	MODELCONDITION_COWERING = 61,
	MODELCONDITION_FEAR = 64
};

// Retail copies the owner position member-wise (three movss loads, no movsd
// block copy); only a user-written copy constructor reproduces that shape, so
// this TU-local view carries just that constructor.
struct MemberwiseCoord3D : public Coord3D
{
	MemberwiseCoord3D(const Coord3D &other) { x = other.x; y = other.y; z = other.z; }
};

extern unsigned char g_00E03745;
extern "C" void *theLogicRandomLogFile;
extern "C" int __cdecl fprintf(void *stream, const char *format, ...);

static __forceinline void critterDesyncLog(const char *text)
{
	if (g_00E03745)
	{
		void *log = theLogicRandomLogFile;
		if (log != 0)
			fprintf(log, text);
	}
}

Int GetGameLogicRandomValue(Int lo, Int hi, char *file, Int line);

class PathNode
{
public:
	const Coord3D *getPosition() const { return &m_pos; }
private:
	char m_pad00[0x0C];
	Coord3D m_pos; // +0x0C
};

class Path
{
public:
	PathNode *getLastNode() const { return m_pathTail; }
private:
	char m_pad00[8];
	PathNode *m_pathTail; // +0x08
};

struct AIUpdateModuleDataView
{
	char m_pad00[0x30];
	UnsignedInt m_cowerMaxFrames; // +0x30
	UnsignedInt m_cowerMinFrames; // +0x34
};

class AIUpdateInterface
{
public:
#define X1_V(n) virtual void slot##n();
#define X1_V10(n) X1_V(n##0) X1_V(n##1) X1_V(n##2) X1_V(n##3) X1_V(n##4) X1_V(n##5) X1_V(n##6) X1_V(n##7) X1_V(n##8) X1_V(n##9)
	X1_V10(0) X1_V10(1) X1_V10(2) X1_V10(3) X1_V10(4) X1_V10(5) X1_V10(6)
	X1_V10(7) X1_V10(8) X1_V10(9) X1_V10(10) X1_V10(11) X1_V10(12)
	X1_V(130) X1_V(131) X1_V(132) X1_V(133) X1_V(134) X1_V(135)
	virtual void slot136();
	X1_V(137) X1_V(138) X1_V(139) X1_V(140) X1_V(141)
#undef X1_V10
#undef X1_V
	virtual Bool chooseLocomotorSet(LocomotorSetType wst);

	Path *getPath() { return m_path; }
	Bool isWaitingForPath() const { return m_waitingForPath; }
	void requestPath(Coord3D *destination, Bool isFinalGoal);
	void rva00262AEA();

	const AIUpdateModuleDataView *m_moduleData; // +0x04
	char m_pad008[0x140 - 0x08];
	Path *m_path; // +0x140
	char m_pad144[0x180 - 0x144];
	Coord3D m_requestedDestination; // +0x180
	char m_pad18C[0x3B0 - 0x18C];
	Bool m_bfmeFlag3B0; // +0x3B0
	Bool m_waitingForPath; // +0x3B1
	char m_pad3B2[0x3C4 - 0x3B2];
	Bool m_bfmeFlag3C4; // +0x3C4
};

class GeometryInfo
{
public:
	GeometryInfo(const GeometryInfo &that);
	virtual ~GeometryInfo();
	Real getMaxHeightAbovePosition() const;
private:
	char m_pad04[0x5C - 0x04];
};

class ModelConditionFlags
{
public:
	UnsignedInt test(Int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void set(Int bit)
	{
		m_words[bit >> 5] |= 1U << (bit & 0x1f);
	}
	void clear(Int bit)
	{
		m_words[bit >> 5] &= ~(1U << (bit & 0x1f));
	}
private:
	UnsignedInt m_words[19];
};

class Thing
{
public:
	void setOrientation(Real angle);
};

class Object : public Thing
{
public:
	const Coord3D *getPosition() const { return &m_position; }
	Real getOrientation() const { return m_orientation; }
	const GeometryInfo &getGeometryInfo() const { return m_geometryInfo; }
	AIUpdateInterface *getAI() { return m_ai; }
	UnsignedInt getPrivateStatus() const { return m_privateStatus; }
	Real GetRelativeAngle(const Coord3D *pos) const;
	void rva0028AE6D();
	void rva0028AD32();
	__forceinline void setModelConditionState(Int bit)
	{
		if (m_conditionBits.test(bit) == 0)
		{
			m_conditionBits.set(bit);
			rva0028AE6D();
		}
	}
	__forceinline void clearModelConditionState(Int bit)
	{
		if (m_conditionBits.test(bit) != 0)
		{
			m_conditionBits.clear(bit);
			rva0028AE6D();
		}
	}
private:
	char m_pad000[0x38];
	Coord3D m_position; // +0x38
	Real m_orientation; // +0x44
	char m_pad048[0xA8 - 0x48];
	GeometryInfo m_geometryInfo; // +0xA8
	char m_pad104[0x10C - 0x104];
	ModelConditionFlags m_conditionBits; // +0x10C
	char m_pad158[0x258 - (0x10C + sizeof(ModelConditionFlags))];
	AIUpdateInterface *m_ai; // +0x258
	char m_pad25C[0x438 - 0x25C];
	UnsignedInt m_privateStatus; // +0x438
};

extern GameLogic *TheGameLogic;

class StateMachine
{
public:
	Object *getOwner() const { return m_owner; }
	Object *getGoalObject();
protected:
	unsigned char m_pad00[0x14];
	Object *m_owner; // +0x14
};

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
	StateMachine *getMachine() const { return m_machine; }
	Object *getMachineOwner() const { return m_machine->getOwner(); }
	Object *getMachineGoalObject() const { return m_machine->getGoalObject(); }
	unsigned char m_pad04[0x18 - 0x04];
	StateMachine *m_machine; // +0x18
};

class AIInternalMoveToState : public State
{
public:
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
protected:
	void setAdjustsDestination(Bool b) { m_adjustsDestination = b; }
	unsigned char m_pad1C[0x20 - 0x1C];
	Coord3D m_goalPosition; // +0x20
	unsigned char m_pad2C[0x48 - 0x2C];
	Bool m_adjustsDestination; // +0x48
};

class AIFearState : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
protected:
	Int m_okToRepathTimes; // +0x4C
	Bool m_checkForPath; // +0x50
	char m_pad51[3];
	Bool m_isCowering; // +0x54
	UnsignedInt m_cowerTimeoutFrame; // +0x58
};

StateReturnType AIFearState::onEnter()
{
	critterDesyncLog("CritterDesync: setAdjustDestination(FALSE) 13");
	setAdjustsDestination(false);
	Object *obj = getMachineOwner();
	Object *enemy = getMachineGoalObject();
	AIUpdateInterface *ai = getMachineOwner()->getAI();
	if (!enemy || !ai || !obj)
		return STATE_FAILURE;

	GeometryInfo geom(enemy->getGeometryInfo());
	Real enemyZ = enemy->getPosition()->z;
	Real ownerZ = obj->getPosition()->z;
	if (ownerZ - enemyZ > geom.getMaxHeightAbovePosition())
		return STATE_FAILURE;

	ai->chooseLocomotorSet(LOCOMOTORSET_PANIC);
	obj->setModelConditionState(MODELCONDITION_FEAR);
	m_okToRepathTimes = 1;
	m_checkForPath = true;
	m_isCowering = false;
	obj->rva0028AD32();

	MemberwiseCoord3D destination(*obj->getPosition());
	Real dx = destination.x - enemy->getPosition()->x;
	Real dy = destination.y - enemy->getPosition()->y;
	Real dz = destination.z - enemy->getPosition()->z;
	Coord3D direction;
	direction.x = dx;
	direction.y = dy;
	direction.z = dz;
	direction.normalize();
	Real x = direction.x * 20.0f + destination.x;
	Real y = direction.y * 20.0f + destination.y;
	Real z = direction.z * 20.0f + destination.z;
	destination.x = x;
	destination.y = y;
	destination.z = z;
	ai->requestPath(&destination, true);
	return AIInternalMoveToState::onEnter();
}

StateReturnType AIFearState::update()
{
	StateMachine *machine = getMachine();
	Object *obj = machine->getOwner();
	if (!obj)
		return STATE_FAILURE;
	AIUpdateInterface *ai = obj->getAI();
	if (!ai)
		return STATE_FAILURE;

	if (m_isCowering)
	{
		Object *enemy = machine->getGoalObject();
		if (!enemy)
			return STATE_SUCCESS;
		if (enemy->getPrivateStatus() & 1)
			return STATE_SUCCESS;
		if (TheGameLogic->getFrame() > m_cowerTimeoutFrame)
			return STATE_SUCCESS;
		ai->slot136();
		obj->clearModelConditionState(MODELCONDITION_COWERING);
		Real angle = obj->GetRelativeAngle(enemy->getPosition());
		angle += obj->getOrientation();
		obj->setOrientation(angle);
		return STATE_CONTINUE;
	}

	if (m_checkForPath)
	{
		Path *thePath = ai->getPath();
		if (thePath && !ai->isWaitingForPath())
		{
			m_goalPosition = *thePath->getLastNode()->getPosition();
			critterDesyncLog("CritterDesync: setAdjustDestination(FALSE) 14");
			setAdjustsDestination(false);
			m_checkForPath = false;
		}
	}

	if (AIInternalMoveToState::update() != STATE_CONTINUE)
	{
		m_isCowering = true;
		ai->slot136();
		ai->rva00262AEA();
		ai->m_requestedDestination = m_goalPosition;
		ai->m_bfmeFlag3B0 = false;
		if (ai->m_bfmeFlag3C4)
		{
			UnsignedInt delay = ai->m_moduleData->m_cowerMinFrames >> 2;
			m_cowerTimeoutFrame = TheGameLogic->getFrame() + delay;
		}
		else
		{
			const AIUpdateModuleDataView *data = ai->m_moduleData;
			UnsignedInt frame = TheGameLogic->getFrame();
			Int high = data->m_cowerMaxFrames;
			Int low = data->m_cowerMinFrames;
			m_cowerTimeoutFrame = frame + GetGameLogicRandomValue(low, high,
				"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\AI\\AIStates.cpp", 4058);
		}
	}
	return STATE_CONTINUE;
}

void AIFearState::onExit(StateExitType status)
{
	AIInternalMoveToState::onExit(status);
	Object *obj = getMachineOwner();
	if (obj)
	{
		obj->clearModelConditionState(MODELCONDITION_FEAR);
		AIUpdateInterface *ai = obj->getAI();
		if (ai)
			ai->m_bfmeFlag3C4 = false;
	}
}
