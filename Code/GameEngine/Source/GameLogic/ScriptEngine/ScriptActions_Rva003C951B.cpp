// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /GX /arch:SSE
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

class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *link(Rva000421C8 *next);	// 0x00625790
	Rva000421C8 *m_next;
};

// The base filter's slot 2 is the trivial virtual retail shares across many
// vftable slots (0x0036CC7A); bind the declaration to that row.
#pragma comment(linker, "/alternatename:?getPlayerMask@Rva000421C8@@UAEHXZ=?Get_File_Handle@FileClass@@UAEPAXXZ")

class ThingTemplate;

// vftable 0x00C1FDEC, allow 0x00261750: +0x08 a thing template, +0x0C
// whether a match allows (Zero Hour's PartitionFilterThing).
class Rva00261750Filter : public Rva000421C8
{
public:
	Rva00261750Filter(const ThingTemplate *tmpl, bool match) : m_template(tmpl), m_match(match) {}
	virtual bool allow(Object *obj);
	const ThingTemplate *m_template;
	bool m_match;
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

struct Coord3D
{
	float x;
	float y;
	float z;
};

#define REALLY_FAR (100000 * 10.0f)

enum DistanceCalculationType
{
	FROM_CENTER_3D = 0
};

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *pos, float maxDist, int dc,
		Rva000421C8 *filters);	// 0x00625360
};
extern PartitionManager *ThePartitionManager;

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1
};

class AICommandInterface
{
public:
	void rva003C7653(Object *target, CommandSourceType cmdSource);	// 0x003C7653
};

class AIUpdateInterface
{
public:
	char m_pad00[0x20];
	AICommandInterface m_commands;	// +0x20
};

class Object
{
public:
	AIUpdateInterface *getAIUpdateInterface() const { return m_ai; }
	const Coord3D *getPosition() const { return &m_pos; }
	char m_pad000[0x38];
	Coord3D m_pos;			// +0x38
	char m_pad044[0x258 - 0x44];
	AIUpdateInterface *m_ai;	// +0x258
};

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);	// 0x002D06CA
};
extern ThingFactory *TheThingFactory;

class ScriptEngine
{
public:
	Object *getUnitNamed(const AsciiString &name);			// 0x003588E7
	int rva00357475(const AsciiString &name, bool *found);		// 0x00357475
	void AppendDebugMessage(const AsciiString &strToAdd, bool mustAdd);	// 0x00205263
};
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
	const ThingTemplate *tmpl = TheThingFactory->findTemplate(thingName);
	if (!tmpl)
		return;
	Object *target = 0;
	if (playerName.compare(AsciiString::TheEmptyString) == 0) {
		Rva00261750Filter thingFilter(tmpl, true);
		target = ThePartitionManager->getClosestObject(obj->getPosition(), REALLY_FAR, FROM_CENTER_3D,
			&thingFilter);
	} else {
		int mask = TheScriptEngine->rva00357475(playerName, 0);
		if (mask) {
			Rva002613AFFilter playerFilter(mask, true);
			Rva00261750Filter thingFilter(tmpl, true);
			target = ThePartitionManager->getClosestObject(obj->getPosition(), REALLY_FAR, FROM_CENTER_3D,
				thingFilter.link(&playerFilter));
		} else {
			AsciiString msg("WARNING - Player (");
			msg.concat(playerName);
			msg.concat(") not found during execution of script.");
			TheScriptEngine->AppendDebugMessage(msg, false);
		}
	}
	if (target)
		ai->m_commands.rva003C7653(target, CMD_FROM_SCRIPT);
}
