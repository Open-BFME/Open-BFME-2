// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX
//
// ScriptActions::doMoveUnitTowardsNearest, retail 0x003C9404, 279 bytes
// (called from the action dispatcher 0x003CA4BE at 0x003CD298). Zero Hour's
// body without its object-type-list fallback, over BFME2's partition filter
// chain: the named unit (with an AI) moves towards the closest object of the
// named template inside the named trigger area that shares its map status.
// BFME2 resolves the template before the trigger, links the three filters
// (built in reverse) and measures from the 3D centre.
//
// The filters are BFME2's partition filter chain (the view
// AIStructureCreepTactic.cpp documents): a vptr, the +0x04 link to the next
// filter (PartitionFilter::link 0x00625790), then each filter's members;
// address-derived names after allow (slot 1), the ctors being inline.
#include "ascii_string.h"

class Object;
class Player;

#include "../../../Include/GameLogic/PartitionFilter.h"

// vftable 0x00BF91BC, allow 0x002611BF.
class Rva002611BFFilter : public Rva000421C8
{
public:
	Rva002611BFFilter(const Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
};

class ThingTemplate;
class PolygonTrigger;

// vftable 0x00C07184, allow 0x00261723: +0x08 a polygon trigger (Zero
// Hour's PartitionFilterPolygonTrigger in this caller).
class Rva00261723Filter : public Rva000421C8
{
public:
	Rva00261723Filter(PolygonTrigger *trigger) : m_trigger(trigger) {}
	virtual bool allow(Object *obj);
	PolygonTrigger *m_trigger;
};

// vftable 0x00C1FDEC, allow 0x00261750: +0x08 a thing template, +0x0C
// whether a match allows (Zero Hour's PartitionFilterThing in this caller).
class Rva00261750Filter : public Rva000421C8
{
public:
	Rva00261750Filter(const ThingTemplate *tmpl, bool match) : m_template(tmpl), m_match(match) {}
	virtual bool allow(Object *obj);
	const ThingTemplate *m_template; // +0x08
	bool m_match; // +0x0C
	char m_pad0D[0x3];
};

#include "../../../../Libraries/Include/Lib/Coord3D.h"

enum CommandSourceType
{
	CMD_FROM_SCRIPT = 1
};

enum DistanceCalculationType
{
	FROM_CENTER_3D = 0
};

#include "../../../Include/GameLogic/Module/AIUpdate.h"

#include "../Object/object.h"

#include "../../../Include/Common/ThingFactory.h"
extern ThingFactory *TheThingFactory;

#include "../../../Include/GameLogic/ScriptEngine.h"
extern ScriptEngine *TheScriptEngine;

#include "../../Common/PartitionRangeQueryCallView.h"
extern PartitionManager *ThePartitionManager;

#define REALLY_FAR (100000 * 10.0f)

class ScriptActions
{
protected:
	void doMoveUnitTowardsNearest(const AsciiString &unitName, const AsciiString &objectType,
		AsciiString triggerName);
};

void ScriptActions::doMoveUnitTowardsNearest(const AsciiString &unitName, const AsciiString &objectType,
	AsciiString triggerName)
{
	Object *obj = TheScriptEngine->getUnitNamed(unitName);
	if (!obj)
		return;

	AIUpdateInterface *ai = obj->getAIUpdateInterface();
	if (!ai)
		return;

	const ThingTemplate *thingTemplate = TheThingFactory->findTemplate(objectType);
	if (!thingTemplate)
		return;

	PolygonTrigger *trig = TheScriptEngine->getQualifiedTriggerAreaByName(triggerName);
	if (!trig)
		return;

	Object *bestObj = ThePartitionManager->getClosestObject(obj->getPosition(), REALLY_FAR, FROM_CENTER_3D,
		Rva00261750Filter(thingTemplate, true).link(Rva00261723Filter(trig).link(&Rva002611BFFilter(obj))));
	if (!bestObj)
		return;

	ai->aiMoveToObject(bestObj, CMD_FROM_SCRIPT);
}
