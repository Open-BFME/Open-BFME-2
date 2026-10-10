// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ?rva004E923E@GateOpenBehaviorList@@QAE_NPAVObject@@@Z, retail 0x004E923E, 249 bytes.
// Gate list path check for one object: finds the gate closest to the
// position recorded for the object's controlling player (rowed
// 0x002A8AB1 lookup on g_00DFEEF8 then the rowed 0x004EBF4B position copy)
// among the gates that player owns (rowed closest-owned scan 0x004E9179).
// Without such a gate the answer is false. Otherwise it aims 100 units past
// the gate along the direction from that position (rowed Coord3D::normalize
// 0x000035B6) and answers true when TheAI's pathfinder (+0x10) finds no
// quick path from the object's position (+0x38) to that point (pinned
// Pathfinder::QuickDoesPathExist 0x002F477E). WorldBuilder twin 0x01376E30
// (unnamed) has the same steps through Coord3D sub/scale/add and
// GateOpenAndCloseBehavior::getPosition (retail's rowed disp8 getter
// 0x004989EE). No direct caller in retail; the name keeps the address.

class Player;
#include "../../../../../Libraries/Include/Lib/Coord3D.h"

class Object
{
public:
	Player *getControllingPlayer() const;
	const Coord3D *getPosition() const { return &m_pos; }

private:
	char m_pad00[0x38];
	Coord3D m_pos; // +0x38
};

struct Rva002A8AB1Record;

class Rva002A8F24
{
public:
	Rva002A8AB1Record *rva002A8AB1(void *player);
};

extern Rva002A8F24 *g_00DFEEF8;

class Rva004EBF4B
{
public:
	Coord3D rva004EBF4B();
};

class Rva004989EEAddDwordField
{
public:
	int get() const;
};

class Pathfinder
{
public:
	bool QuickDoesPathExist(Object *obj, const Coord3D *from, const Coord3D *to, int flags);
};

class AI
{
public:
	Pathfinder *pathfinder() { return m_pathfinder; }

private:
	char m_pad00[0x10];
	Pathfinder *m_pathfinder; // +0x10
};

extern AI *TheAI;

class GateOpenBehaviorList
{
public:
	void *rva004E9179(const Coord3D *pos, const Player *player);
	bool rva004E923E(Object *obj);

private:
	void **m_begin; // +0
	void **m_end; // +4
};

bool GateOpenBehaviorList::rva004E923E(Object *obj)
{
	Rva004EBF4B *record = (Rva004EBF4B *)g_00DFEEF8->rva002A8AB1(obj->getControllingPlayer());
	Coord3D pos = record->rva004EBF4B();
	void *gate = rva004E9179(&pos, obj->getControllingPlayer());
	if (gate != 0)
	{
		const Coord3D *gatePos = (const Coord3D *)((Rva004989EEAddDwordField *)gate)->get();
		Coord3D target;
		target.x = gatePos->x;
		target.y = gatePos->y;
		target.z = gatePos->z;
		Coord3D dir;
		dir.x = target.x - pos.x;
		dir.y = target.y - pos.y;
		dir.z = target.z - pos.z;
		dir.normalize();
		// A member-wise copy of the direction that never escapes: retail keeps
		// it in registers and stores only the target.
		Coord3D off;
		off.x = dir.x;
		off.y = dir.y;
		off.z = dir.z;
		off.x *= 100.0f;
		off.y *= 100.0f;
		off.z *= 100.0f;
		target.x += off.x;
		target.y += off.y;
		target.z += off.z;
		if (!TheAI->pathfinder()->QuickDoesPathExist(obj, obj->getPosition(), &target, 0))
			return true;
	}
	return false;
}
