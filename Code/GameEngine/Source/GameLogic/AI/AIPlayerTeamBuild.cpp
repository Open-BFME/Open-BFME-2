// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX
//
// AIPlayer's factory search and team-build feasibility, Zero Hour's
// AIPlayer.cpp bodies (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference) with BFME 2's additions read off
// retail:
//  - findFactory 0x004F09CF (371 bytes): ZH's walk of TheGameLogic's object
//    list for this player's idle, built, unsold, enabled factories with a
//    production interface (Object::rva0028BC58(0)). BFME 2 checks a private
//    status bit (+0x438 & 1), asks the player's build table at +0x738 for a
//    build index (0x0037EE4C) and passes it to TheBuildAssistant's
//    isPossibleToMakeUnit (slot +0x64); with the player flag at +0x735 a busy
//    factory whose first queued entry (type 1 or 3) is a different template
//    flagged at +0x633 also counts as available.
//  - isPossibleToBuildTeam 0x004F0B42 (323 bytes): ZH's cost sum over the
//    prototype's unit infos (+0x130, count +0x1D8), with BFME 2's early
//    success when 0x002A8AB1 finds a record for the player, cost from the
//    build index (0x0037E649) or the template (0x0033A69A), and free units
//    (template +0x11B & 0x20).
//  - findDozer 0x004F0C85 (345 bytes, vtable slot +0x50): ZH's closest idle
//    dozer search; queueDozer is slot +0x54 and the repair dozer is +0x50.
//  - rva004F13D8 0x004F13D8 (398 bytes): BFME 2's check that the minimum
//    unit counts can be met from units already on the field (default team,
//    prototype flag +0x210 or team flags +0x110/+0x111) and the player's
//    money; its only callers are isAGoodIdeaToBuildTeam's paths.
//  - isAGoodIdeaToBuildTeam 0x004F1566 (237 bytes): ZH's production
//    condition (TeamPrototype 0x003A0E6E), instance limit (+0x218 against
//    countTeamInstances 0x0039D954) and build-queue duplicate checks, then
//    BFME 2's on-field shortcut (rva004F13D8) before isPossibleToBuildTeam and
//    ZH's two debug-AI messages (GlobalData +0x9B8). The queue walk calls
//    dlink_next_TeamBuildQueue, which retail folded into the shared
//    mov eax,[ecx+8] getter at 0x0030F45F.
// GameLogic comes from the canonical GameLogicObjectLookupView.h.
#include "ascii_string.h"
typedef bool Bool;
typedef int Int;
typedef float Real;
#define NULL 0

#include "../../../../Libraries/Include/Lib/Coord3D.h"
class ThingTemplate;
class Player;
class Team;

#include "../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

enum ObjectStatusTypes
{
	OBJECT_STATUS_UNDER_CONSTRUCTION = 2,
	OBJECT_STATUS_SOLD = 0x13
};

template <int N>
class BitFlags
{
public:
	Bool any() const;
	Bool test(Int bit) const { return (m_bits[0] & (1 << bit)) != 0; }
	unsigned int m_bits[1];
};

class ThingTemplate
{
public:
	Bool isEquivalentTo(const ThingTemplate *other) const;
	Int rva0033A69A(const Player *player, Int a, Int b) const;
	unsigned char m_pad000[0x109];
	unsigned char m_kindOf109;			// +0x109, bit 0x40 = KINDOF_DOZER
	unsigned char m_pad10A[0x10F - 0x10A];
	unsigned char m_kindOf10F;			// +0x10F, bit 0x80 = factory
	unsigned char m_pad110[0x11B - 0x110];
	unsigned char m_bfme11B;			// +0x11B, bit 0x20 = free to build
	unsigned char m_pad11C[0x633 - 0x11C];
	unsigned char m_bfme633;			// +0x633
};

class Object;
class Rva0037EE4C
{
public:
	Int rva0037EE4C(const ThingTemplate *thing, Int a, Int b);
};
class Rva0037E6E8
{
public:
	Int rva0037E649(Int index, Object *obj);
};

class Player
{
public:
	unsigned char m_pad000[0x94];
	unsigned int m_money;				// +0x94
	unsigned char m_pad098[0x2EC - 0x98];
	Team *m_defaultTeam;			// +0x2EC
	unsigned char m_pad2F0[0x735 - 0x2F0];
	Bool m_bfme735;					// +0x735
	unsigned char m_pad736[0x738 - 0x736];
	union
	{
		Rva0037EE4C m_738;			// +0x738
		Rva0037E6E8 m_738b;
	};
};

class DozerAIInterface
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual Bool isTaskPending(int task);		// +0x18
	virtual void slot1c();
	virtual Bool isAnyTaskPending();		// +0x20
};

class SupplyTruckAIInterface
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual Bool isCurrentlyFerryingSupplies();	// +0x14
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2c();
	virtual Bool isForcedIntoWantingState();	// +0x30
};

class AIUpdateInterface
{
public:
	virtual void slot000();
	virtual void slot004();
	virtual void slot008();
	virtual void slot00c();
	virtual void slot010();
	virtual void slot014();
	virtual void slot018();
	virtual void slot01c();
	virtual void slot020();
	virtual void slot024();
	virtual void slot028();
	virtual void slot02c();
	virtual void slot030();
	virtual void slot034();
	virtual void slot038();
	virtual void slot03c();
	virtual void slot040();
	virtual void slot044();
	virtual void slot048();
	virtual void slot04c();
	virtual void slot050();
	virtual void slot054();
	virtual void slot058();
	virtual void slot05c();
	virtual void slot060();
	virtual void slot064();
	virtual void slot068();
	virtual void slot06c();
	virtual void slot070();
	virtual void slot074();
	virtual void slot078();
	virtual void slot07c();
	virtual void slot080();
	virtual void slot084();
	virtual void slot088();
	virtual void slot08c();
	virtual void slot090();
	virtual void slot094();
	virtual void slot098();
	virtual void slot09c();
	virtual void slot0a0();
	virtual void slot0a4();
	virtual void slot0a8();
	virtual void slot0ac();
	virtual void slot0b0();
	virtual void slot0b4();
	virtual void slot0b8();
	virtual void slot0bc();
	virtual void slot0c0();
	virtual void slot0c4();
	virtual void slot0c8();
	virtual void slot0cc();
	virtual void slot0d0();
	virtual void slot0d4();
	virtual void slot0d8();
	virtual void slot0dc();
	virtual void slot0e0();
	virtual void slot0e4();
	virtual void slot0e8();
	virtual void slot0ec();
	virtual void slot0f0();
	virtual void slot0f4();
	virtual void slot0f8();
	virtual void slot0fc();
	virtual void slot100();
	virtual void slot104();
	virtual void slot108();
	virtual void slot10c();
	virtual void slot110();
	virtual void slot114();
	virtual void slot118();
	virtual void slot11c();
	virtual void slot120();
	virtual void slot124();
	virtual void slot128();
	virtual void slot12c();
	virtual void slot130();
	virtual void slot134();
	virtual void slot138();
	virtual void slot13c();
	virtual void slot140();
	virtual void slot144();
	virtual void slot148();
	virtual void slot14c();
	virtual void slot150();
	virtual void slot154();
	virtual void slot158();
	virtual void slot15c();
	virtual void slot160();
	virtual void slot164();
	virtual void slot168();
	virtual void slot16c();
	virtual void slot170();
	virtual DozerAIInterface *getDozerAIInterface();		// +0x174
	virtual void slot178();
	virtual SupplyTruckAIInterface *getSupplyTruckAIInterface();	// +0x17C

	unsigned char m_pad004[0x3BE - 0x04];
	Bool m_bfme3BE;					// +0x3BE
};

class Object
{
public:
	Player *getControllingPlayer() const;
	Bool testStatus(ObjectStatusTypes bit) const;
	void *rva0028BC58(Int which);

	void *m_vtable;
	ThingTemplate *m_template;			// +0x04
	unsigned char m_pad008[0x38 - 0x08];
	Coord3D m_pos;					// +0x38
	unsigned char m_pad044[0x74 - 0x44];
	ObjectID m_id;					// +0x74
	unsigned char m_pad078[0x8C - 0x78];
	Object *m_next;					// +0x8C
	unsigned char m_pad090[0x1C8 - 0x90];
	BitFlags<11> m_disabledMask;			// +0x1C8
	unsigned char m_pad1CC[0x258 - 0x1CC];
	AIUpdateInterface *m_ai;			// +0x258
	unsigned char m_pad25C[0x304 - 0x25C];
	Team *m_team;					// +0x304
	unsigned char m_pad308[0x438 - 0x308];
	unsigned char m_privateStatus;			// +0x438
};

class BuildAssistant
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual Bool isPossibleToMakeUnit(Object *factory, const ThingTemplate *thing, Int buildIndex);	// +0x64
};
extern BuildAssistant *TheBuildAssistant;

class ProductionEntry
{
public:
	void *m_vtable;
	Int m_type;
	ThingTemplate *m_thing;
};

class ProductionUpdateInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual Int getProductionCount() const;		// +0x44
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual ProductionEntry *firstProduction() const;	// +0x54
};

class Rva002D06CA
{
public:
	void *rva002D06CA(const AsciiString *name);
};
extern Rva002D06CA *TheThingFactory;

struct Rva002A8AB1Record;
class Rva002A8F24
{
public:
	Rva002A8AB1Record *rva002A8AB1(void *player);
};
extern Rva002A8F24 *g_00DFEEF8;

struct TAiData
{
	char m_pad000[0x28];
	float m_teamResourcesToBuild;	// +0x28
};

class AI
{
public:
	char m_pad00[0x18];
	TAiData *m_aiData;		// +0x18
};
extern AI *TheAI;

struct TCreateUnitsInfo
{
	Int minUnits;			// +0x00
	Int maxUnits;			// +0x04
	Int m_08;
	Int m_0C;
	AsciiString unitThingName;	// +0x10
	Int m_14;
};

class TeamPrototype
{
public:
	Bool evaluateProductionCondition();
	Int countTeamInstances();
	const AsciiString &getName() const { return m_name; }

	char m_pad000[0x14];
	AsciiString m_name;			// +0x14
	char m_pad018[0x130 - 0x18];
	TCreateUnitsInfo m_unitsInfo[7];	// +0x130
	Int m_numUnitsInfo;			// +0x1D8
	char m_pad1DC[0x210 - 0x1DC];
	Bool m_bfme210;				// +0x210
	char m_pad211[0x218 - 0x211];
	Int m_maxInstances;			// +0x218
};

class Team
{
public:
	char m_pad000[0x30];
	TeamPrototype *m_proto;			// +0x30
	char m_pad034[0x5D - 0x34];
	Bool m_active;				// +0x5D
	char m_pad05E[0x110 - 0x5E];
	Bool m_bfme110;				// +0x110
	Bool m_bfme111;				// +0x111
};

template <class OBJCLASS> class DLINK_ITERATOR
{
public:
	typedef OBJCLASS *(OBJCLASS::*GetNextFunc)() const;
	DLINK_ITERATOR(OBJCLASS *cur, GetNextFunc getNextFunc) : m_cur(cur), m_getNextFunc(getNextFunc) {}
	void advance() { if (m_cur) m_cur = (m_cur->*m_getNextFunc)(); }
	Bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
private:
	OBJCLASS *m_cur;
	GetNextFunc m_getNextFunc;
};

class TeamInQueue
{
public:
	TeamInQueue *dlink_next_TeamBuildQueue() const { return m_next; }
	void *m_vtbl;
	TeamInQueue *m_prev;			// +0x04
	TeamInQueue *m_next;			// +0x08
	char m_pad0C[0x1C - 0x0C];
	Team *m_team;				// +0x1C
};

class GlobalData
{
public:
	char m_pad000[0x9B8];
	Int m_debugAI;				// +0x9B8
};
extern GlobalData *TheWritableGlobalData;

class ScriptEngine
{
public:
	void AppendDebugMessage(const AsciiString &message, Bool forcePause);
};
extern ScriptEngine *TheScriptEngine;

class AIPlayer
{
protected:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual Object *findDozer(const Coord3D *searchPosition);	// +0x50
	virtual void queueDozer();					// +0x54

	Object *findFactory(const ThingTemplate *thing, Bool busyOK, Int *buildIndex);
	Bool isPossibleToBuildTeam(TeamPrototype *proto, Bool requireIdleFactory, Bool &notEnoughMoney);
	Bool rva004F13D8(TeamPrototype *proto);
	Bool isAGoodIdeaToBuildTeam(TeamPrototype *proto);
	DLINK_ITERATOR<TeamInQueue> iterate_TeamBuildQueue() const
	{
		return DLINK_ITERATOR<TeamInQueue>(m_teamBuildQueue, &TeamInQueue::dlink_next_TeamBuildQueue);
	}

private:
	TeamInQueue *m_teamBuildQueue;	// +0x04
	TeamInQueue *m_teamReadyQueue;	// +0x08
	Player *m_player;		// +0x0C
	unsigned char m_pad10[0x50 - 0x10];
	ObjectID m_repairDozer;		// +0x50
};

enum { DOZER_TASK_BUILD = 0 };

Object *AIPlayer::findFactory(const ThingTemplate *thing, Bool busyOK, Int *buildIndex)
{
	Object *busyFactory = NULL;
	if (thing == NULL)
		return NULL;
	if (buildIndex != NULL)
		*buildIndex = -1;

	for (Object *factory = TheGameLogic->getFirstObject(); factory != NULL; factory = factory->m_next)
	{
		if (factory->getControllingPlayer() != m_player)
			continue;
		if ((factory->m_template->m_kindOf10F & 0x80) == 0)
			continue;
		if (factory->testStatus(OBJECT_STATUS_UNDER_CONSTRUCTION))
			continue;
		if (factory->testStatus(OBJECT_STATUS_SOLD))
			continue;
		if (factory->m_disabledMask.any())
			continue;
		ProductionUpdateInterface *production = (ProductionUpdateInterface *)factory->rva0028BC58(0);
		if (production == NULL)
			continue;
		if (factory->m_privateStatus & 1)
			continue;

		Player *owner = factory->getControllingPlayer();
		Int index = owner->m_738.rva0037EE4C(thing, -1, 0);
		if (index != -1)
		{
			if (!TheBuildAssistant->isPossibleToMakeUnit(factory, NULL, index))
				continue;
			if (buildIndex != NULL)
				*buildIndex = index;
		}
		else if (!TheBuildAssistant->isPossibleToMakeUnit(factory, thing, -1))
			continue;

		if (production->getProductionCount() <= 0)
			return factory;
		if (m_player->m_bfme735)
		{
			ProductionEntry *entry = production->firstProduction();
			if (entry != NULL)
			{
				switch (entry->m_type)
				{
				case 1:
				case 3:
					ThingTemplate *entryThing = entry->m_thing;
					if (entryThing != NULL && entryThing->m_bfme633 && !thing->isEquivalentTo(entryThing))
						return factory;
				}
			}
		}
		if (busyOK)
			busyFactory = factory;
	}
	return busyOK ? busyFactory : NULL;
}

Bool AIPlayer::isPossibleToBuildTeam(TeamPrototype *proto, Bool requireIdleFactory, Bool &notEnoughMoney)
{
	if (g_00DFEEF8->rva002A8AB1(m_player) != NULL)
		return true;

	notEnoughMoney = false;
	Bool anyIdle = false;
	Int cost = 0;
	for (Int i = 0; i < proto->m_numUnitsInfo; ++i)
	{
		const ThingTemplate *thing = (const ThingTemplate *)TheThingFactory->rva002D06CA(&proto->m_unitsInfo[i].unitThingName);
		if (thing == NULL)
			continue;
		if (findFactory(thing, true, NULL) == NULL)
			return false;
		Int buildIndex;
		if (findFactory(thing, false, &buildIndex) != NULL)
			anyIdle = true;
		Int thingCost;
		if (buildIndex == -1)
			thingCost = thing->rva0033A69A(m_player, 0, -1);
		else
			thingCost = m_player->m_738b.rva0037E649(buildIndex, NULL);
		if (thing->m_bfme11B & 0x20)
			thingCost = 0;
		cost = (Int)(cost + thingCost * ((float)(proto->m_unitsInfo[i].maxUnits + proto->m_unitsInfo[i].minUnits) * 0.5f));
	}
	cost = (Int)((float)cost * TheAI->m_aiData->m_teamResourcesToBuild);
	if (m_player->m_money < (unsigned int)cost)
	{
		notEnoughMoney = true;
		return false;
	}
	if (anyIdle)
		return true;
	if (!requireIdleFactory)
		return true;
	return false;
}

Object *AIPlayer::findDozer(const Coord3D *searchPosition)
{
	Object *candidateObject;
	Object *fallbackDozer = NULL;
	Bool shouldQueueDozer = true;
	Object *closestIdleDozer = NULL;
	Real closestIdleDistanceSquared = 0;

	for (candidateObject = TheGameLogic->getFirstObject(); candidateObject;
		candidateObject = candidateObject->m_next)
	{
		Player *candidateOwner = candidateObject->getControllingPlayer();
		if (candidateOwner == m_player)
		{
			const ThingTemplate *candidateTemplate = candidateObject->m_template;
			if ((candidateTemplate->m_kindOf109 & 0x40) != 0)
			{
				AIUpdateInterface *candidateAI = candidateObject->m_ai;
				if (candidateAI == NULL)
					continue;

				DozerAIInterface *dozerInterface = candidateAI->getDozerAIInterface();
				if (dozerInterface)
				{
					SupplyTruckAIInterface *supplyTruckInterface =
						candidateAI->getSupplyTruckAIInterface();
					if (!dozerInterface->isAnyTaskPending() && supplyTruckInterface)
					{
						if (supplyTruckInterface->isCurrentlyFerryingSupplies()
							|| supplyTruckInterface->isForcedIntoWantingState())
							continue;
					}
					if (candidateObject->m_id == m_repairDozer)
						continue;
					shouldQueueDozer = false;
					if (dozerInterface->isTaskPending(DOZER_TASK_BUILD))
						continue;
					if (!dozerInterface->isAnyTaskPending())
						fallbackDozer = candidateObject;
					if (fallbackDozer == NULL)
						fallbackDozer = candidateObject;
					if (fallbackDozer && !dozerInterface->isAnyTaskPending())
					{
						Real dozerDistanceSquared;
						Real deltaX = searchPosition->x - fallbackDozer->m_pos.x;
						Real deltaY = searchPosition->y - fallbackDozer->m_pos.y;
						dozerDistanceSquared = deltaX * deltaX + deltaY * deltaY;
						if (closestIdleDozer == NULL)
						{
							closestIdleDozer = fallbackDozer;
							closestIdleDistanceSquared = dozerDistanceSquared;
						}
						else if (dozerDistanceSquared < closestIdleDistanceSquared)
						{
							closestIdleDozer = fallbackDozer;
							closestIdleDistanceSquared = dozerDistanceSquared;
						}
					}
				}
			}
		}
	}
	if (shouldQueueDozer)
		queueDozer();
	if (closestIdleDozer)
		return closestIdleDozer;
	return fallbackDozer;
}

Bool AIPlayer::rva004F13D8(TeamPrototype *proto)
{
	const TCreateUnitsInfo *unitInfo = &proto->m_unitsInfo[0];
	Bool result = true;
	float totalCost = 0.0f;
	for (Int i = 0; i < proto->m_numUnitsInfo; ++i)
	{
		const ThingTemplate *thing = (const ThingTemplate *)TheThingFactory->rva002D06CA(&unitInfo[i].unitThingName);
		if (unitInfo[i].maxUnits <= 0)
			continue;

		Int count = 0;
		for (Object *object = TheGameLogic->getFirstObject(); object; object = object->m_next)
		{
			if (!object->m_template->isEquivalentTo(thing))
				continue;
			if (object->getControllingPlayer() != m_player)
				continue;

			Team *team = object->m_team;
			Bool eligible = false;
			if (team == m_player->m_defaultTeam)
				eligible = true;
			if (!team->m_active)
				continue;
			if (team->m_proto->m_bfme210)
				eligible = true;
			if (team->m_bfme110)
				eligible = team->m_bfme111;
			if (!eligible)
				continue;
			if (object->m_ai && !object->m_ai->m_bfme3BE)
				continue;
			if (object->m_disabledMask.m_bits[0] & 8)
				continue;
			++count;
		}

		if (count >= unitInfo[i].minUnits)
			continue;
		Int buildIndex;
		if (!findFactory(thing, false, &buildIndex))
		{
			result = false;
			break;
		}
		Int thingCost;
		if (buildIndex == -1)
			thingCost = thing->rva0033A69A(m_player, 0, -1);
		else
			thingCost = m_player->m_738b.rva0037E649(buildIndex, NULL);
		totalCost += (float)((unitInfo[i].minUnits - count) * thingCost);
		if ((float)m_player->m_money < totalCost)
		{
			result = false;
			break;
		}
	}
	return result;
}

Bool AIPlayer::isAGoodIdeaToBuildTeam(TeamPrototype *proto)
{
	if (!proto->evaluateProductionCondition())
		return false;

	if (proto->countTeamInstances() >= proto->m_maxInstances)
		return false;

	for (DLINK_ITERATOR<TeamInQueue> iter = iterate_TeamBuildQueue(); !iter.done(); iter.advance())
	{
		TeamInQueue *team = iter.cur();
		if (team->m_team->m_proto == proto)
			return false;
	}

	if (rva004F13D8(proto))
		return true;

	Bool needMoney;
	if (!isPossibleToBuildTeam(proto, true, needMoney))
	{
		if (TheWritableGlobalData->m_debugAI)
		{
			AsciiString str;
			if (needMoney)
				str.format("Team %s not chosen - Not enough money.", proto->getName().str());
			else
				str.format("Team %s not chosen - Factory/tech missing or busy.", proto->getName().str());
			TheScriptEngine->AppendDebugMessage(str, false);
		}
		return false;
	}
	return true;
}
