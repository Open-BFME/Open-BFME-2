// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX
//
// ScriptActions::rva003C951B, retail 0x003C951B, 353 bytes (called from the
// action dispatcher 0x003CA4BE at 0x003CD2BF). A BFME2 script action: the
// named unit's AI gets AICMD 0x49 (AICommandInterface::rva003C7653, from a
// script) at the object of the given template closest to it, anywhere
// (REALLY_FAR), restricted to the named player mask unless the player name
// is empty; an unknown player only logs the Zero Hour warning.
//
// The filters are BFME2's partition filter chain (the view
// AIStructureCreepTactic.cpp documents): a vptr, the +0x04 link to the next
// filter (PartitionFilter::link 0x00625790), then each filter's members;
// address-derived names after allow (slot 1), the ctors being inline.
#include "ascii_string.h"

class Object;
class Player;

#include "../../../Include/GameLogic/PartitionFilter.h"

class ThingTemplate;

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

// vftable 0x00C1FDE0, allow 0x002613AF, slot 2 0x002613A3: +0x08 a player
// mask, +0x0C whether a match allows.
class Rva002613AFFilter : public Rva000421C8
{
public:
	Rva002613AFFilter(int playerMask, bool match) : m_playerMask(playerMask), m_match(match) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	int m_playerMask;
	bool m_match;
};

#include "../../../../Libraries/Include/Lib/Coord3D.h"

#define REALLY_FAR (100000 * 10.0f)

enum DistanceCalculationType
{
	FROM_CENTER_3D = 0
};

#include "../../Common/PartitionRangeQueryCallView.h"
extern PartitionManager *ThePartitionManager;

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1
};

#include "../../../Include/GameLogic/Module/AIUpdate.h"

#include "../Object/object.h"

#include "../../../Include/Common/ThingFactory.h"
extern ThingFactory *TheThingFactory;

#include "../../../Include/GameLogic/ScriptEngine.h"
extern ScriptEngine *TheScriptEngine;

class ScriptActions
{
public:
	void rva003C951B(const AsciiString &unitName, const AsciiString &thingName,
		const AsciiString &playerName);
};

void ScriptActions::rva003C951B(const AsciiString &unitName, const AsciiString &thingName,
	const AsciiString &playerName)
{
	Object *obj = TheScriptEngine->getUnitNamed(unitName);
	if (!obj)
		return;
	AIUpdateInterface *ai = obj->getAIUpdateInterface();
	if (!ai)
		return;
	const ThingTemplate *thingTemplate = TheThingFactory->findTemplate(thingName);
	if (!thingTemplate)
		return;
	Object *target = 0;
	if (playerName.compare(AsciiString::TheEmptyString) == 0) {
		Rva00261750Filter thingFilter(thingTemplate, true);
		target = ThePartitionManager->getClosestObject(obj->getPosition(), REALLY_FAR, FROM_CENTER_3D,
			&thingFilter);
	} else {
		int mask = TheScriptEngine->rva00357475(playerName, 0);
		if (mask) {
			Rva002613AFFilter playerFilter(mask, true);
			Rva00261750Filter thingFilter(thingTemplate, true);
			target = ThePartitionManager->getClosestObject(obj->getPosition(), REALLY_FAR, FROM_CENTER_3D,
				thingFilter.link(&playerFilter));
		} else {
			AsciiString msg("WARNING - Player (");
			((StringBase<char> *)&msg)->concat(*(const StringBase<char> *)&playerName);
			((StringBase<char> *)&msg)->concat(") not found during execution of script.");
			TheScriptEngine->AppendDebugMessage(msg, false);
		}
	}
	if (target)
		ai->rva003C7653(target, CMD_FROM_SCRIPT);
}
