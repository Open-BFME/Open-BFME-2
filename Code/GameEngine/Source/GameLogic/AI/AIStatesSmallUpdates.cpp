// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// AIDeadState::update, retail 0x0033FF05 (38 bytes): slot 6 of vtable
// 0x00C11318, whose slot-2 name getter returns AIDeadState (slot 5 is the
// rowed AIDeadState::onExit). BFME2 body (target evidence): the owner's AI, if
// any, gets AIUpdateInterface vslot 136 (+0x220), then the owner is marked
// effectively dead (pinned Object::setEffectivelyDead) and the state continues.
// AIFollowWaypointPathExactState::update, retail 0x0034A167 (28 bytes): slot 6
// of vtable 0x00C12A08 (name getter AIFollowWaypointPathExactState), the Zero
// Hour body: setCanPathThroughUnits(true) on the AI (byte +0x3BA), then the
// pinned base AIInternalMoveToState::update 0x00347460 (tail jump).
// AIFollowWaypointPathExactState::onExit, retail 0x0034A121 (70 bytes): slot 5
// of vtable 0x00C12A08 (name getter AIFollowWaypointPathExactState), the Zero
// Hour body: base onExit, then if AI and current locomotor, setCompletedWaypoint,
// clear canPathThroughUnits and allowInvalidPosition.
// AIFollowWaypointPathExactState::onEnter, retail 0x0034F01B (312 bytes): slot 4
// of vtable 0x00C12A08 (name getter AIFollowWaypointPathExactState), the Zero
// Hour body: goal waypoint check, setGoalPosition, group center/speed offset,
// CritterDesync log, base onEnter, setPathFromWaypoint, update goal position from
// path tail, locomotor allowInvalidPosition, and setDesiredSpeed.
// AIFollowWaypointPathExactState::xfer, retail 0x00341114 (104 bytes): slot 3
// of vtable 0x00C12A08 (name getter AIFollowWaypointPathExactState), the Zero
// Hour body: Version1, base xfer, IsLightCRC check, lastWaypoint ID xfer,
// and TheTerrainLogic waypoint ID lookup on load.
typedef bool Bool;
typedef float Real;
enum StateExitType
{
	EXIT_NORMAL = 0
};
enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};
struct Coord3D
{
	Real x, y, z;
};
struct Coord2D
{
	Real x, y;
};
class PathNode
{
public:
	const Coord3D *getPosition() const { return &m_pos; }
private:
	unsigned char m_pad00[0x0C];
	Coord3D m_pos; // +0x0C
};
class Path
{
public:
	PathNode *getLastNode() const { return m_lastNode; }
private:
	unsigned char m_pad00[0x08];
	PathNode *m_lastNode; // +0x08
};
class Waypoint
{
public:
	int m_pad00;
	unsigned int m_id; // +4
	unsigned char m_pad08[0x0C - 8];
	Coord3D m_location; // +0x0C
	const Coord3D *getLocation() const { return &m_location; }
};
class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;
class Xfer
{
public:
	class Version;
	Xfer();
	virtual ~Xfer();
	void Version1();
	virtual bool IsLoading() const;
	virtual bool IsStoring() const;
	virtual bool IsCRC() const;
	virtual bool IsLightCRC() const;
	virtual void v5() = 0;
	virtual void v6() = 0;
	virtual void v7() = 0;
	virtual void SkipBadBlock(Snapshot &snapshot, unsigned int size);
	virtual Xfer &XferRawBytes(void *data, unsigned int size);
	virtual Xfer &operator==(bool &value);
	virtual Xfer &operator==(char &value);
	virtual Xfer &operator==(unsigned char &value);
	virtual Xfer &operator==(short &value);
	virtual Xfer &operator==(unsigned short &value);
	virtual Xfer &operator==(int &value);
	virtual Xfer &operator==(unsigned int &value);
	virtual Xfer &operator==(__int64 &value);
	virtual Xfer &operator==(float &value);
	virtual Xfer &operator==(AsciiString &value);
	virtual Xfer &operator==(UnicodeString &value);
	virtual Xfer &operator==(PooledString &value);
	virtual Xfer &operator==(Coord3DBase &value);
	virtual Xfer &operator==(ICoord3D &value);
	virtual Xfer &operator==(Region3D &value);
	virtual Xfer &operator==(IRegion3D &value);
	virtual Xfer &operator==(Coord2D &value);
	virtual Xfer &operator==(ICoord2D &value);
	virtual Xfer &operator==(Region2D &value);
	virtual Xfer &operator==(IRegion2D &value);
	virtual Xfer &operator==(RealRange &value);
	virtual Xfer &operator==(RGBColor &value);
	virtual Xfer &operator==(RGBAColorReal &value);
	virtual Xfer &operator==(RGBAColorInt &value);
	virtual Xfer &operator==(Snapshot &value);
	virtual Xfer &operator==(XferUnknown11 &value) = 0;
	virtual Xfer &operator==(Version &value);
	virtual Xfer &XferEnum(const char *name, void *data, unsigned int size);
protected:
	virtual void XferData(unsigned int type, void *data, unsigned int size) = 0;
};

class TerrainLogic
{
public:
	virtual void _00(); virtual void _01(); virtual void _02(); virtual void _03();
	virtual void _04(); virtual void _05(); virtual void _06(); virtual void _07();
	virtual void _08(); virtual void _09(); virtual void _10(); virtual void _11();
	virtual void _12(); virtual void _13(); virtual void _14(); virtual void _15();
	virtual void _16(); virtual void _17(); virtual void _18(); virtual void _19();
	virtual void _20(); virtual void _21(); virtual void _22(); virtual void _23();
	virtual void _24(); virtual void _25(); virtual void _26(); virtual void _27();
	virtual void _28(); virtual void _29(); virtual void _30(); virtual void _31();
	virtual void _32(); virtual void _33(); virtual void _34();
	virtual const Waypoint *getWaypointByID(unsigned int id);
};
extern TerrainLogic *TheTerrainLogic;
class AIGroup
{
public:
	Real getSpeed();
	Bool getCenter(Coord3D *center);
};
class RadarObject;
struct FprintfTarget
{
	char m_pad[4];
};
extern "C" void fprintf(FprintfTarget *target, const char *format, ...);
extern unsigned char g_00E03745;
extern void *g_00DFEFF0;
template <int N> class AIDeadStateAISlots : public AIDeadStateAISlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class AIDeadStateAISlots<0>
{
};
class Locomotor
{
public:
	enum LocoFlag
	{
		IS_BRAKING = 0,
		ALLOW_INVALID_POSITION,
	};
	void setAllowInvalidPosition(Bool b)
	{
		if (b)
			m_flags |= (1 << ALLOW_INVALID_POSITION);
		else
			m_flags &= ~(1 << ALLOW_INVALID_POSITION);
	}
private:
	unsigned char m_pad00[0x44];
	unsigned int m_flags; // +0x44
};
// AIUpdateInterface: vslot 136 (+0x220) is called on a dead owner's AI.
class AIUpdateInterface : public AIDeadStateAISlots<136>
{
public:
	virtual void rva0033FF05Slot136() = 0;
	void setCompletedWaypoint(const Waypoint *wp);
	Locomotor *getCurLocomotor() { return m_curLocomotor; }
	void setCanPathThroughUnits(Bool b) { m_canPathThroughUnits = b; }
	RadarObject *rva002630F5();
	void setPathFromWaypoint(const Waypoint *wp, const Coord2D *offset);
	void setDesiredSpeed(Real speed);
	Path *getPath() const { return m_path; }
private:
	unsigned char m_pad004[0x140 - 0x04];
	Path *m_path; // +0x140
	unsigned char m_pad144[0x1F0 - 0x144];
	Locomotor *m_curLocomotor; // +0x1F0
	unsigned char m_pad1F4[0x3BA - 0x1F4];
	Bool m_canPathThroughUnits; // +0x3BA
};
class Object
{
public:
	const Coord3D *getPosition() const { return &m_position; }
	AIUpdateInterface *getAI() { return m_ai; }
	void setEffectivelyDead(bool dead);
private:
	unsigned char m_pad00[0x38];
	Coord3D m_position; // +0x38
	unsigned char m_pad44[0x258 - (0x38 + sizeof(Coord3D))];
	AIUpdateInterface *m_ai; // +0x258
};
class StateMachine
{
public:
	Object *getOwner() const { return m_owner; }
	const Waypoint *getGoalWaypoint() const { return m_goalWaypoint; }
	void setGoalPosition(const Coord3D *pos);
private:
	unsigned char m_pad00[0x14];
	Object *m_owner; // +0x14
	unsigned char m_pad18[0x48 - (0x14 + sizeof(Object *))];
	const Waypoint *m_goalWaypoint; // +0x48
};
class State
{
public:
	virtual ~State();
	virtual void slot01();
	virtual void slot02();
	virtual void xfer(Xfer *xfer);
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
protected:
	Object *getMachineOwner() const { return m_machine->getOwner(); }
	unsigned char m_pad04[0x18 - 0x04];
	StateMachine *m_machine; // +0x18
};
class AIDeadState : public State
{
public:
	virtual StateReturnType update();
};
StateReturnType AIDeadState::update()
{
	Object *obj = getMachineOwner();
	AIUpdateInterface *ai = obj->getAI();
	if (ai)
		ai->rva0033FF05Slot136();
	obj->setEffectivelyDead(true);
	return STATE_CONTINUE;
}
class AIInternalMoveToState : public State
{
public:
	AIInternalMoveToState(StateMachine *machine, unsigned int hash);
	virtual ~AIInternalMoveToState();
	virtual void xfer(Xfer *xfer);
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
protected:
	unsigned char m_pad1C[0x20 - 0x1C];
	Coord3D m_goalPosition; // +0x20
	unsigned char m_pad2C[0x48 - (0x20 + sizeof(Coord3D))];
	Bool m_adjustsDestination; // +0x48
};
class AIFollowWaypointPathExactState : public AIInternalMoveToState
{
public:
	AIFollowWaypointPathExactState(StateMachine *machine, Bool moveAsGroup);
	virtual ~AIFollowWaypointPathExactState();
	virtual void xfer(Xfer *xfer);
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
private:
	const Waypoint *m_lastWaypoint; // +0x4C
	Bool m_moveAsGroup; // +0x50
};





AIFollowWaypointPathExactState::AIFollowWaypointPathExactState(StateMachine *machine, Bool moveAsGroup)
	: AIInternalMoveToState(machine, 0xE1CB82BFu)
{
	m_lastWaypoint = 0;
	m_moveAsGroup = moveAsGroup;
}

// ?AIFollowWaypointPathExactState::~AIFollowWaypointPathExactState present-unmatched
AIFollowWaypointPathExactState::~AIFollowWaypointPathExactState()
{
}

StateReturnType AIFollowWaypointPathExactState::onEnter()
{
	const Waypoint *currentWaypoint = m_machine->getGoalWaypoint();
	AIUpdateInterface *ai = m_machine->getOwner()->getAI();
	if (!currentWaypoint)
		return STATE_FAILURE;
	if (!ai->getCurLocomotor())
		return STATE_FAILURE;

	m_machine->setGoalPosition(currentWaypoint->getLocation());

	Coord2D groupOffset;
	groupOffset.x = groupOffset.y = 0.0f;

	Object *obj = m_machine->getOwner();
	Real speed = 999999.0f;
	if (m_moveAsGroup)
	{
		AIGroup *group = (AIGroup *)ai->rva002630F5();
		if (group)
		{
			speed = group->getSpeed();
			Coord3D center;
			group->getCenter(&center);
			groupOffset.x = obj->getPosition()->x - center.x;
			groupOffset.y = obj->getPosition()->y - center.y;
		}
	}

	ai->setCanPathThroughUnits(true);

	if (g_00E03745)
	{
		FprintfTarget *log = (FprintfTarget *)g_00DFEFF0;
		if (log)
			fprintf(log, "CritterDesync: setAdjustDestination(FALSE) 56");
	}

	m_adjustsDestination = false;
	m_goalPosition = *currentWaypoint->getLocation();

	StateReturnType ret = AIInternalMoveToState::onEnter();

	ai->setPathFromWaypoint(currentWaypoint, &groupOffset);

	if (ai->getPath() && ai->getPath()->getLastNode())
	{
		m_goalPosition = *ai->getPath()->getLastNode()->getPosition();
	}

	m_lastWaypoint = currentWaypoint;
	ai->getCurLocomotor()->setAllowInvalidPosition(true);
	ai->setDesiredSpeed(speed);

	return ret;
}
void AIFollowWaypointPathExactState::onExit(StateExitType status)
{
	AIInternalMoveToState::onExit(status);

	AIUpdateInterface *ai = getMachineOwner()->getAI();
	if (ai && ai->getCurLocomotor())
	{
		ai->setCompletedWaypoint(m_lastWaypoint);
		ai->setCanPathThroughUnits(false);
		ai->getCurLocomotor()->setAllowInvalidPosition(false);
	}
}
StateReturnType AIFollowWaypointPathExactState::update()
{
	AIUpdateInterface *ai = getMachineOwner()->getAI();
	if (ai)
		ai->setCanPathThroughUnits(true);
	return AIInternalMoveToState::update();
}

void AIFollowWaypointPathExactState::xfer(Xfer *xfer)
{
	xfer->Version1();
	AIInternalMoveToState::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	unsigned int id = 0x7fffffff;
	if (m_lastWaypoint)
		id = m_lastWaypoint->m_id;
	*xfer == id;
	if (xfer->IsLoading())
		m_lastWaypoint = TheTerrainLogic->getWaypointByID(id);
}

