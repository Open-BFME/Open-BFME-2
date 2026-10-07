// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/bfmealloc /Ireference/shims/moduledata
// stlport

// ?getControllingPlayer@Team@@QBEPAVPlayer@@XZ, retail 0x0039D7CF (12 bytes).
// Team::getControllingPlayer is `return m_proto ? m_proto->m_owningPlayer :
// NULL`. Retail-measured BFME2 layout: Team::m_proto is at +0x30 here and the
// prototype owner holds m_owningPlayer at +0x08. Dedicated TU so the pin
// (Object::getControllingPlayer tail target) resolves to a row.
//
// ?getRelationship@Team@@QBE?AW4Relationship@@PBV1@@Z, retail 0x003A0FD2
// (137 bytes). BFME1 donor Team::getRelationship (Team.cpp:2128): the
// team-override map, then the player-override map keyed by the other team's
// controlling player index, then the controlling player's own relationship.
// BFME2 retail layout: Team+0x34 is the team key (Player 0x002AD0C6 inlines
// the same +0x34 read), Team+0x118 the team-override map and Team+0x11C the
// player-override map (the BFME1 donor keeps them at +0xEC/+0xF0),
// Player+0x54 is m_playerIndex. Callees: the rowed hashtable _M_find
// 0x002888D4 and Player::getRelationship(const Team *) 0x002AD0C6; 9 callers
// such as 0x002760E1 and 0x0028D243. Retail keeps state across the
// getControllingPlayer call in a volatile register, which cl only does when
// that callee was compiled earlier in the same TU, so it joins this file; the
// TU takes the STLport flags its hash_map needs (the two earlier bodies are
// unchanged by them).
//
// ?updateState@TeamPrototype@@QAEXXZ, retail 0x003A34AC (158 bytes), pinned
// from the byte-verified Player::updateTeamStates. Zero Hour's
// TeamPrototype::updateState over the +0x334 team list with Zero Hour's
// DLINK_ITERATOR shape (TeamPrototypeTeamIterators.cpp: the advance calls
// through &Team::dlink_next_TeamInstanceList with Team's two-base zero
// this-adjustment): each team's updateState (0x0039F0E3, pinned from this
// call), then the empty-team sweep -- singleton bit 0 of +0x18, the
// controlling player's default team at +0x2EC, the team's active flag at
// +0x5D -- deleting through TheTeamFactory's teamAboutToBeDeleted
// (0x003A3048) and BFME 2's deleteInstance shape. Retail reuses ecx for the
// second getControllingPlayer call, so it joins this file too; Team gains
// its two polymorphic bases here (MemoryPoolObject, Snapshot), which
// leaves every offset above unchanged.
//
// ?rva003A0CD1@TeamPrototype@@QAEXXZ, retail 0x003A0CD1 (57 bytes), called
// out of line by ~TeamPrototype. Zero Hour's destructor tail (owner and factory
// list removal) with one BFME 2 addition: the owner's record in the
// g_00DFEEF8 registry (rowed lookup 0x002A8AB1) also drops this prototype
// through 0x004EC07D, an 11-byte forward to its +0x90 member.
//
// ?teamAboutToBeDeleted@TeamPrototype@@QAEXPAVTeam@@@Z, retail 0x003A2CA5
// (70 bytes), pinned from the byte-verified TeamFactory::teamAboutToBeDeleted.
// Zero Hour's body over the same team-list iterator: each team drops its
// override relationship with the dying team's id (+0x34, TEAM_ID_INVALID for
// null) through 0x003A2897, whose map-erase body is Zero Hour's
// Team::removeOverrideTeamRelationship on the +0x118 relation map.
//
// Team recruiting, ported from Zero Hour Team.cpp (isInBuildVariations and
// Team::tryToRecruit) and reconciled to BFME 2's retail bodies:
//   0x003A1201  isInBuildVariations (static; custom register args)
//   0x003A123C  per-object recruit test split out of ZH tryToRecruit's loop
//   0x003A135B  Team::tryToRecruit
//   0x003A1542  count of recruitable objects against a minimum
// Donor facts: the recruitability checks (equivalent template or build
// variation, same controlling player, active team, production priority,
// AI-recruitable template or the per-team recruitability override, AI
// recruitable flag, not HELD) and the squared-distance selection.
// Target facts: Team prototype at +0x30, template info at prototype+0x1E8
// (AI-recruitable +0x210, production priority +0x21C), active +0x5D,
// recruitability set/value +0x110/+0x111; Object template +0x04, position
// +0x38, next +0x8C, destroyed bit +0x94, HELD bit +0x1C8, contain +0x250,
// AI +0x258, team +0x304; Player default team +0x2EC; ThingTemplate name
// +0x64, behaviour module info +0x2E4, build variations +0x330.
// BFME 2 deltas (target): tryToRecruit takes three extra unused arguments
// (ret 0x18), resolves a two-member horde from the first behaviour module's
// v21 data and recruits the pair through the leader's contain (vslots
// +0x70/+0x74), then sets status 0x44 on the recruit via 0x00346C53.
// The 0x003A1542 count body repeats the loop with the ZH recruitability
// order and no destroyed test; its identity beyond that is not recovered.
//
// ?rva003A1AA3@Team@@QAEHPBVThingTemplate@@PAVObjectTypes@@HM@Z, retail
// 0x003A1AA3 (407 bytes). Recruits up to maxCount of the controlling player's
// objects to this team, nearest first within maxDist of the team position
// (0x0039DA2A): an object qualifies by an equivalent template or build
// variation of the given template, or by the ObjectTypes filter (0x00376A84),
// then by Zero Hour tryToRecruit's team checks (other active team of lower
// production priority, recruitable by default team, template or per-team
// override, AI recruitable, not HELD). Each pick joins through
// Object::setTeam (0x00298AE4); eax returns the count. Target facts only:
// the identity is not recovered beyond the Zero Hour recruit checks it shares.
// Retail calls 0x0039DA2A on the ecx that getControllingPlayer preserved, so
// the recruit bodies joined this TU; they are unchanged by its knowledge, and
// the earlier bodies are unchanged by the recruit bodies' STLport shims.
#include <vector>
#include <hash_map>
#include "ascii_string.h"
#include "Common/Snapshot.h"
#include "../GameLogicObjectLookupView.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"

typedef bool Bool;
typedef float Real;
typedef unsigned int UnsignedInt;
#define NULL 0

extern GameLogic *TheGameLogic;

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2
};

typedef std::hash_map<int, Relationship, std::hash<int>, std::equal_to<int> > PlayerRelationMapType;

struct RetailPlayerRelationMap
{
	void *m_vtbl;
	PlayerRelationMapType m_map;
};

class ModuleData;

class Rva003A135BHordeData
{
public:
	unsigned int getNameCount() const { return m_names.size(); }
	const AsciiString *getName(int i) const { return m_names[i]; }
private:
	unsigned char m_pad00[0x1A4];
	_STL::vector<const AsciiString *> m_names; // +0x1A4
};

class ModuleData
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20();
	virtual const Rva003A135BHordeData *v21() const;
};

class ModuleInfo
{
	const void *m_begin;
	const void *m_end;
	const void *m_storage;
public:
	int getCount() const
	{
		return ((const char *)m_end - (const char *)m_begin) / 20;
	}
	const ModuleData *getNthData(int i) const;
};

class ThingTemplate;

class Rva002D06CA
{
public:
	void *rva002D06CA(const AsciiString *key);
};
extern Rva002D06CA *TheThingFactory;

class ThingTemplate
{
public:
	const ModuleInfo &getBehaviorModuleInfo() const { return m_behaviorModuleInfo; }
	Bool isEquivalentTo(const ThingTemplate *tt) const;
	const AsciiString &getName() const { return m_name; }
	const _STL::vector<AsciiString> &getBuildVariations() const { return m_buildVariations; }
private:
	unsigned char m_pad00[0x64];
	AsciiString m_name; // +0x64
	unsigned char m_pad68[0x108 - 0x68];
public:
	UnsignedInt m_kind0; // +0x108
	unsigned char m_pad10C[0x11A - 0x10C];
	unsigned char m_kindByte11a; // +0x11A
private:
	unsigned char m_pad11B[0x2E4 - 0x11B];
	ModuleInfo m_behaviorModuleInfo; // +0x2E4
	unsigned char m_pad2F0[0x330 - 0x2F0];
	_STL::vector<AsciiString> m_buildVariations; // +0x330
};

class Player;
class Team;

class Object;

class Rva003A135BHordeContain
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual Bool v28(Object *member);
	virtual Object *v29(Object *member, Object *leader, int flag);
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_RVA003A135B = 0x44
};

class AIUpdateInterface
{
public:
	Bool isRecruitable() const { return m_isRecruitable; }
private:
	unsigned char m_pad00[0x3BE];
	Bool m_isRecruitable; // +0x3BE
};

class Object
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	const Coord3D *getPosition() const { return &m_pos; }
	Player *getControllingPlayer() const;
	Team *getTeam() const { return m_team; }
	AIUpdateInterface *getAIUpdateInterface() const { return m_ai; }
	Bool isDisabledByType_HELD() const { return (m_disabledMask & 8) != 0; }
	Bool isDestroyed() const { return (m_status & 1) != 0; }
	Object *getNextObject() { return m_next; }
	void *getContain() const { return m_contain; }
	void *rva0028C197() const;
	void rva00346C53(ObjectStatusTypes status, Bool set);
	void setTeam(Team *team);
private:
	void *m_vtbl;
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad08[0x38 - 0x08];
	Coord3D m_pos; // +0x38
	unsigned char m_pad44[0x74 - 0x44];
public:
	unsigned int m_id; // +0x74
private:
	unsigned char m_pad78[0x8C - 0x78];
	Object *m_next; // +0x8C
	unsigned char m_pad90[0x94 - 0x90];
public:
	unsigned char m_status; // +0x94
private:
	unsigned char m_pad95[0x1C8 - 0x95];
	unsigned char m_disabledMask; // +0x1C8
	unsigned char m_pad1C9[0x250 - 0x1C9];
	void *m_contain; // +0x250
	unsigned char m_pad254[0x258 - 0x254];
	AIUpdateInterface *m_ai; // +0x258
	unsigned char m_pad25C[0x304 - 0x25C];
	Team *m_team; // +0x304
	unsigned char m_pad308[0x438 - 0x308];
public:
	unsigned char m_dead; // +0x438
};

class TeamPrototype;
class Player
{
public:
	int getPlayerIndex() const { return m_playerIndex; }
	Relationship getRelationship(const Player *that) const;
	Relationship getRelationship(const Team *that) const;
	Relationship getRelationship(const Object *that) const;
	void removeTeamFromList(TeamPrototype *team);
	Team *getDefaultTeam() const { return m_defaultTeam; }

	char m_pad00[0x54];
	int m_playerIndex; // +0x54
	char m_pad58[0x5c - 0x58];
	int m_playerType; // +0x5C
	char m_pad60[0x2EC - 0x60];
	Team *m_defaultTeam; // +0x2EC
	char m_pad2F0[0x330 - 0x2F0];
	RetailPlayerRelationMap *m_playerRelations; // +0x330
	RetailPlayerRelationMap *m_teamRelations; // +0x334
};

class MemoryPoolObject
{
public:
	virtual void *deleteInstance(int flags);
};

template <class OBJCLASS>
class TeamInstanceIterator
{
public:
	typedef OBJCLASS* (OBJCLASS::*GetNextFunc)() const;
private:
	OBJCLASS* m_cur;
	GetNextFunc m_getNextFunc;
public:
	TeamInstanceIterator(OBJCLASS* cur, GetNextFunc getNextFunc) : m_cur(cur), m_getNextFunc(getNextFunc)
	{
	}
	void advance()
	{
		if (m_cur)
			m_cur = ((*m_cur).*(m_getNextFunc))();
	}
	bool done() const
	{
		return m_cur == 0;
	}
	OBJCLASS* cur() const
	{
		return m_cur;
	}
};

class Rva002A9BF2
{
public:
	void *rva002A9BF2();
};

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

class BfmeTab1026
{
public:
	char bfmeHas1026(int a, int b);
};

class ObjectTypes;
class Rva00376A62
{
public:
	Bool rva00376A84(const void *tmpl);
};

struct TeamTemplateInfo
{
	unsigned char m_pad00[0x210 - 0x1E8];
	Bool m_isAIRecruitable; // proto +0x210
	unsigned char m_pad211[0x21C - 0x211];
	int m_productionPriority; // proto +0x21C
};

class Team : public MemoryPoolObject, public Snapshot
{
public:
	Team *dlink_next_TeamInstanceList() const;
	void updateState();
	bool removeOverrideTeamRelationship(unsigned int teamID);
	Object *getFirstItemIn_TeamMemberList() const { return m_dlinkhead_TeamMemberList; }
	Bool isActive() const { return m_active; }
	Player *getControllingPlayer() const;
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
	void rva0039D84A(Object *obj);
	bool rva0039DF87(BfmeTab1026 *tab);
	int getTeamKey() const { return m_key34; }
	Relationship getRelationship(const Team *that) const;
	const TeamPrototype *getPrototype() const { return m_proto; }
	void rva0039DA2A(Coord3D *out) const;
	Bool rva003A123C(Object **recruit, Real *distSqr, Object *obj, const ThingTemplate *tTemplate, const Coord3D *teamHome);
	Object *tryToRecruit(const ThingTemplate *tTemplate, const Coord3D *teamHome, Real maxDist, int a4, int a5, int a6);
	Bool rva003A1542(const ThingTemplate *tTemplate, int minCount);
	int rva003A1AA3(const ThingTemplate *tTemplate, ObjectTypes *objectTypes, int maxCount, Real maxDist);

private:
	unsigned char m_pad08[0x30 - 0x08];
	TeamPrototype *m_proto; // +0x30
	int m_key34; // +0x34
	Object *m_dlinkhead_TeamMemberList; // +0x38
	unsigned char m_pad3C[0x5D - 0x3C];
	Bool m_active; // +0x5D
	unsigned char m_pad5E[0x110 - 0x5E];
	Bool m_isRecruitablitySet; // +0x110
	Bool m_isRecruitable; // +0x111
	unsigned char m_pad112[0x114 - 0x112];
	unsigned int m_target; // +0x114
	RetailPlayerRelationMap *m_teamRelations; // +0x118
	RetailPlayerRelationMap *m_playerRelations; // +0x11C
};

class TeamFactory
{
public:
	void teamAboutToBeDeleted(Team *team);
	void removeTeamPrototypeFromList(TeamPrototype *team);
};

extern TeamFactory *TheTeamFactory;

enum { TEAM_SINGLETON = 0x01 };

struct Rva002A8AB1Record
{
	void rva004EC07D(TeamPrototype *proto);
};
class Rva002A8F24
{
public:
	Rva002A8AB1Record *rva002A8AB1(void *owner);
};
extern Rva002A8F24 *g_00DFEEF8;

class TeamPrototype
{
public:
	TeamInstanceIterator<Team> iterate_TeamInstanceList() const
	{
		return TeamInstanceIterator<Team>(m_dlinkhead_TeamInstanceList, &Team::dlink_next_TeamInstanceList);
	}
	bool getIsSingleton() const { return (m_flags & TEAM_SINGLETON) != 0; }
	Player *getControllingPlayer() const { return m_owningPlayer; }
	const TeamTemplateInfo *getTemplateInfo() const { return &m_teamTemplate; }
	void updateState();
	void teamAboutToBeDeleted(Team *team);
	void rva003A0CD1();

private:
	unsigned char m_pad00[0x04];
	TeamFactory *m_factory; // +0x04
	Player *m_owningPlayer; // +0x08
	unsigned char m_pad0C[0x18 - 0x0C];
	int m_flags; // +0x18
	unsigned char m_pad1C[0x1E8 - 0x1C];
	TeamTemplateInfo m_teamTemplate; // +0x1E8
	unsigned char m_pad220[0x334 - 0x220];
	Team *m_dlinkhead_TeamInstanceList; // +0x334
};

Player *Team::getControllingPlayer() const
{
	if( !m_proto )
		return 0;
	return m_proto->getControllingPlayer();
}

// ?rva0039D84A@Team@@QAEXPAVObject@@@Z, retail 0x0039D84A (63 bytes).
// Team::rva0039D84A(Object*): clears Team+0x114 when arg null else stores
// Object+0x74 id only for computer players (Player+0x5c == 1) with non-zero
// difficulty via rowed Rva002A9BF2::rva002A9BF2. Shape matches the BFME1/ZH
// Team::setTeamTargetObject donor with BFME2 deltas (Team proto +0x30 vs +0x04
// target +0x114 vs +0xE8 Player type +0x5c vs +0x2c Object id +0x74 same).
// Same TU as getControllingPlayer so the second call reuses ecx as retail does.
void Team::rva0039D84A(Object *obj)
{
	if( obj == 0 )
	{
		m_target = 0;
		return;
	}
	if( getControllingPlayer()->m_playerType != 1 )
		return;
	if( ((Rva002A9BF2 *)getControllingPlayer())->rva002A9BF2() == 0 )
		return;
	m_target = obj->m_id;
}

Relationship Team::getRelationship(const Team *that) const
{
	RetailPlayerRelationMap *teamMap = m_teamRelations;
	if (!teamMap->m_map.empty() && that != NULL)
	{
		PlayerRelationMapType::const_iterator it = teamMap->m_map.find(that->getTeamKey());
		if (it != teamMap->m_map.end())
		{
			return (*it).second;
		}
	}

	RetailPlayerRelationMap *playerMap = m_playerRelations;
	if (!playerMap->m_map.empty() && that != NULL)
	{
		Player *thatPlayer = that->getControllingPlayer();
		if (thatPlayer != NULL)
		{
			PlayerRelationMapType::const_iterator it = playerMap->m_map.find(thatPlayer->getPlayerIndex());
			if (it != playerMap->m_map.end())
			{
				return (*it).second;
			}
		}
	}

	return getControllingPlayer()->getRelationship(that);
}

bool Team::rva0039DF87(BfmeTab1026 *tab)
{
	Player *player = getControllingPlayer();
	for (DLINK_ITERATOR<Object> iter = iterate_TeamMemberList(); !iter.done(); iter.advance()) {
		Object *cur = iter.cur();
		if ((cur->m_dead & 1) != 0)
			continue;
		if ((cur->m_status & 1) != 0)
			continue;
		const ThingTemplate *tmpl = cur->getTemplate();
		if ((int)(tmpl->m_kind0 & 0x80) != 0)
			continue;
		if ((tmpl->m_kind0 & 0x2000000) != 0)
			continue;
		if ((tmpl->m_kindByte11a & 0x10) != 0)
			continue;
		if (tab->bfmeHas1026((int)cur, (int)player) != 0)
			return true;
	}
	return false;
}

void TeamPrototype::updateState()
{
	for (TeamInstanceIterator<Team> iter = iterate_TeamInstanceList(); !iter.done(); iter.advance())
	{
		iter.cur()->updateState();
	}
	/* remove empty teams. */
	bool done = false;
	while (!done) {
		done = true;
		for (TeamInstanceIterator<Team> iter = iterate_TeamInstanceList(); !iter.done(); iter.advance())
		{
			if (iter.cur()->getFirstItemIn_TeamMemberList() == 0)
			{
				// Team has no members.
				if (this->getIsSingleton())
				{
					continue; // Don't delete singleton teams, even if they are empty.
				}

				if (iter.cur()->getControllingPlayer() && iter.cur()->getControllingPlayer()->getDefaultTeam() == iter.cur())
				{
					// This is the player's default team, so don't remove it.
					continue;
				}

				// don't delete inactive teams - they are under construction
				if (iter.cur()->isActive() == false)
				{
					continue;
				}

				// So remove it
				TheTeamFactory->teamAboutToBeDeleted(iter.cur());
				::operator delete(iter.cur()->deleteInstance(0));

				done = false;
				break;
			}
		}
	}
}

void TeamPrototype::teamAboutToBeDeleted(Team *team)
{
	for (TeamInstanceIterator<Team> iter = iterate_TeamInstanceList(); !iter.done(); iter.advance())
	{
		iter.cur()->removeOverrideTeamRelationship(team ? team->getTeamKey() : 0);
	}
}

void TeamPrototype::rva003A0CD1()
{
	if (m_owningPlayer)
	{
		m_owningPlayer->removeTeamFromList(this);
		Rva002A8AB1Record *record = g_00DFEEF8->rva002A8AB1(m_owningPlayer);
		if (record)
			record->rva004EC07D(this);
	}
	if (m_factory)
		m_factory->removeTeamPrototypeFromList(this);
}

static Bool isInBuildVariations(const ThingTemplate* ttWithVariations, const ThingTemplate* b)
{
	const _STL::vector<AsciiString>& bv = ttWithVariations->getBuildVariations();
	if (bv.empty())
		return false;

	for (_STL::vector<AsciiString>::const_iterator it = bv.begin(); it != bv.end(); ++it)
	{
		if (b->getName() == *it)
			return true;
	}
	return false;
}

Bool Team::rva003A123C(Object **recruit, Real *distSqr, Object *obj, const ThingTemplate *tTemplate, const Coord3D *teamHome)
{
	Player *myPlayer = getControllingPlayer();
	if (!obj->getTemplate()->isEquivalentTo(tTemplate))
	{
		if (!isInBuildVariations(tTemplate, obj->getTemplate()))
			return false;
	}
	if (obj->getControllingPlayer() != myPlayer)
		return false;
	Team *team = obj->getTeam();
	Bool isDefaultTeam = false;
	if (team == myPlayer->getDefaultTeam()) {
		isDefaultTeam = true;
	}
	if (!team->isActive()) {
		return false;
	}
	if (!isDefaultTeam && team->getPrototype()->getTemplateInfo()->m_productionPriority >= getPrototype()->getTemplateInfo()->m_productionPriority) {
		return false;
	}
	Bool teamIsRecruitable = isDefaultTeam;	 // Default team always recruitable.
	if (team->getPrototype()->getTemplateInfo()->m_isAIRecruitable) {
		teamIsRecruitable = true;
	} else if (team->m_isRecruitablitySet) {
		// Check & see if individual team has been marked for recruitability.
		teamIsRecruitable = team->m_isRecruitable;
	}
	if (!teamIsRecruitable) {
		return false;
	}
	if (obj->getAIUpdateInterface() && !obj->getAIUpdateInterface()->isRecruitable()) {
		return false;
	}
	if (obj->isDisabledByType_HELD()) {
		return false;
	}
	Real dx, dy;
	dx = teamHome->x - obj->getPosition()->x;
	dy = teamHome->y - obj->getPosition()->y;

	if (isDefaultTeam && *recruit == NULL) {
		*distSqr = dx*dx+dy*dy;
	} else {
		if (dx*dx+dy*dy > *distSqr) {
			return false;
		}
		*distSqr = dx*dx+dy*dy;
	}
	*recruit = obj;
	return true;
}

Object *Team::tryToRecruit(const ThingTemplate *tTemplate, const Coord3D *teamHome, Real maxDist, int a4, int a5, int a6)
{
	const ModuleInfo &mi = tTemplate->getBehaviorModuleInfo();
	int count = mi.getCount();
	Real distSqr = maxDist*maxDist;
	Real distSqr0 = distSqr;
	Real distSqr1 = distSqr;
	Object *recruit = NULL;
	const ThingTemplate *t0 = NULL;
	const ThingTemplate *t1 = NULL;
	Bool isHorde = false;
	Object *recruit0 = NULL;
	Object *recruit1 = NULL;
	for (int i = 0; i < count; i++) {
		const ModuleData *md = mi.getNthData(i);
		if (md == NULL)
			continue;
		const Rva003A135BHordeData *hd = md->v21();
		if (hd == NULL)
			continue;
		if (hd->getNameCount() > 1) {
			t0 = (const ThingTemplate *)TheThingFactory->rva002D06CA(hd->getName(0));
			t1 = (const ThingTemplate *)TheThingFactory->rva002D06CA(hd->getName(1));
			if (t0 && t1)
				isHorde = true;
			else
				isHorde = false;
		}
		break;
	}

	for (Object *obj = TheGameLogic->getFirstObject(); obj; obj = obj->getNextObject()) {
		if (obj->isDestroyed())
			continue;
		if (rva003A123C(&recruit, &distSqr, obj, tTemplate, teamHome))
			continue;
		if (!isHorde)
			continue;
		if (rva003A123C(&recruit0, &distSqr0, obj, t0, teamHome))
			continue;
		rva003A123C(&recruit1, &distSqr1, obj, t1, teamHome);
	}

	if (isHorde && recruit0 && recruit1) {
		if (recruit != NULL && (distSqr0 > distSqr || distSqr1 > distSqr)) {
			recruit->rva00346C53(OBJECT_STATUS_RVA003A135B, false);
			return recruit;
		}
		if (distSqr1 > distSqr0) {
			Object *tmp = recruit0;
			recruit0 = recruit1;
			recruit1 = tmp;
		}
		Object *leader = recruit0;
		Rva003A135BHordeContain *contain = leader->getContain() ? (Rva003A135BHordeContain *)leader->rva0028C197() : NULL;
		if (contain && contain->v28(recruit1)) {
			Object *r = contain->v29(recruit1, leader, 0);
			if (r)
				recruit = r;
		}
	}
	if (recruit)
		recruit->rva00346C53(OBJECT_STATUS_RVA003A135B, false);
	return recruit;
}

Bool Team::rva003A1542(const ThingTemplate *tTemplate, int minCount)
{
	Player *myPlayer = getControllingPlayer();
	int count = 0;
	for (Object *obj = TheGameLogic->getFirstObject(); obj; obj = obj->getNextObject())
	{
		if (!obj->getTemplate()->isEquivalentTo(tTemplate))
		{
			if (!isInBuildVariations(tTemplate, obj->getTemplate()))
				continue;
		}
		if (obj->getControllingPlayer() != myPlayer)
			continue;
		Team *team = obj->getTeam();
		Bool isDefaultTeam = false;
		if (team == myPlayer->getDefaultTeam()) {
			isDefaultTeam = true;
		}
		if (!team->isActive()) {
			continue;
		}
		if (team->getPrototype()->getTemplateInfo()->m_productionPriority >= getPrototype()->getTemplateInfo()->m_productionPriority) {
			continue;
		}
		Bool teamIsRecruitable = isDefaultTeam;
		if (team->getPrototype()->getTemplateInfo()->m_isAIRecruitable) {
			teamIsRecruitable = true;
		}
		if (team->m_isRecruitablitySet) {
			teamIsRecruitable = team->m_isRecruitable;
		}
		if (!teamIsRecruitable) {
			continue;
		}
		if (obj->getAIUpdateInterface() && !obj->getAIUpdateInterface()->isRecruitable()) {
			continue;
		}
		if (obj->isDisabledByType_HELD()) {
			continue;
		}
		count++;
	}
	return count >= minCount;
}

int Team::rva003A1AA3(const ThingTemplate *tTemplate, ObjectTypes *objectTypes, int maxCount, Real maxDist)
{
	Player *myPlayer = getControllingPlayer();
	Real maxDistSqr = maxDist*maxDist;
	Real distSqr = maxDistSqr;
	int count = 0;
	Coord3D home;
	rva0039DA2A(&home);
	while (count < maxCount)
	{
		Object *recruit = NULL;
		for (Object *obj = TheGameLogic->getFirstObject(); obj; obj = obj->getNextObject())
		{
			Player *player = obj->getControllingPlayer();
			if (player != myPlayer)
				continue;
			Bool match = false;
			if (tTemplate)
			{
				if (obj->getTemplate()->isEquivalentTo(tTemplate))
					match = true;
				if (isInBuildVariations(tTemplate, obj->getTemplate()))
					match = true;
			}
			if (objectTypes && ((Rva00376A62 *)objectTypes)->rva00376A84(obj->getTemplate()))
				match = true;
			if (!match)
				continue;
			Team *team = obj->getTeam();
			Bool isDefaultTeam = false;
			if (team == player->getDefaultTeam())
				isDefaultTeam = true;
			if (team == this)
				continue;
			if (!team->isActive())
				continue;
			if (team->getPrototype()->getTemplateInfo()->m_productionPriority >= getPrototype()->getTemplateInfo()->m_productionPriority)
				continue;
			Bool teamIsRecruitable = isDefaultTeam;
			if (team->getPrototype()->getTemplateInfo()->m_isAIRecruitable)
				teamIsRecruitable = true;
			if (team->m_isRecruitablitySet)
				teamIsRecruitable = team->m_isRecruitable;
			if (!teamIsRecruitable)
				continue;
			if (obj->getAIUpdateInterface() && !obj->getAIUpdateInterface()->isRecruitable())
				continue;
			if (obj->isDisabledByType_HELD())
				continue;
			Real dx = home.x - obj->getPosition()->x;
			Real dy = home.y - obj->getPosition()->y;
			Real d = dx*dx + dy*dy;
			if (d > distSqr)
				continue;
			distSqr = d;
			recruit = obj;
		}
		if (recruit == NULL)
			break;
		count++;
		recruit->setTeam(this);
		distSqr = maxDistSqr;
	}
	return count;
}
