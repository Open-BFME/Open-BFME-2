// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// AIGuardMachine::rva00543326, retail 0x00543326 (212 bytes): the guard
// position Zero Hour's AIGuard.cpp computes inline in lookForInnerTarget and
// the guard states (target's position, else the position to guard, then the
// area's center when there is an area), gathered into one BFME 2 function
// (target evidence: called by the pinned lookForInnerTarget 0x005433FA at
// 0x0054362A and by 0x00543CC4). BFME 2 also falls back to the guarded
// team's estimated position (the pinned Team::rva0039E5B9) when there is no
// target, takes a precomputed area center (+0x54, valid flag +0x60) over the
// area's PolygonTrigger::getCenterPoint, and uses the owner's position when
// the result is still at x = y = 0. Layout as in AIGuardStates.cpp.
typedef bool Bool;
typedef float Real;
typedef unsigned int UnsignedInt;
#define NULL 0

enum ObjectID
{
	INVALID_ID = 0
};
typedef UnsignedInt TeamID;

struct Coord3D
{
	Coord3D() {}
	Coord3D(const Coord3D &that) : x(that.x), y(that.y), z(that.z) {}
	Real x, y, z;
	void zero() { x = 0.0f; y = 0.0f; z = 0.0f; }
};

class Object
{
public:
	const Coord3D *getPosition() const { return &m_position; }
private:
	unsigned char m_pad00[0x38];
	Coord3D m_position; // +0x38
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};
extern GameLogic *TheGameLogic;

class Team
{
public:
	void rva0039E5B9(Coord3D *pos); // estimated team position
};
class TeamFactory
{
public:
	Team *findTeamByID(TeamID id);
};
extern TeamFactory *TheTeamFactory;

class PolygonTrigger
{
public:
	void getCenterPoint(Coord3D *pOutCoord) const;
};

class StateMachine
{
public:
	Object *getOwner() const { return m_owner; }
protected:
	unsigned char m_pad00[0x14];
	Object *m_owner; // +0x14
};

class AIGuardMachine : public StateMachine
{
public:
	Coord3D rva00543326() const;
	Object *findTargetToGuardByID() const { return TheGameLogic->findObjectByID(m_targetToGuard); }
	Team *findTeamToGuardByID() const { return TheTeamFactory->findTeamByID(m_teamToGuard); }
private:
	unsigned char m_pad18[0x3C - 0x18];
	ObjectID m_targetToGuard; // +0x3C
	TeamID m_teamToGuard; // +0x40
	const PolygonTrigger *m_areaToGuard; // +0x44
	Coord3D m_positionToGuard; // +0x48
	Coord3D m_bfmeAreaCenter; // +0x54
	Bool m_bfmeAreaCenterValid; // +0x60
};

Coord3D AIGuardMachine::rva00543326() const
{
	Object *targetToGuard = findTargetToGuardByID();
	Team *teamToGuard = findTeamToGuardByID();
	Coord3D pos;
	pos.zero();
	if (targetToGuard)
		pos = *targetToGuard->getPosition();
	else if (teamToGuard)
		teamToGuard->rva0039E5B9(&pos);
	else
		pos = m_positionToGuard;

	if (m_areaToGuard)
	{
		if (m_bfmeAreaCenterValid)
			pos = m_bfmeAreaCenter;
		else
			m_areaToGuard->getCenterPoint(&pos);
	}

	if (pos.x == 0.0f && pos.y == 0.0f)
		pos = *getOwner()->getPosition();

	return pos;
}
