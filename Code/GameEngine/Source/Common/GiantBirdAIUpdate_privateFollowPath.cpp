// cl: /DNDEBUG /MD
// ?privateFollowPath@GiantBirdAIUpdate@@QAEXABVRva0035149F@@PBVObject@@PBVWaypoint@@H@Z, RVA 0x003697F9, 172 bytes.
// Evidence: unlock lane, caller GiantBirdAIUpdate::privateFollowWaypointPath (0x0036BA77) passes its own this,
// vector<Coord3D> + null + Waypoint; the body sits inside GiantBirdAIUpdate's code; callees rowed
// Object::isMobile 0x002907A1, StateMachine::setGoalPosition 0x004D745C,
// Rva00351759::rva00351759 0x00351759, AIStateMachine::setGoalWaypoint 0x003E3BFB,
// AIUpdateInterface::ignoreObstacle 0x00268D88; virtual slots 0x14/0x20 on +0x30;
// float const VA 0x00BBB8E0 (FLT_MAX, 3.4028235e+38f); +0x528 flag.

#include "../../../Libraries/Include/Lib/Coord3D.h"

#include "../GameLogic/Object/object.h"

#include "../../Include/GameLogic/Waypoint.h"

class Rva0035149F
{
public:
	Coord3D *m_start;
	Coord3D *m_finish;
	Coord3D *m_end;
};

class Rva00351759
{
public:
	char m_pad[0x3c];
	Rva0035149F m_vec;
	Rva0035149F &rva00351759(const Rva0035149F &other);
};

class StateMachine
{
public:
	virtual void vslot00();
	virtual void vslot04();
	virtual void vslot08();
	virtual void vslot0c();
	virtual void vslot10();
	virtual void vslot14();
	virtual void vslot18();
	virtual void vslot1c();
	virtual void vslot20(int v);
	void setGoalPosition(const Coord3D *pos, float v);
};

class AIStateMachine
{
public:
	void setGoalWaypoint(const Waypoint *w);
};

#include "../../Include/GameLogic/Module/AIUpdate.h"


class GiantBirdAIUpdate
{
public:
	char m_pad0[8];
	Object *m_object; // +8
	char m_padC[0x30 - 0x0c];
	StateMachine *m_machine; // +0x30
	char m_pad34[0x528 - 0x34];
	int m_flag528; // +0x528
	void privateFollowPath(const Rva0035149F &path, const Object *obstacle, const Waypoint *goal, int unk);
};

void GiantBirdAIUpdate::privateFollowPath(const Rva0035149F &path, const Object *obstacle, const Waypoint *goal, int unk)
{
	if (!m_object->isMobile())
		return;
	m_machine->vslot14();
	unsigned int n = (unsigned int)(path.m_finish - path.m_start);
	if (n > 0)
	{
		Coord3D *last = path.m_start + n - 1;
		Coord3D tmp;
		tmp.x = last->x;
		tmp.y = last->y;
		tmp.z = last->z;
		m_machine->setGoalPosition(&tmp, 3.4028235e+38f);
	}
	((Rva00351759 *)m_machine)->rva00351759(path);
	((AIStateMachine *)this)->setGoalWaypoint(goal);
	((AIUpdateInterface *)this)->ignoreObstacle(obstacle);
	m_machine->vslot20(0x3f6);
	m_flag528 = 1;
}
