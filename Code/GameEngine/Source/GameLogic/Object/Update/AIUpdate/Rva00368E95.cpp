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

// Slot 2 of the retail tables is the class-name getter.
#define BFME_SNAPSHOT_NAME_SLOT
#include "../../object.h"
class Waypoint;
class AIStateMachine { public: void setGoalWaypoint(const Waypoint *p); };
#include "../../../../../Include/Common/StateMachineClass.h"
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
	if (!obj->isMobile())
		return;
	m_angle = obj->GetRelativeAngle(pos);
	m_angle += obj->getOrientation();
	m_machine->clear();
	m_machine->setGoalPosition(obj->getPosition());
	((AIStateMachine *)this)->setGoalWaypoint(wp);
	if (extra)
		m_machine->setState(0x3FF);
	else
		m_machine->setState(0x3FC);
	m_done = 2;
}
