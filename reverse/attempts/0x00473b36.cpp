// ?instigateQuarrel@HordeContain@@UAEXHHUQuarrelPacket@@0@Z
// partial score=0.8 date=2026-10-10
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?instigateQuarrel@HordeContain@@UAEXHHUQuarrelPacket@@0@Z, retail
// 0x00473B36 (543B, ret 0xA0): the method WorldBuilder names
// HordeContain::instigateQuarrel, on the interface at +0x11C of the horde
// contain. Body: Open-BFME-1 HordeContain/MemberSelection00244680.cpp (retail
// 0x00244680 there, donor revision 575ba2b04) re-laid onto BFME 2's offsets:
// the member list comes from the rowed 0x0046247D on the primary subobject
// (this-0x11C), the update module wake runs on it with the Object at
// this-0x114, the two 0x4C-byte packets are copied to +0x98 / +0xE4, the
// picked pair's ids are stored at +0x90 / +0x94 and the per-member quarrel
// timers go into the int-to-int map at +0x130. The "HordeContain.cpp" random
// calls are at lines 8135 and 8162.
#include <list>
#include <map>
#include "../../../../Include/GameLogic/ContainmentListView.h"

class Object;
enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1 };
class UpdateModule
{
public:
	void wake(Object *object, int sleep) { setWakeFrame(object, (UpdateSleepTime)sleep); }
protected:
	void setWakeFrame(Object *object, UpdateSleepTime sleep);
};

int GetGameLogicRandomValue(int low, int high, char *file, int line);
float GetGameLogicRandomValueReal(float low, float high, char *file, int line);

struct QuarrelPacket
{
	int words[0x13];
};

struct Rva0046247DPair
{
	void *a;
	ContainmentList *objects;
};

class Rva0046247D
{
public:
	void rva0046247D(Rva0046247DPair &pair);
};

// The donor's Coord3D arithmetic, kept inline in this unit.
struct QuarrelVector
{
	float x, y, z;
	void zero() { x = 0.0f; y = 0.0f; z = 0.0f; }
	void add(const QuarrelVector *a) { x += a->x; y += a->y; z += a->z; }
	void sub(const QuarrelVector *a) { x -= a->x; y -= a->y; z -= a->z; }
	void set(const QuarrelVector *a) { x = a->x; y = a->y; z = a->z; }
	void scale(float s) { x *= s; y *= s; z *= s; }
};

struct QuarrelMember
{
	unsigned char m_pad00[0x38];
	QuarrelVector position;
	unsigned char m_pad44[0x74 - 0x44];
	int id;
};

#define SLOT(n) virtual void slot##n();
#define SLOT10(n) SLOT(n##0) SLOT(n##1) SLOT(n##2) SLOT(n##3) SLOT(n##4) SLOT(n##5) SLOT(n##6) SLOT(n##7) SLOT(n##8) SLOT(n##9)

class HordeContain
{
public:
	SLOT10(0) SLOT10(1) SLOT10(2) SLOT10(3) SLOT10(4) SLOT10(5) SLOT10(6) SLOT10(7) SLOT10(8) SLOT10(9)
	SLOT(100) SLOT(101) SLOT(102) SLOT(103) SLOT(104) SLOT(105) SLOT(106)
	virtual void slot107();
	virtual void instigateQuarrel(int low, int high, QuarrelPacket packetA, QuarrelPacket packetB);

private:
	unsigned char m_pad04[0x90 - 4];
	int m_first90;
	int m_second94;
	QuarrelPacket m_packetB98;
	QuarrelPacket m_packetAE4;
	_STL::map<int, int> m_timers;
};

void HordeContain::instigateQuarrel(int low, int high, QuarrelPacket packetA, QuarrelPacket packetB)
{
	m_timers.clear();
	Rva0046247DPair outer;
	UpdateModule *update = (UpdateModule *)((char *)this - 0x11C);
	((Rva0046247D *)update)->rva0046247D(outer);
	ContainmentList &members = *outer.objects;
	ContainmentList::iterator first = members.begin();
	int count = (int)members.size();
	if (count < 2)
		return;

	int closest = -1;
	QuarrelVector center;
	center.zero();
	float best = 10000.0f;
	int index = 1;
	for (ContainmentList::iterator it = first; it != members.end(); ++it) {
		QuarrelMember *member = *(QuarrelMember **)&*it;
		if (!member) {
			slot107();
			return;
		}
		center.add(&member->position);
	}
	center.scale(1.0f / (float)count);
	for (ContainmentList::iterator it = first; it != members.end(); ++it, ++index) {
		QuarrelMember *member = *(QuarrelMember **)&*it;
		if (!member) {
			slot107();
			return;
		}
		QuarrelVector diff;
		diff.set(&member->position);
		diff.sub(&center);
		float distance = diff.x * diff.x + diff.y * diff.y;
		if (distance < best) {
			closest = index;
			best = distance;
		}
	}
	int leader = closest;
	if (leader == -1)
		leader = 1;
	int other = leader + GetGameLogicRandomValue(1, count - 1, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Contain\\HordeContain\\HordeContain.cpp", 8135);
	if (other > count)
		other -= count;
	m_packetB98 = packetB;
	m_packetAE4 = packetA;
	index = 1;
	for (ContainmentList::iterator it = first; it != members.end(); ++it, ++index) {
		QuarrelMember *member = *(QuarrelMember **)&*it;
		if (!member) {
			slot107();
			return;
		}
		if (index == other)
			m_first90 = member->id;
		else if (index == leader)
			m_second94 = member->id;
		else {
			int &timer = m_timers[member->id];
			timer = (int)GetGameLogicRandomValueReal((float)low, (float)high, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Contain\\HordeContain\\HordeContain.cpp", 8162);
		}
	}
	update->wake(*(Object **)((char *)this - 0x114), 1);
}
