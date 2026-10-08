// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?killTeam@Team@@QAEXXZ @0x003A1D1A 587B.
// Identity: Zero Hour Team.cpp Team::killTeam (donor for flow, list names and
// the kill / neutral / release split); the one call into the rowed
// Team::rva003A1C3A (0x003A1C3A) with false matches deleteTeam's sibling.
// BFME 2 deltas (target): members equivalent to the player template's beacon
// (ThingFactory 0x002D06CA on PlayerTemplate +0x17C) are kept even when dead;
// KindOf 209 members go neutral with Lua event 15 "neutral" and clear
// model-condition bit 119 (0x0028AE6D); status-62 members are released
// through 0x0029A12B on their horde container when there is one; lists hold
// the members as ints through the rowed list<int> calls. Shape: the DLINK
// iterator and Team::iterate_TeamMemberList are defined in-TU over the
// virtual-inheritance Object skeleton (TeamUpdateState.cpp); with the
// declared-only iterator the first loop swapped this/member registers.
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

class BfmeObjectVirtualTail { public: unsigned char m_vt[4]; };

class BfmeObjectVbptrCarrier : public virtual BfmeObjectVirtualTail
{
public:
	unsigned char m_carrier[4];
};

class BfmeObjectVtbl { public: virtual void bfmeObjectSlot0(); };

class BfmeObjectDlinkBase
{
public:
	Object *dlink_next_TeamMemberList() const;
};

class BfmeObjectDlinkPad
{
public:
	const ThingTemplate *m_template;	// +0x04
	unsigned char m_pad[0x60];
};

class Object : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
	public BfmeObjectDlinkPad, public BfmeObjectVbptrCarrier
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

	unsigned char m_pad070[0x94 - 0x70];
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

// DLINK_ITERATOR<Object>::advance (0x00263526) and
// Team::iterate_TeamMemberList (0x00263864) are defined as in the header;
// neither is inlined here.
template<class OBJCLASS>
class DLINK_ITERATOR
{
public:
	typedef OBJCLASS *(OBJCLASS::*GetNextFunc)() const;
	DLINK_ITERATOR(OBJCLASS *cur, GetNextFunc getNextFunc) : m_cur(cur), m_getNextFunc(getNextFunc) {}
	void advance() { if (m_cur) m_cur = ((*m_cur).*(m_getNextFunc))(); }
	bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
private:
	OBJCLASS *m_cur;
	GetNextFunc m_getNextFunc;
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
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const { return DLINK_ITERATOR<Object>(m_head, &Object::dlink_next_TeamMemberList); }
	void rva003A1C3A(bool flag);
	void killTeam();
private:
	unsigned char m_pad00[0x38];
	Object *m_head; // +0x38
};

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
