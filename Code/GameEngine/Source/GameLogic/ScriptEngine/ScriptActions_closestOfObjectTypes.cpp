// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB
// stlport
//
// BFME2 script actions over the object of a type nearest a team.
//
//   0x003C2662  (called from the dispatcher 0x003CA4BE at 0x003CDF80): the
//               team's new group is ordered (0x00372571, source 1) to the
//               closest object of the given types or template to the team's
//               centre
//   0x003C276A  (called from the dispatcher 0x003CA4BE at 0x003CDFAF): the
//               player-mask form of 0x003C2662: for each player of the
//               named mask the closest object of the types or template to
//               the team's centre that player owns; the nearest of those
//               (within 99999) is where the team's new group is ordered
//   0x003C4625  (called from the action dispatcher 0x003CA4BE at
//               0x003CDD4D): the closest object to the team's centre that
//               the team's controlling player owns, of the given ObjectTypes
//               list (through the helper 0x003C24F0) or else the given
//               template; the script name then goes to it (0x00208968 and
//               0x0020A5FF, both TheScriptEngine members)
//   0x003C55A6  (called from the dispatcher 0x003CA4BE at 0x003CC7FF): the
//               same search from the team's centre for each player of the
//               named player mask in turn; the first hit goes to the named
//               apply 0x003C420A
//   0x003C33C9  (called from the dispatcher 0x003CA4BE at 0x003CE72B): the
//               closest object to the named team's centroid (0x0039DA2A)
//               that the named player owns, of the given ObjectTypes list
//               (0x003C24F0, passing the flag) or else the given template
//               (with the flag, also the 0x0026149C(false) filter); the
//               script name then goes to it
//   0x003C56D6  (called from the dispatcher at 0x003CC7B3): the closest
//               object of the types or template to the team's centre, any
//               owner, goes to the named apply 0x003C420A
//
// The filters are BFME2's partition filter chain (the view
// AIStructureCreepTactic.cpp documents): a vptr, the +0x04 link to the next
// filter (PartitionFilter::link 0x00625790), then each filter's members;
// address-derived names after allow (slot 1), the ctors being inline.
#include "../../../Include/GameLogic/ObjectTypesClass.h"

class Object;
class Player;

#include "../../../Include/GameLogic/PartitionFilter.h"

class ThingTemplate;

// vftable 0x00BFAD28, allow 0x0026137E, slot 2 0x00261368: +0x08 a
// player, +0x0C whether a hit allows.
#include "../../../Include/GameLogic/Rva0026137EFilter.h"

// vftable 0x00C1FDEC, allow 0x00261750: +0x08 a thing template, +0x0C
// whether a match allows (Zero Hour's PartitionFilterThing).
class Rva00261750Filter : public Rva000421C8
{
public:
	Rva00261750Filter(const ThingTemplate *tmpl, bool match) : m_template(tmpl), m_match(match) {}
	virtual bool allow(Object *obj);
	const ThingTemplate *m_template; // +0x08
	bool m_match; // +0x0C
	char m_pad0D[0x3];
};

// vftable 0x00C1FE10, allow 0x0026149C: +0x08 a flag.
class Rva0026149CFilter : public Rva000421C8
{
public:
	Rva0026149CFilter(bool flag) : m_flag(flag) {}
	virtual bool allow(Object *obj);
	bool m_flag;
};

#include "../../../../Libraries/Include/Lib/Coord3D.h"

class Object
{
public:
	const Coord3D *getPosition() const { return &m_pos; }
	char m_pad000[0x38];
	Coord3D m_pos;			// +0x38
};


#include "../../../Include/Common/ThingFactory.h"
extern ThingFactory *TheThingFactory;

#include "../../Common/PartitionRangeQueryCallView.h"
extern PartitionManager *ThePartitionManager;

#define REALLY_FAR (100000 * 10.0f)

#include "../../../Include/GameLogic/ScriptParameter.h"

class AIGroup;

#include "../../../Include/Common/TeamBFME2.h"

#include "../../../Include/Common/PlayerList.h"
extern PlayerList *ThePlayerList;

// The argument block 0x00372571 takes (built inline by its callers).
#include "../../../Include/Common/Rva00372571Params.h"

#include "../../../Include/GameLogic/AIGroup.h"

#include "../../../Include/GameLogic/AI.h"
extern AI *TheAI;

#include "../../../Include/GameLogic/ScriptEngine.h"
extern ScriptEngine *TheScriptEngine;

class AsciiString;
class BfmeTargetBH;

class ScriptActions
{
public:
	Object *rva003C24F0(const Coord3D *pos, ObjectTypes *types, Player *player, bool flag);
	void rva003C33C9(Parameter *typeParm, Parameter *playerParm, Parameter *teamParm, Parameter *nameParm,
		bool flag);
	void rva003C2662(const AsciiString &teamName, const AsciiString &objectType);
	void rva003C276A(const AsciiString &teamName, const AsciiString &objectType, Parameter *playerParm);
	void rva003C4625(const AsciiString &objectType, Parameter *teamParm, const AsciiString &unitName);
	void bfmeAddBH(const AsciiString &playerName, const AsciiString &name, BfmeTargetBH *target);	// 0x003C420A
	void rva003C56D6(void *what, const AsciiString &name, const AsciiString &objectType,
		const AsciiString &teamName);
	void rva003C55A6(void *what, const AsciiString &name, const AsciiString &objectType,
		const AsciiString &teamName, const AsciiString &playerName);
};

void ScriptActions::rva003C2662(const AsciiString &teamName, const AsciiString &objectType)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (!team)
		return;
	Coord3D pos;
	team->rva0039E5B9(&pos);
	Object *obj;
	ObjectTypes *types = TheScriptEngine->getObjectTypes(objectType);
	if (types) {
		obj = rva003C24F0(&pos, types, 0, false);
	} else {
		const ThingTemplate *thingTemplate = TheThingFactory->findTemplate(objectType);
		if (!thingTemplate)
			return;
		obj = ThePartitionManager->getClosestObject(&pos, REALLY_FAR, 0, &Rva00261750Filter(thingTemplate, true));
	}
	if (!obj)
		return;
	AIGroup *group = TheAI->createGroup();
	if (!group)
		return;
	team->getTeamAsAIGroup(group);
	{
		Rva00372571Params params;
		params.m_14 = -1;
		params.m_pos = obj->getPosition();
		params.m_04 = false;
		params.m_08 = 0;
		params.m_0C = 0;
		params.m_10 = 0;
		params.m_18 = 0;
		params.m_1C = false;
		group->groupMoveToPosition(&params, 1);
	}
}

void ScriptActions::rva003C4625(const AsciiString &objectType, Parameter *teamParm, const AsciiString &unitName)
{
	Team *team = TheScriptEngine->getTeamNamed(teamParm->getString(), false);
	if (!team)
		return;
	Coord3D pos;
	team->rva0039E5B9(&pos);
	Object *obj;
	ObjectTypes *types = TheScriptEngine->getObjectTypes(objectType);
	if (types) {
		obj = rva003C24F0(&pos, types, team->getControllingPlayer(), false);
	} else {
		const ThingTemplate *thingTemplate = TheThingFactory->findTemplate(objectType);
		if (!thingTemplate)
			return;
		obj = ThePartitionManager->getClosestObject(&pos, REALLY_FAR, 0,
			Rva00261750Filter(thingTemplate, true).link(&Rva0026137EFilter(team->getControllingPlayer(), true)));
	}
	if (obj) {
		TheScriptEngine->rva00208968(unitName, obj);
		TheScriptEngine->addObjectToCache(obj, unitName);
	}
}

void ScriptActions::rva003C55A6(void *what, const AsciiString &name, const AsciiString &objectType,
	const AsciiString &teamName, const AsciiString &playerName)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (!team)
		return;
	Coord3D pos;
	team->rva0039E5B9(&pos);
	int mask = TheScriptEngine->rva00357475(playerName, 0);
	if (!mask)
		return;
	do {
		Player *player = ThePlayerList->getEachPlayerFromMask(mask);
		Object *obj;
		ObjectTypes *types = TheScriptEngine->getObjectTypes(objectType);
		if (types) {
			obj = rva003C24F0(&pos, types, player, false);
		} else {
			const ThingTemplate *thingTemplate = TheThingFactory->findTemplate(objectType);
			if (!thingTemplate)
				continue;
			obj = ThePartitionManager->getClosestObject(&pos, REALLY_FAR, 0,
				Rva00261750Filter(thingTemplate, true).link(&Rva0026137EFilter(player, true)));
		}
		if (obj) {
			bfmeAddBH(*(const AsciiString *)what, (const AsciiString &)name, (BfmeTargetBH *)obj);
			return;
		}
	} while (mask);
}

void ScriptActions::rva003C56D6(void *what, const AsciiString &name, const AsciiString &objectType,
	const AsciiString &teamName)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (!team)
		return;
	Coord3D pos;
	team->rva0039E5B9(&pos);
	Object *obj;
	ObjectTypes *types = TheScriptEngine->getObjectTypes(objectType);
	if (types) {
		obj = rva003C24F0(&pos, types, 0, false);
	} else {
		const ThingTemplate *thingTemplate = TheThingFactory->findTemplate(objectType);
		if (!thingTemplate)
			return;
		obj = ThePartitionManager->getClosestObject(&pos, REALLY_FAR, 0, &Rva00261750Filter(thingTemplate, true));
	}
	if (obj)
		bfmeAddBH(*(const AsciiString *)what, (const AsciiString &)name, (BfmeTargetBH *)obj);
}

void ScriptActions::rva003C33C9(Parameter *typeParm, Parameter *playerParm, Parameter *teamParm,
	Parameter *nameParm, bool flag)
{
	Player *player = ThePlayerList->getPlayerFromMask(TheScriptEngine->rva00357475(playerParm->getString(), 0));
	if (!player)
		return;
	Team *team = TheScriptEngine->getTeamNamed(teamParm->getString(), false);
	if (!team)
		return;
	Coord3D pos;
	team->rva0039DA2A(&pos);
	Object *obj;
	ObjectTypes *types = TheScriptEngine->getObjectTypes(typeParm->getString());
	if (types) {
		if (flag)
			obj = rva003C24F0(&pos, types, player, true);
		else
			obj = rva003C24F0(&pos, types, player, false);
	} else {
		const ThingTemplate *thingTemplate = TheThingFactory->findTemplate(typeParm->getString());
		if (!thingTemplate)
			return;
		Rva00261750Filter thingFilter(thingTemplate, true);
		Rva0026137EFilter playerFilter(player, true);
		Rva0026149CFilter extraFilter(false);
		thingFilter.link(&playerFilter);
		if (flag)
			thingFilter.link(&extraFilter);
		obj = ThePartitionManager->getClosestObject(&pos, REALLY_FAR, 0, &thingFilter);
	}
	if (obj) {
		TheScriptEngine->rva00208968(nameParm->getString(), obj);
		TheScriptEngine->addObjectToCache(obj, nameParm->getString());
	}
}

void ScriptActions::rva003C276A(const AsciiString &teamName, const AsciiString &objectType, Parameter *playerParm)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (!team)
		return;
	Coord3D pos;
	team->rva0039E5B9(&pos);
	ObjectTypes *types = TheScriptEngine->getObjectTypes(objectType);
	const ThingTemplate *thingTemplate = 0;
	if (!types) {
		thingTemplate = TheThingFactory->findTemplate(objectType);
		if (!thingTemplate)
			return;
	}
	Object *best = 0;
	float bestDist = 99999.0f;
	int mask = TheScriptEngine->rva00357B82(playerParm);
	if (!mask)
		return;
	do {
		Player *player = ThePlayerList->getEachPlayerFromMask(mask);
		Object *obj;
		if (types)
			obj = rva003C24F0(&pos, types, player, false);
		else
			obj = ThePartitionManager->getClosestObject(&pos, REALLY_FAR, 0,
				Rva00261750Filter(thingTemplate, true).link(&Rva0026137EFilter(player, true)));
		if (obj) {
			Coord3D delta;
			delta.x = obj->getPosition()->x;
			delta.y = obj->getPosition()->y;
			delta.z = obj->getPosition()->z;
			delta.x -= pos.x;
			delta.y -= pos.y;
			delta.z -= pos.z;
			float dist = delta.length();
			if (!best || bestDist > dist) {
				best = obj;
				bestDist = dist;
			}
		}
	} while (mask);
	if (!best)
		return;
	AIGroup *group = TheAI->createGroup();
	if (!group)
		return;
	team->getTeamAsAIGroup(group);
	{
		Rva00372571Params params;
		params.m_14 = -1;
		params.m_pos = best->getPosition();
		params.m_04 = false;
		params.m_08 = 0;
		params.m_0C = 0;
		params.m_10 = 0;
		params.m_18 = 0;
		params.m_1C = false;
		group->groupMoveToPosition(&params, 1);
	}
}
