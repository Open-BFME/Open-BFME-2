// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
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
#include <vector>
#include "ascii_string.h"
#include "../GameLogicObjectLookupView.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"

typedef bool Bool;
typedef float Real;
#define NULL 0

extern GameLogic *TheGameLogic;


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
	unsigned char m_pad68[0x2E4 - 0x68];
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
private:
	void *m_vtbl;
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad08[0x38 - 0x08];
	Coord3D m_pos; // +0x38
	unsigned char m_pad44[0x8C - 0x44];
	Object *m_next; // +0x8C
	unsigned char m_pad90[0x94 - 0x90];
	unsigned char m_status; // +0x94
	unsigned char m_pad95[0x1C8 - 0x95];
	unsigned char m_disabledMask; // +0x1C8
	unsigned char m_pad1C9[0x250 - 0x1C9];
	void *m_contain; // +0x250
	unsigned char m_pad254[0x258 - 0x254];
	AIUpdateInterface *m_ai; // +0x258
	unsigned char m_pad25C[0x304 - 0x25C];
	Team *m_team; // +0x304
};

class Player
{
public:
	Team *getDefaultTeam() const { return m_defaultTeam; }
private:
	unsigned char m_pad00[0x2EC];
	Team *m_defaultTeam; // +0x2EC
};

struct TeamTemplateInfo
{
	unsigned char m_pad00[0x210 - 0x1E8];
	Bool m_isAIRecruitable; // proto +0x210
	unsigned char m_pad211[0x21C - 0x211];
	int m_productionPriority; // proto +0x21C
};

class TeamPrototype
{
public:
	const TeamTemplateInfo *getTemplateInfo() const { return &m_teamTemplate; }
private:
	unsigned char m_pad00[0x1E8];
	TeamTemplateInfo m_teamTemplate;
};

class Team
{
public:
	Player *getControllingPlayer() const;
	const TeamPrototype *getPrototype() const { return m_proto; }
	Bool isActive() const { return m_active; }
	Bool rva003A123C(Object **recruit, Real *distSqr, Object *obj, const ThingTemplate *tTemplate, const Coord3D *teamHome);
	Object *tryToRecruit(const ThingTemplate *tTemplate, const Coord3D *teamHome, Real maxDist, int a4, int a5, int a6);
	Bool rva003A1542(const ThingTemplate *tTemplate, int minCount);
private:
	unsigned char m_pad00[0x30];
	TeamPrototype *m_proto; // +0x30
	unsigned char m_pad34[0x5D - 0x34];
	Bool m_active; // +0x5D
	unsigned char m_pad5E[0x110 - 0x5E];
	Bool m_isRecruitablitySet; // +0x110
	Bool m_isRecruitable; // +0x111
};

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
