// stlport
// cl: /ICode/Libraries/Include /O1 /G7 /arch:SSE /MD /DNDEBUG
//
// ?setUnitsShouldHunt@Player@@QAEX_NW4CommandSourceType@@@Z, retail
// 0x002AE9B8, 231 bytes. Player orders every unit to hunt or idle: store the
// hunt flag at +0x33D, walk the prototype list at +0x32C and every team's
// member list, skip KindOf-masked (bits 14/16/91) and status-38 objects,
// leave the group, and send aiHunt/aiIdle through the AI at object+0x258
// (commands at +0x20).
//
// ZH Player.cpp setUnitsShouldHunt donor supplies the semantics; the loop
// skeleton, Team PMF idiom (eight-byte member pointer, pfn rowed at
// 0x005C4AF5), prototype offsets (+0x32C list, +0x334 team head) and AI
// offsets (+0x258, commands +0x20) follow the landed sibling
// Code/GameEngine/Source/Common/RTS/PlayerTeamCommands.cpp
// (ungarrisonAllUnits 0x002AF037, same triple walk). Differences from the
// sibling: the object walk uses the (obj = cur()) != 0 form with no done()
// call (S2 ScriptConditions idiom, _ReadWriteBarrier first for the
// team-EDI/member-ESI roles), there is no null-team continue, and the AI is
// reused in ESI. All callees rowed: iterate 0x00263864, advance 0x00263526,
// isAnyKindOf 0x0030ADC7, testStatus 0x0004E536, leaveGroup 0x0028C01F,
// aiHunt 0x002AE657, aiIdle 0x001E8A38.
#include <list>
#include <cstring>

extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)

// _List_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _IterTp, class _LeftTraits, class _RightTraits>
static inline bool operator!=(const _List_iterator<_IterTp, _LeftTraits> &a,
			      const _List_iterator<_IterTp, _RightTraits> &b)
{ return a._M_node != b._M_node; }
}

enum CommandSourceType { CMD_FROM_PLAYER, CMD_FROM_SCRIPT, CMD_FROM_AI };

template<int N> class BitFlags
{
public:
	unsigned bits[7];
	BitFlags() { std::memset(bits, 0, sizeof(bits)); }
};

enum ObjectStatusTypes
{
	STATUS_RVA38 = 38
};

class Thing
{
public:
	bool isAnyKindOf(const BitFlags<69> &) const;
};

class AICommandInterface
{
public:
	void aiHunt(CommandSourceType source);
	void aiIdle(CommandSourceType source);
};

struct Rva2AE9B8AI
{
	char pad[32];
	AICommandInterface commands;
};

struct Rva2AE9B8Template
{
	char pad[0x108];
	unsigned kinds;
};

struct Rva2AE9B8Object
{
	void *vt;
	Rva2AE9B8Template *type;
	char pad[0x258 - 8];
	Rva2AE9B8AI *ai;
};

class Object
{
public:
	bool testStatus(ObjectStatusTypes status) const;
	void leaveGroup();
};

template<class T> class DLINK_ITERATOR
{
public:
	typedef T *(T::*GetNextFunc)() const;
	DLINK_ITERATOR(T *cur, GetNextFunc next) : m_cur(cur), m_getNext(next) {}
	T *cur() const { return m_cur; }
	bool done() const { return m_cur == 0; }
	void advance();
private:
	T *m_cur;
	GetNextFunc m_getNext;
};

class Rva2AE9B8TeamBase1 {};
class Rva2AE9B8TeamBase2 {};

#include "../../../Include/Common/TeamBFME2.h"

template<> __forceinline void DLINK_ITERATOR<Team>::advance()
{
	if (m_cur)
		m_cur = (m_cur->*m_getNext)();
}

// The Object member-list iterator carries the 12-byte virtual-inheritance
// member pointer plus padding (24 bytes total, m_cur first); the rowed
// iterate/advance bodies read and write that full extent through the hidden
// return pointer and the iterator home.
template<> class DLINK_ITERATOR<Object>
{
public:
	Object *cur() const { return m_cur; }
	bool done() const { return m_cur == 0; }
	void advance();
private:
	Object *m_cur;
	unsigned char m_abi[20];
};

struct Rva2AE9B8Prototype
{
	char pad[0x334];
	Team *head;
};

class Player
{
public:
	void setUnitsShouldHunt(bool enabled, CommandSourceType source);
private:
	char pad[0x32c];
	_STL::list<Rva2AE9B8Prototype*> prototypes;
	char gap[0x33d - 0x330];
	bool hunt;
};

void Player::setUnitsShouldHunt(bool enabled, CommandSourceType source)
{
	hunt = enabled;
	for (_STL::list<Rva2AE9B8Prototype*>::iterator it = prototypes.begin(); it != prototypes.end(); ++it) {
		for (DLINK_ITERATOR<Team> iter((*it)->head, &Team::dlink_next_TeamInstanceList); !iter.done(); iter.advance()) {
			Team *team = iter.cur();
			if (!team)
				continue;
			Object *obj;
			for (DLINK_ITERATOR<Object> objects = team->iterate_TeamMemberList(); (obj = objects.cur()) != 0; objects.advance()) {
				BitFlags<69> mask;
				mask.bits[0] |= 0x14000;
				reinterpret_cast<unsigned char*>(mask.bits)[11] |= 8;
				if (reinterpret_cast<Thing*>(obj)->isAnyKindOf(mask))
					continue;
				if (obj->testStatus((ObjectStatusTypes)38))
					continue;
				obj->leaveGroup();
				Rva2AE9B8AI *ai = reinterpret_cast<Rva2AE9B8Object*>(obj)->ai;
				if (!ai)
					continue;
				if (enabled)
					ai->commands.aiHunt(source);
				else
					ai->commands.aiIdle(source);
			}
		}
	}
}
