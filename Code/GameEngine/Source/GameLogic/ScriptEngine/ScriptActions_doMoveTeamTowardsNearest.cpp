// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /GX
//
// ScriptActions::doMoveTeamTowardsNearest, retail 0x003C967C (342B; ret 0xC)
// Target identity: the action dispatcher 0x003CA4BE calls it at 0x003CD301;
// BFME 1's ScriptActions_doMoveTeamTowardsNearest.cpp and Zero Hour's
// ScriptActions::doMoveTeamTowardsNearest are the donors for the name and
// flow. Target body: the team by name (getTeamNamed 0x003584E9), the
// template (findTemplate 0x002D06CA) and the trigger area
// (getQualifiedTriggerAreaByName 0x0035768D) are resolved first, then every
// member (iterate_TeamMemberList 0x00263864, advance 0x00263526) with an AI
// (+0x258) moves (aiMoveToObject 0x00352ECA, from script) to the closest
// object (getClosestObject 0x00625360, 3D centre) passing the same three
// filters as the sibling doMoveUnitTowardsNearest (0x003C9404); a member
// that finds none ends the action.
// Target differences from the donor: no object-type-list fallback and the
// filter chain is BFME 2's linked one. Donor-carried: the thing /
// polygon-trigger / same-map meaning of the three filters.
// Shape: DLINK_ITERATOR<Object>::advance and Team::iterate_TeamMemberList are
// defined inline over the virtual-inheritance Object layout of
// TeamIterateTeamMemberList.cpp (neither is inlined); with only their
// declarations the member lands in EAX and is copied to EDI where retail
// loads EDI directly.
//
// The filters are BFME2's partition filter chain as in
// ScriptActions_doMoveUnitTowardsNearest.cpp: a vptr, the +0x04 link to the
// next filter (PartitionFilter::link 0x00625790), then each filter's members;
// address-derived names after allow (slot 1), the ctors being inline.
#include "ascii_string.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../Common/PartitionRangeQueryCallView.h"

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

class Object;

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
	unsigned char m_pad04[0x34];
	Coord3D m_pos;			// +0x38
	unsigned char m_pad44[0x24];
};

class Object : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
	public BfmeObjectDlinkPad, public BfmeObjectVbptrCarrier
{
public:
	AIUpdateInterface *getAIUpdateInterface() { return m_ai; }
	const Coord3D *getPosition() const { return &m_pos; }
private:
	unsigned char m_pad070[0x258 - 0x70];
	AIUpdateInterface *m_ai;	// +0x258
};

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);	// 0x002D06CA
};
extern ThingFactory *TheThingFactory;

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

class Team
{
public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const { return DLINK_ITERATOR<Object>(m_head, &Object::dlink_next_TeamMemberList); }
private:
	unsigned char m_pad00[0x38];
	Object *m_head;
};

class ScriptEngine
{
public:
	Team *getTeamNamed(AsciiString name, bool exact);			// 0x003584E9
	PolygonTrigger *getQualifiedTriggerAreaByName(AsciiString name);	// 0x0035768D
};
extern ScriptEngine *TheScriptEngine;

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
		if (ai) {
			Object *bestObj = ThePartitionManager->getClosestObject(obj->getPosition(), REALLY_FAR, FROM_CENTER_3D,
				Rva00261750Filter(templ, true).link(Rva00261723Filter(trig).link(&Rva002611BFFilter(obj))));
			if (!bestObj)
				return;
			ai->m_commands.aiMoveToObject(bestObj, CMD_FROM_SCRIPT);
		}
	}
}

