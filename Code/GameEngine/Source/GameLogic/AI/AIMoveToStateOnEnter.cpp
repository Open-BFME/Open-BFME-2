// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// AIMoveToState::onEnter, retail 0x0034C7BD (264 bytes).
//
// Donor: Zero Hour AIStates.cpp AIMoveToState::onEnter (adjust the destination
// unless the goal object is the obstacle being ignored, take the goal object's
// or the machine's goal position, then AIInternalMoveToState::onEnter). BFME2
// target facts: each setAdjustsDestination writes its CritterDesync log line
// first (strings 4 and 5, as in AIMoveToStateSA::onEnter); when the owner has
// kind-of bit 25 the goal height is raised by half the goal geometry's
// maximum height above position (0x006BD7C0), twice when that already lifts
// it above the goal. Layout as in AIEnterStateOnEnter.cpp.

#include "../../Common/GameLogicObjectLookupView.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"

typedef bool Bool;
typedef float Real;
typedef unsigned int UnsignedInt;

enum StateReturnType
{
	STATE_FAILURE = -2
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

class AIUpdateInterface
{
public:
	ObjectID getIgnoredObstacleID() const;
};

class ThingTemplate
{
public:
	__forceinline UnsignedInt isKindOf(UnsignedInt bit) const
	{
		return m_kindOf[bit >> 5] & (1U << (bit & 0x1f));
	}
	char m_pad000[0x108];
	UnsignedInt m_kindOf[8];
};

class GeometryInfo
{
public:
	Real getMaxHeightAbovePosition() const;
private:
	char m_pad00[0x14];
};

class Object
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	const Coord3D *getPosition() const { return &m_position; }
	ObjectID getID() const { return m_id; }
	const GeometryInfo &getGeometryInfo() const { return m_geometryInfo; }
	AIUpdateInterface *getAI() { return m_ai; }
private:
	char m_pad000[4];
	const ThingTemplate *m_template;
	char m_pad008[0x38 - 0x08];
	Coord3D m_position;
	char m_pad044[0x74 - 0x44];
	ObjectID m_id;
	char m_pad078[0xA8 - 0x78];
	GeometryInfo m_geometryInfo; // +0xA8
	char m_pad0BC[0x258 - 0xBC];
	AIUpdateInterface *m_ai; // +0x258
};

class StateMachine
{
public:
	Object *getOwner() const { return m_owner; }
	Object *getGoalObject();
	const Coord3D *getGoalPosition() const { return &m_goalPosition; }
protected:
	unsigned char m_pad00[0x14];
	Object *m_owner; // +0x14
	unsigned char m_pad18[0x24 - 0x18];
	Coord3D m_goalPosition; // +0x24
};

class State
{
public:
	virtual ~State();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual StateReturnType onEnter();
protected:
	StateMachine *getMachine() const { return m_machine; }
	Object *getMachineOwner() const { return m_machine->getOwner(); }
	unsigned char m_pad04[0x18 - 0x04];
	StateMachine *m_machine; // +0x18
};

class AIInternalMoveToState : public State
{
public:
	virtual StateReturnType onEnter();
protected:
	void setAdjustsDestination(Bool b) { m_adjustsDestination = b; }
	unsigned char m_pad1C[0x20 - 0x1C];
	Coord3D m_goalPosition; // +0x20
	unsigned char m_pad2C[0x48 - 0x2C];
	Bool m_adjustsDestination; // +0x48
};

class AIMoveToState : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
};

enum
{
	KINDOF_BIT_25 = 25
};

StateReturnType AIMoveToState::onEnter()
{
	critterDesyncLog("CritterDesync: setAdjustDestination(TRUE) 4");
	setAdjustsDestination(true);

	// If we have a goal object and are trying to ignore it as an obstacle...
	AIUpdateInterface *ai = getMachineOwner()->getAI();
	if (getMachine()->getGoalObject())
	{
		if (ai && getMachine()->getGoalObject()->getID() == ai->getIgnoredObstacleID())
		{
			critterDesyncLog("CritterDesync: setAdjustDestination(FALSE) 5");
			setAdjustsDestination(false);
		}
	}

	// if we have a goal object, move to it, otherwise move to goal position
	if (getMachine()->getGoalObject())
	{
		m_goalPosition = *getMachine()->getGoalObject()->getPosition();
		if (getMachineOwner()->getTemplate()->isKindOf(KINDOF_BIT_25))
		{
			Real halfHeight = getMachine()->getGoalObject()->getGeometryInfo().getMaxHeightAbovePosition() * 0.5f;
			m_goalPosition.z += halfHeight;
			if (m_goalPosition.z > getMachine()->getGoalObject()->getPosition()->z)
				m_goalPosition.z += halfHeight;
		}
	}
	else
		m_goalPosition = *getMachine()->getGoalPosition();

	return AIInternalMoveToState::onEnter();
}
