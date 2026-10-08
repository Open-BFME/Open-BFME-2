// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
//
// The two followToNextPointNow bodies of BFME 2's giant-bird path states
// (WorldBuilder's GiantBirdAIUpdate.cpp names both):
//
//  - GiantBirdFollowPathState::followToNextPointNow, retail 0x00368662
//    (305 bytes, WorldBuilder 0x00F334D0), point index at +0x58;
//  - GiantBirdFollowWaypointPathState::followToNextPointNow, retail
//    0x003687DD (305 bytes, WorldBuilder 0x00F34190), point index at +0x20.
//
// The two retail bodies differ only in that offset. Retail proves the
// owner/AI/locomotor chain (AI +0x1F0), the path-point accessor of the AI's
// state machine (+0x30, rowed 0x00346FA5), the loop byte (+0x550), the
// look-ahead bit 7 of AI +0x4B8, the flight height (+0x540) added to the
// terrain's ground height (TerrainLogic slot 6), and the route call (rowed
// 0x003681F2) with the current point, the look-ahead point and a bool that
// is set when there is no look-ahead point. Retail loads the look-ahead
// index into a register before pushing it, which the local copy reproduces.

typedef bool Bool;
typedef float Real;

#include "../../../../../../Libraries/Include/Lib/Coord3D.h"

template <int N> class GiantBirdPathSlots : public GiantBirdPathSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class GiantBirdPathSlots<0>
{
};

class Rva00346FA5
{
public:
	void *rva00346FA5(int index) const;
};

class Rva00368C7A
{
public:
	void rva003681F2(const Coord3D *position, const unsigned char *mask,
		const Coord3D *lookAhead, Bool noLookAhead);
};

class TerrainLogic : public GiantBirdPathSlots<6>
{
public:
	virtual Real getGroundHeight(Real x, Real y, int unused);
};
extern TerrainLogic *TheTerrainLogic;
extern unsigned char g_00E01EC0[4];

class AIUpdateInterface
{
public:
	Rva00346FA5 *getPathMachine() const { return m_pathMachine; }
	Bool hasLocomotor() const { return m_locomotor != 0; }
	Bool loopsPath() const { return m_loopPath; }
	Real getPathHeight() const { return m_pathHeight; }
	void setLookAhead(Bool value)
	{
		if (value) m_pathFlags |= 0x80;
		else m_pathFlags &= ~0x80;
	}
private:
	void *m_vtbl;
	unsigned char m_pad04[0x30 - 4];
	Rva00346FA5 *m_pathMachine; // +0x30
	unsigned char m_pad34[0x1F0 - 0x34];
	void *m_locomotor; // +0x1F0
	unsigned char m_pad1F4[0x4B8 - 0x1F4];
	unsigned char m_pathFlags; // +0x4B8, bit 7
	unsigned char m_pad4B9[0x540 - 0x4B9];
	Real m_pathHeight; // +0x540
	unsigned char m_pad544[0x550 - 0x544];
	Bool m_loopPath; // +0x550
};

class Object
{
public:
	AIUpdateInterface *getAI() { return m_ai; }
private:
	unsigned char m_pad000[0x258];
	AIUpdateInterface *m_ai; // +0x258
};

class StateMachine
{
public:
	Object *getOwner() const { return m_owner; }
private:
	unsigned char m_pad00[0x14];
	Object *m_owner; // +0x14
};

class State
{
public:
	virtual ~State();
protected:
	Object *getMachineOwner() const { return m_machine->getOwner(); }
	unsigned char m_pad04[0x18 - 0x04];
	StateMachine *m_machine; // +0x18
};

class GiantBirdFollowPathState : public State
{
public:
	Bool followToNextPointNow();
private:
	unsigned char m_pad1C[0x58 - 0x1C];
	int m_pointIndex; // +0x58
};

Bool GiantBirdFollowPathState::followToNextPointNow()
{
	Object *owner = getMachineOwner();
	if (!owner) return false;
	AIUpdateInterface *ai = owner->getAI();
	if (!ai) return false;
	if (!ai->hasLocomotor()) return false;

	const Coord3D *point = (const Coord3D *)ai->getPathMachine()->rva00346FA5(m_pointIndex++);
	if (!point)
	{
		if (!ai->loopsPath()) return false;
		m_pointIndex = 0;
		point = (const Coord3D *)ai->getPathMachine()->rva00346FA5(m_pointIndex++);
		if (!point) return false;
	}

	Coord3D lookAhead;
	int nextIndex = m_pointIndex;
	const Coord3D *next = (const Coord3D *)ai->getPathMachine()->rva00346FA5(nextIndex);
	if (next)
	{
		ai->setLookAhead(true);
		lookAhead = *next;
		next = &lookAhead;
		lookAhead.z = TheTerrainLogic->getGroundHeight(lookAhead.x, lookAhead.y, 0) + ai->getPathHeight();
	}
	else
		ai->setLookAhead(false);

	Coord3D position;
	position.x = point->x;
	position.y = point->y;
	position.z = point->z;
	position.z = TheTerrainLogic->getGroundHeight(position.x, position.y, 0) + ai->getPathHeight();
	((Rva00368C7A *)ai)->rva003681F2(&position, g_00E01EC0, next, next == 0);
	return true;
}

class GiantBirdFollowWaypointPathState : public State
{
public:
	Bool followToNextPointNow();
private:
	unsigned char m_pad1C[0x20 - 0x1C];
	int m_pointIndex; // +0x20
};

Bool GiantBirdFollowWaypointPathState::followToNextPointNow()
{
	Object *owner = getMachineOwner();
	if (!owner) return false;
	AIUpdateInterface *ai = owner->getAI();
	if (!ai) return false;
	if (!ai->hasLocomotor()) return false;

	const Coord3D *point = (const Coord3D *)ai->getPathMachine()->rva00346FA5(m_pointIndex++);
	if (!point)
	{
		if (!ai->loopsPath()) return false;
		m_pointIndex = 0;
		point = (const Coord3D *)ai->getPathMachine()->rva00346FA5(m_pointIndex++);
		if (!point) return false;
	}

	Coord3D lookAhead;
	int nextIndex = m_pointIndex;
	const Coord3D *next = (const Coord3D *)ai->getPathMachine()->rva00346FA5(nextIndex);
	if (next)
	{
		ai->setLookAhead(true);
		lookAhead = *next;
		next = &lookAhead;
		lookAhead.z = TheTerrainLogic->getGroundHeight(lookAhead.x, lookAhead.y, 0) + ai->getPathHeight();
	}
	else
		ai->setLookAhead(false);

	Coord3D position;
	position.x = point->x;
	position.y = point->y;
	position.z = point->z;
	position.z = TheTerrainLogic->getGroundHeight(position.x, position.y, 0) + ai->getPathHeight();
	((Rva00368C7A *)ai)->rva003681F2(&position, g_00E01EC0, next, next == 0);
	return true;
}
