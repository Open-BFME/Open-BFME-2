// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
// Native 00368E95..00368F08, 115B, RET12. A sibling of the Rva00368344.cpp
// command handlers (same +8 Object gated by the rowed mobile predicate 002907A1,
// +30 machine slots 5 and 8, the +48 waypoint setter 003E3BFB on this and
// the +528 mode store), but built /O1: it pushes its stack arguments directly
// and tail-merges the two slot-8 calls. It turns toward the goal first: the
// rowed relative-angle helper 000B4542 plus the Object's +44 orientation
// lands at +52C, and the rowed StateMachine::setGoalPosition 00262224 takes
// the Object's +38 position. Original member name unknown.
#include "../../../../../../Libraries/Include/Lib/Coord3D.h"

class Object
{
public:
	bool rva002907A1();
	float GetRelativeAngle(const Coord3D *pos) const;
	const Coord3D *getPosition() const { return &m_position; }
	float getOrientation() const { return m_orientation; }
private:
	char m_pad00[0x38];
	Coord3D m_position; // +0x38
	float m_orientation; // +0x44
};
class Waypoint;
class AIStateMachine { public: void setGoalWaypoint(const Waypoint *p); };
class StateMachine
{
public:
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
	virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(int v);
	void setGoalPosition(const Coord3D *pos);
};
class Rva00368344
{
public:
	void rva00368E95(const Coord3D *pos, const Waypoint *wp, bool extra);
private:
	char m_pad00[8];
	Object *m_gate08; // +0x08
	char m_pad0C[0x30 - 0x0C];
	StateMachine *m_machine; // +0x30
	char m_pad34[0x528 - 0x34];
	int m_done; // +0x528
	float m_angle; // +0x52C
};

void Rva00368344::rva00368E95(const Coord3D *pos, const Waypoint *wp, bool extra)
{
	Object *obj = m_gate08;
	if (!obj->rva002907A1())
		return;
	m_angle = obj->GetRelativeAngle(pos);
	m_angle += obj->getOrientation();
	m_machine->s5();
	m_machine->setGoalPosition(obj->getPosition());
	((AIStateMachine *)this)->setGoalWaypoint(wp);
	if (extra)
		m_machine->s8(0x3FF);
	else
		m_machine->s8(0x3FC);
	m_done = 2;
}
