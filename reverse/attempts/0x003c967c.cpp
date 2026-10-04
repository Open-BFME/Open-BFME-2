// ?doMoveTeamTowardsNearest@ScriptActions@@IAEXABVAsciiString@@0V2@@Z
// partial score=0.9 date=2026-10-04
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /GX /arch:SSE
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

// vftable 0x00BF91BC, allow 0x002611BF.
class Rva002611BFFilter : public Rva000421C8
{
public:
	Rva002611BFFilter(const Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
};

// The base filter's slot 2 is the trivial virtual retail shares across many
// vftable slots (0x0036CC7A); bind the declaration to that row.
#pragma comment(linker, "/alternatename:?getPlayerMask@Rva000421C8@@UAEHXZ=?Get_File_Handle@FileClass@@UAEPAXXZ")

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
	const ThingTemplate *m_template;
	bool m_match;
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

enum CommandSourceType
{
	CMD_FROM_SCRIPT = 1
};

enum DistanceCalculationType
{
	FROM_CENTER_3D = 0
};

class AICommandInterface
{
public:
	void aiMoveToObject(Object *obj, CommandSourceType source);	// 0x00352ECA
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
	AIUpdateInterface *getAIUpdateInterface() { return m_ai; }
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

template<class OBJ> class DLINK_ITERATOR
{
public:
	void advance();						// 0x00263526
	bool done() const { return m_cur == 0; }
	OBJ *cur() const { return m_cur; }
private:
	OBJ *m_cur;
	char m_pad[20];
};

class Team
{
public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;	// 0x00263864
};

class ScriptEngine
{
public:
	Team *getTeamNamed(AsciiString name, bool exact);			// 0x003584E9
	PolygonTrigger *getQualifiedTriggerAreaByName(AsciiString name);	// 0x0035768D
};
extern ScriptEngine *TheScriptEngine;

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *pos, float maxDist, int dc,
		Rva000421C8 *filters);	// 0x00625360
};
extern PartitionManager *ThePartitionManager;

#define REALLY_FAR (100000 * 10.0f)

class ScriptActions
{
protected:
	void doMoveTeamTowardsNearest(const AsciiString &teamName, const AsciiString &objectType,
		AsciiString triggerName);
};

void ScriptActions::doMoveTeamTowardsNearest(const AsciiString &teamName, const AsciiString &objectType,
	AsciiString triggerName)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (!team)
		return;

	const ThingTemplate *templ = TheThingFactory->findTemplate(objectType);
	if (!templ)
		return;

	PolygonTrigger *trig = TheScriptEngine->getQualifiedTriggerAreaByName(triggerName);
	if (!trig)
		return;

	for (DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList(); !iter.done(); iter.advance()) {
		Object *obj = iter.cur();
		AIUpdateInterface *ai = obj->getAIUpdateInterface();
		if (!ai)
			continue;
		Object *bestObj = ThePartitionManager->getClosestObject(obj->getPosition(), REALLY_FAR, FROM_CENTER_3D,
			Rva00261750Filter(templ, true).link(Rva00261723Filter(trig).link(&Rva002611BFFilter(obj))));
		if (!bestObj)
			return;
		ai->m_commands.aiMoveToObject(bestObj, CMD_FROM_SCRIPT);
	}
}

