// ?killTeam@Team@@QAEXXZ
// partial score=0.9 date=2026-10-07
// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva003A1C3A@Team@@QAEX_N@Z @0x003A1C3A (224B).
// Team::rva003A1C3A(bool): builds a local list<int> of filtered member
// Objects then notifies each entry's +0x250 target. Retail filters are
// Object+0x94 bit0, Object+0x438 bit0, null +0x250, flag-gated virtual +8,
// virtual +0x114 returning 0 to skip, then list<int> insert via rowed
// 0x005925E2. Second walk reads node data at +8 then target at +0x250 and
// calls virtual +0xA8 with 0. Uses rowed iterate_TeamMemberList 0x00263864,
// pinned DLINK advance at 0x00263526, rowed list insert/clear/base. Callers
// at 0x002AB4A6 0x002AEB1D 0x003A1D63. Honest Team method name.
#include <list>
#include "ascii_string.h"
#include "../GameLogicObjectLookupView.h"

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}


class Rva003A1C3AInner;

class Object;

template<class OBJCLASS>
class DLINK_ITERATOR
{
private:
	OBJCLASS *m_cur;
	unsigned char m_targetAbiState[20];

public:
	void advance();
	bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
};

class Rva003A1C3AInner
{
public:
	virtual void v00();
	virtual void v01();
	virtual int v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void v25();
	virtual void v26();
	virtual void v27();
	virtual void v28();
	virtual void v29();
	virtual void v30();
	virtual void v31();
	virtual void v32();
	virtual void v33();
	virtual void v34();
	virtual void v35();
	virtual void v36();
	virtual void v37();
	virtual void v38();
	virtual void v39();
	virtual void v40();
	virtual void v41();
	virtual void v42(int a);
	virtual void v43();
	virtual void v44();
	virtual void v45();
	virtual void v46();
	virtual void v47();
	virtual void v48();
	virtual void v49();
	virtual void v50();
	virtual void v51();
	virtual void v52();
	virtual void v53();
	virtual void v54();
	virtual void v55();
	virtual void v56();
	virtual void v57();
	virtual void v58();
	virtual void v59();
	virtual void v60();
	virtual void v61();
	virtual void v62();
	virtual void v63();
	virtual void v64();
	virtual void v65();
	virtual void v66();
	virtual void v67();
	virtual void v68();
	virtual unsigned int v69(int a);
};

class Team;
class ThingTemplate;

enum KindOfType
{
	KINDOF_HORDE = 109,
	KINDOF_TECH_BUILDING = 209
};

class ThingTemplate
{
public:
	bool isEquivalentTo(const ThingTemplate *tt) const;
	__forceinline bool isKindOf(KindOfType t) const { return (m_kindof[(unsigned)t >> 3] & (1 << ((unsigned)t & 7))) != 0; }
private:
	unsigned char m_pad00[0x108];
	unsigned char m_kindof[0x20]; // +0x108
};

class ModelConditionBits
{
public:
	unsigned int test(unsigned int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void clear(unsigned int bit)
	{
		m_words[bit >> 5] &= ~(1U << (bit & 0x1f));
	}
private:
	unsigned int m_words[20];
};

enum DamageType { DAMAGE_RVA003A1D1A = 8 };
enum DeathType { DEATH_NORMAL = 0 };
enum ObjectStatusTypes { OBJECT_STATUS_RVA0029A12B = 62 };

class Object
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	__forceinline bool isKindOf(KindOfType t) const { return m_template->isKindOf(t); }
	bool isDestroyed() const { return (m_flag94 & 1) != 0; }
	bool isEffectivelyDead() const { return (m_flag438 & 1) != 0; }
	Team *getTeam() const { return m_team; }
	Object *getContainedBy() const { return m_containedBy; }
	bool testStatus(ObjectStatusTypes bit) const;
	void kill(DamageType damageType, DeathType deathType);
	void setTeam(Team *team);
	void rva0029A12B();
	void rva0028AE6D();

	void *m_vtbl;
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad08[0x94 - 0x08];
	unsigned char m_flag94;
	unsigned char m_pad95[0x10C - 0x95];
	ModelConditionBits m_conditionBits; // +0x10C
	unsigned char m_pad15C[0x250 - 0x15C];
	Rva003A1C3AInner *m_inner250;
	unsigned char m_pad254[0x274 - 0x254];
	Object *m_containedBy; // +0x274
	unsigned char m_pad278[0x304 - 0x278];
	Team *m_team; // +0x304
	unsigned char m_pad308[0x438 - 0x308];
	unsigned char m_flag438;
};

class PlayerTemplate
{
public:
	const AsciiString *getBeaconTemplate() const { return &m_beaconTemplate; }
private:
	unsigned char m_pad00[0x17C];
	AsciiString m_beaconTemplate; // +0x17C
};

class Player
{
public:
	const PlayerTemplate *getPlayerTemplate() const { return m_playerTemplate; }
	Team *getDefaultTeam() const { return m_defaultTeam; }
private:
	unsigned char m_pad00[0x34];
	const PlayerTemplate *m_playerTemplate; // +0x34
	unsigned char m_pad38[0x2EC - 0x38];
	Team *m_defaultTeam; // +0x2EC
};

class PlayerList
{
public:
	Player *getNeutralPlayer() const { return m_neutralPlayer; }
private:
	unsigned char m_pad00[0x18];
	Player *m_neutralPlayer; // +0x18
};
extern PlayerList *ThePlayerList;

class Rva002D06CA
{
public:
	void *rva002D06CA(const AsciiString *key);
};
extern Rva002D06CA *TheThingFactory;

struct BfmeDispatchDelayedLuaEvent
{
	void *m_vtable;
	float m_number;
	unsigned char m_boolean;
	unsigned m_objectID;
	AsciiString m_string;
	unsigned m_type;
};

struct BfmeDelayedLuaEventList
{
	BfmeDelayedLuaEventList();
	~BfmeDelayedLuaEventList();
	void *m_vtable;
	BfmeDispatchDelayedLuaEvent m_events[3];
};

class BfmeObjectEventDispatch
{
public:
	void rva003360D2(int index, void *object, BfmeDelayedLuaEventList *eventList);
};
class LuaScriptEngine;
extern LuaScriptEngine *TheLuaScriptEngine;

extern GameLogic *TheGameLogic;

class Team
{
public:
	Player *getControllingPlayer() const;
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
	void deleteTeam(bool ignoreDead);
	void rva003A1C3A(bool flag);
	void killTeam();
};

// Team::deleteTeam, retail 0x003A10FE (259 bytes), ported from Zero Hour's
// GameEngine/Source/Common/RTS/Team.cpp. Target evidence: the controlling
// player's default team is Player +0x2EC; the evacuation list calls the
// rowed list<int> base ctor/insert/base dtor (0x004EC36C, 0x005925E2,
// 0x004EC395), so the members are held as ints exactly as rva003A1C3A
// does; getContain is Object +0x250 with getContainCount at vslot +0x114
// and removeAllContained at +0xA8; isEffectivelyDead is Object +0x438 bit 0;
// TheGameLogic->destroyObject is the rowed 0x00242C09.
void Team::deleteTeam(bool ignoreDead)
{
	if (this == getControllingPlayer()->getDefaultTeam()) {
		_STL::list<int> guysToMakeEvacuate;
		for (DLINK_ITERATOR<Object> iter = iterate_TeamMemberList(); !iter.done(); iter.advance()) {
			Object *obj = iter.cur();
			int objVal = (int)obj;
			if (!obj)
				continue;
			Rva003A1C3AInner *contain = obj->m_inner250;
			if (contain && contain->v69(0) > 0)
				guysToMakeEvacuate.push_back(objVal);
		}
		for (_STL::list<int>::iterator it = guysToMakeEvacuate.begin(); it != guysToMakeEvacuate.end(); ) {
			Object *obj = (Object *)(*it);
			it++;
			Rva003A1C3AInner *contain = obj->m_inner250;
			if (contain)
				contain->v42(0);
		}
	}

	for (DLINK_ITERATOR<Object> iter = iterate_TeamMemberList(); !iter.done(); iter.advance()) {
		Object *obj = iter.cur();
		if (!obj)
			continue;
		if (ignoreDead && (obj->m_flag438 & 1) != 0)
			continue;
		TheGameLogic->destroyObject(obj);
	}
}

void Team::rva003A1C3A(bool flag)
{
	_STL::list<int> tmp;
	for (DLINK_ITERATOR<Object> iter = iterate_TeamMemberList(); !iter.done(); iter.advance()) {
		Object *cur = iter.cur();
		int curVal = (int)cur;
		if (cur == 0)
			continue;
		if ((cur->m_flag94 & 1) != 0)
			continue;
		if ((cur->m_flag438 & 1) != 0)
			continue;
		Rva003A1C3AInner *inner = cur->m_inner250;
		if (inner == 0)
			continue;
		if (flag) {
			if (inner->v02() == 0)
				continue;
		}
		if (inner->v69(0) <= 0)
			continue;
		tmp.push_back(curVal);
	}
	for (_STL::list<int>::iterator it = tmp.begin(); it != tmp.end(); ++it) {
		Object *obj = (Object *)(*it);
		Rva003A1C3AInner *inner = obj->m_inner250;
		if (inner == 0)
			continue;
		inner->v42(0);
	}
	tmp.clear();
}

// Team::killTeam, retail 0x003A1D1A (587 bytes), from Zero Hour Team.cpp.
// NEAR MISS (595 bytes): only the member-classification loop differs --
// retail keeps this in EDI and the member in ESI straight from the loop
// test; this source keeps this in ESI and copies the member from EAX to
// EDI. Everything after that loop (kill, neutral capture with Lua event 15
// "neutral" and model-condition bit 119, horde-aware release via
// 0x0029A12B) is byte-exact.
void Team::killTeam()
{
	_STL::list<int> objectsToKill;
	_STL::list<int> objectsToRelease;
	_STL::list<int> objectsToNeutral;

	rva003A1C3A(false);

	const ThingTemplate *beaconTemplate = (const ThingTemplate *)TheThingFactory->rva002D06CA(getControllingPlayer()->getPlayerTemplate()->getBeaconTemplate());

	for (DLINK_ITERATOR<Object> iter = iterate_TeamMemberList(); !iter.done(); iter.advance()) {
		Object *obj = iter.cur();
		int objVal = (int)obj;
		if (!obj)
			continue;
		if (obj->isDestroyed())
			continue;
		if (obj->isEffectivelyDead() && !obj->getTemplate()->isEquivalentTo(beaconTemplate))
			continue;
		if (obj->isKindOf(KINDOF_TECH_BUILDING)) {
			objectsToNeutral.push_back(objVal);
			continue;
		}
		Team *objTeam = obj->getTeam();
		if (obj->testStatus(OBJECT_STATUS_RVA0029A12B))
			objectsToRelease.push_back(objVal);
		else if (objTeam == this)
			objectsToKill.push_back(objVal);
	}

	_STL::list<int>::iterator objIt;
	for (objIt = objectsToKill.begin(); objIt != objectsToKill.end(); ++objIt) {
		Object *obj = (Object *)(*objIt);
		obj->kill(DAMAGE_RVA003A1D1A, DEATH_NORMAL);
	}
	for (objIt = objectsToNeutral.begin(); objIt != objectsToNeutral.end(); ++objIt) {
		Object *obj = (Object *)(*objIt);
		obj->setTeam(ThePlayerList->getNeutralPlayer()->getDefaultTeam());
		BfmeDelayedLuaEventList list;
		{
			AsciiString value("neutral");
			list.m_events[0].m_string = value;
			list.m_events[0].m_type = 4;
		}
		reinterpret_cast<BfmeObjectEventDispatch *>(TheLuaScriptEngine)->rva003360D2(15, obj, &list);
		if (obj->m_conditionBits.test(119) != 0) {
			obj->m_conditionBits.clear(119);
			obj->rva0028AE6D();
		}
	}
	for (objIt = objectsToRelease.begin(); objIt != objectsToRelease.end(); ++objIt) {
		Object *obj = (Object *)(*objIt);
		Object *container = obj->getContainedBy();
		((container && container->isKindOf(KINDOF_HORDE)) ? container : obj)->rva0029A12B();
	}
	objectsToKill.clear();
	objectsToRelease.clear();
	objectsToNeutral.clear();
}
