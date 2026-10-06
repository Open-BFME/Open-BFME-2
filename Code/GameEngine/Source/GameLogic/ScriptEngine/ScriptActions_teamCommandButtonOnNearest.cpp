// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX
//
// Zero Hour's ScriptActions::doTeamUseCommandButtonOnNearest* family as BFME2
// builds it (all called from the action dispatcher 0x003CA4BE):
//
//   0x003C10D8  doTeamUseCommandButtonOnNearestEnemy
//   0x003C1322  doTeamUseCommandButtonOnNearestGarrisonedBuilding
//   0x003C15BA  doTeamUseCommandButtonOnNearestKindof
//   0x003C1839  doTeamUseCommandButtonOnNearestBuilding
//   0x003C1AB7  doTeamUseCommandButtonOnNearestBuildingClass
//   0x003C7018  a BFME2 form (called at 0x003CD3F5): within the given
//               range (from the 3D centre) of the group's centre, the enemy
//               (or, without +0x1C bit 5, the valid target) whose template
//               ranks highest by its +0x5DA word, with no kind filter and
//               no isReady check, and the team's controlling player required
//               (the dispatcher's fourth, boolean argument goes unused)
//
// Zero Hour's shape (the team's group, the button's source object through
// the special-power or command-type lookup, the closest target to the group
// centre) with BFME2's changes: the source must pass CommandButton::isReady;
// every search rejects kinds 54, 89 and 130 (folded into the kind-7 filter
// for BuildingClass); a button with its +0x1C bit 5 set targets the found
// object's position (groupDoCommandButtonAtPosition) and leaves out the
// valid-target filter; the filters are linked (built inner first) and
// measured from the 3D centre.
//
// The filters are BFME2's partition filter chain (the view
// AIStructureCreepTactic.cpp documents): a vptr, the +0x04 link to the next
// filter (PartitionFilter::link 0x00625790), then each filter's members;
// address-derived names after the out-of-line ctor, else after allow
// (slot 1). Retail updates the unwind state only after the kind filters
// are built, so the bitset and kind-filter ctors are declared throw() here.
#include <string.h>
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

// A KindOfMaskType as the mask filters copy it (0x0004543D).
class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other) throw();
private:
	unsigned char m_bytes[28];
};

// vftable 0x00BC2908, allow 0x002610DE: accept what has every kind of the
// first mask and none of the second (ZH's PartitionFilterAcceptByKindOf).
class Rva0004584D : public Rva000421C8
{
public:
	Rva0004584D(const BfmeFixedStorage0004543D &a, const BfmeFixedStorage0004543D &b) throw();
	virtual bool allow(Object *obj);
	BfmeFixedStorage0004543D m_08;
	BfmeFixedStorage0004543D m_24;
};

// vftable 0x00C004D8, allow 0x00261409: the player's relationship to the
// object's team against the +0x10 flags (ZH's PartitionFilterRelationship
// analogue), +0x0C whether a hit allows.
class Rva00261409Filter : public Rva000421C8
{
public:
	Rva00261409Filter(Player *player, bool match, int flags)
		: m_player(player), m_match(match), m_flags(flags) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	Player *m_player;
	bool m_match;
	int m_flags;
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

class CommandButton;

// A KindOfMaskType view: 224 bits, zeroed then set bit by bit.
struct Rva003C10D8Mask
{
	Rva003C10D8Mask() { memset(this, 0, sizeof(*this)); }
	void set(int bit) { m_bits[bit >> 5] |= 1u << (bit & 31); }
	unsigned int m_bits[7];
};

struct Rva00045411BitSet
{
	Rva00045411BitSet(int unused, int bit) throw();	// 0x00045411
	unsigned int m_bits[7];
};
extern unsigned char g_00DFEFA4StoragePrototype[28];

// vftable 0x00C1FE34, allow 0x002614BC: +0x08 the source object, +0x0C the
// command button, +0x10 whether a valid target allows, +0x14 the command
// source (Zero Hour's PartitionFilterValidCommandButtonTarget).
class Rva002614BCFilter : public Rva000421C8
{
public:
	Rva002614BCFilter(Object *source, const CommandButton *button, bool match, int cmdSource)
		: m_source(source), m_button(button), m_match(match), m_cmdSource(cmdSource) {}
	virtual bool allow(Object *obj);
	Object *m_source;
	const CommandButton *m_button;
	bool m_match;
	int m_cmdSource;
};

// vftable 0x00C1FE04, allow 0x0026144C: +0x08 a flag (Zero Hour's
// PartitionFilterGarrisonable).
class Rva0026144CFilter : public Rva000421C8
{
public:
	Rva0026144CFilter(bool match) : m_match(match) {}
	virtual bool allow(Object *obj);
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

enum GUICommandType
{
	GUI_COMMAND_NONE = 0
};

class ThingTemplate
{
public:
	char m_pad000[0x5DA];
	unsigned short m_5DA;	// +0x5DA
};

class Object
{
public:
	const Coord3D *getPosition() const { return &m_pos; }
	const ThingTemplate *getTemplate() const { return m_template; }
	char m_pad000[0x04];
	const ThingTemplate *m_template;	// +0x04
	char m_pad008[0x38 - 0x08];
	Coord3D m_pos;			// +0x38
};

struct BfmeWideResult
{
	Object *next() throw();	// 0x00045623
	~BfmeWideResult();	// 0x0004AA28
	void *m_value;
};

class Overridable
{
public:
	const Overridable *friend_getFinalOverride() const;	// 0x00288609
};

class SpecialPowerTemplate : public Overridable
{
public:
	unsigned int getID() const
	{
		return ((const SpecialPowerTemplate *)friend_getFinalOverride())->m_id;
	}
	char m_pad00[0x14];
	unsigned int m_id;	// +0x14
};

class CommandButton
{
public:
	bool isReady(const Object *obj) const;	// 0x0035B069
	GUICommandType getCommandType() const { return m_command; }
	const SpecialPowerTemplate *getSpecialPowerTemplate() const { return m_specialPower; }
	bool rva003BDCCA() const { return (m_options >> 5) & 1; }
	char m_pad00[0x14];
	GUICommandType m_command;				// +0x14
	char m_pad18[0x1C - 0x18];
	unsigned int m_options;					// +0x1C
	char m_pad20[0x44 - 0x20];
	const SpecialPowerTemplate *m_specialPower;		// +0x44
};

class ControlBar
{
public:
	const CommandButton *findCommandButton(const AsciiString &name);	// 0x0031BE3C
};
extern ControlBar *TheControlBar;

class AIGroup
{
public:
	Object *getSpecialPowerSourceObject(unsigned int specialPowerID);		// 0x0036E111
	Object *getCommandButtonSourceObject(GUICommandType type);			// 0x0036E158
	bool getCenter(Coord3D *center);						// 0x0036D035
	void groupDoCommandButtonAtPosition(const CommandButton *button, const Coord3D *pos,
		CommandSourceType source);						// 0x0036DCB8
	void groupDoCommandButtonAtObject(const CommandButton *button, Object *obj,
		CommandSourceType source);						// 0x0036DCE7
};

class AI
{
public:
	AIGroup *createGroup();	// 0x002FEC4B
};
extern AI *TheAI;

class Team
{
public:
	Player *getControllingPlayer() const;	// 0x0039D7CF
	void getTeamAsAIGroup(AIGroup *group);	// 0x003A0F62
};

class ScriptEngine
{
public:
	Team *getTeamNamed(AsciiString name, bool exact);	// 0x003584E9
};
extern ScriptEngine *TheScriptEngine;

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *pos, float maxDist, int dc,
		Rva000421C8 *filters);	// 0x00625360
	BfmeWideResult iterateObjectsInRange(const Coord3D *pos, float radius, int distCalc,
		Rva000421C8 *filters, int order);	// 0x00625610
};
extern PartitionManager *ThePartitionManager;

#define REALLY_FAR (100000 * 10.0f)

class ScriptActions
{
protected:
	void doTeamUseCommandButtonOnNearestEnemy(const AsciiString &teamName, const AsciiString &commandAbility);
	void doTeamUseCommandButtonOnNearestGarrisonedBuilding(const AsciiString &teamName, const AsciiString &commandAbility);
	void doTeamUseCommandButtonOnNearestKindof(const AsciiString &teamName, const AsciiString &commandAbility, int kindofBit);
	void doTeamUseCommandButtonOnNearestBuilding(const AsciiString &teamName, const AsciiString &commandAbility);
	void doTeamUseCommandButtonOnNearestBuildingClass(const AsciiString &teamName, const AsciiString &commandAbility, int kindofBit);
public:
	void rva003C7018(const AsciiString &teamName, const AsciiString &commandAbility, float range, bool flag);
};

void ScriptActions::doTeamUseCommandButtonOnNearestEnemy(const AsciiString &teamName, const AsciiString &commandAbility)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (!team)
		return;

	AIGroup *theGroup = TheAI->createGroup();
	team->getTeamAsAIGroup(theGroup);

	const CommandButton *commandButton = TheControlBar->findCommandButton(commandAbility);
	if (!commandButton)
		return;

	Object *srcObj;
	if (commandButton->getSpecialPowerTemplate())
		srcObj = theGroup->getSpecialPowerSourceObject(commandButton->getSpecialPowerTemplate()->getID());
	else
		srcObj = theGroup->getCommandButtonSourceObject(commandButton->getCommandType());
	if (!srcObj)
		return;
	if (!commandButton->isReady(srcObj))
		return;

	Coord3D pos;
	theGroup->getCenter(&pos);

	Rva003C10D8Mask mask;
	mask.set(89);
	mask.set(54);
	mask.set(130);
	if (commandButton->rva003BDCCA()) {
		Object *obj = ThePartitionManager->getClosestObject(&pos, REALLY_FAR, 0,
			Rva00261409Filter(team->getControllingPlayer(), true, 4)
				.link(Rva0004584D(*(BfmeFixedStorage0004543D *)g_00DFEFA4StoragePrototype,
					*(BfmeFixedStorage0004543D *)&mask).link(&Rva002611BFFilter(srcObj))));
		if (!obj)
			return;
		theGroup->groupDoCommandButtonAtPosition(commandButton, obj->getPosition(), CMD_FROM_SCRIPT);
	} else {
		Object *obj = ThePartitionManager->getClosestObject(&pos, REALLY_FAR, 0,
			Rva00261409Filter(team->getControllingPlayer(), true, 4)
				.link(Rva002614BCFilter(srcObj, commandButton, true, CMD_FROM_SCRIPT)
					.link(Rva0004584D(*(BfmeFixedStorage0004543D *)g_00DFEFA4StoragePrototype,
						*(BfmeFixedStorage0004543D *)&mask).link(&Rva002611BFFilter(srcObj)))));
		if (!obj)
			return;
		theGroup->groupDoCommandButtonAtObject(commandButton, obj, CMD_FROM_SCRIPT);
	}
}

void ScriptActions::doTeamUseCommandButtonOnNearestGarrisonedBuilding(const AsciiString &teamName, const AsciiString &commandAbility)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (!team)
		return;

	AIGroup *theGroup = TheAI->createGroup();
	team->getTeamAsAIGroup(theGroup);

	const CommandButton *commandButton = TheControlBar->findCommandButton(commandAbility);
	if (!commandButton)
		return;

	Object *srcObj;
	if (commandButton->getSpecialPowerTemplate())
		srcObj = theGroup->getSpecialPowerSourceObject(commandButton->getSpecialPowerTemplate()->getID());
	else
		srcObj = theGroup->getCommandButtonSourceObject(commandButton->getCommandType());
	if (!srcObj)
		return;
	if (!commandButton->isReady(srcObj))
		return;

	Coord3D pos;
	theGroup->getCenter(&pos);

	Rva003C10D8Mask mask;
	mask.set(89);
	mask.set(54);
	mask.set(130);
	if (commandButton->rva003BDCCA()) {
		Object *obj = ThePartitionManager->getClosestObject(&pos, REALLY_FAR, 0,
			Rva00261409Filter(team->getControllingPlayer(), true, 4)
				.link(Rva0004584D(*(BfmeFixedStorage0004543D *)g_00DFEFA4StoragePrototype,
					*(BfmeFixedStorage0004543D *)&mask).link(&Rva002611BFFilter(srcObj))));
		if (!obj)
			return;
		theGroup->groupDoCommandButtonAtPosition(commandButton, obj->getPosition(), CMD_FROM_SCRIPT);
	} else {
		Object *obj = ThePartitionManager->getClosestObject(&pos, REALLY_FAR, 0,
			Rva00261409Filter(team->getControllingPlayer(), true, 4)
				.link(Rva0004584D(*(BfmeFixedStorage0004543D *)&Rva00045411BitSet(0, 7), *(BfmeFixedStorage0004543D *)g_00DFEFA4StoragePrototype).link(Rva0026144CFilter(true).link(Rva002614BCFilter(srcObj, commandButton, true, CMD_FROM_SCRIPT)
					.link(Rva0004584D(*(BfmeFixedStorage0004543D *)g_00DFEFA4StoragePrototype,
						*(BfmeFixedStorage0004543D *)&mask).link(&Rva002611BFFilter(srcObj)))))));
		if (!obj)
			return;
		theGroup->groupDoCommandButtonAtObject(commandButton, obj, CMD_FROM_SCRIPT);
	}
}

void ScriptActions::doTeamUseCommandButtonOnNearestKindof(const AsciiString &teamName, const AsciiString &commandAbility, int kindofBit)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (!team)
		return;

	AIGroup *theGroup = TheAI->createGroup();
	team->getTeamAsAIGroup(theGroup);

	const CommandButton *commandButton = TheControlBar->findCommandButton(commandAbility);
	if (!commandButton)
		return;

	Object *srcObj;
	if (commandButton->getSpecialPowerTemplate())
		srcObj = theGroup->getSpecialPowerSourceObject(commandButton->getSpecialPowerTemplate()->getID());
	else
		srcObj = theGroup->getCommandButtonSourceObject(commandButton->getCommandType());
	if (!srcObj)
		return;
	if (!commandButton->isReady(srcObj))
		return;

	Coord3D pos;
	theGroup->getCenter(&pos);

	Rva003C10D8Mask mask;
	mask.set(89);
	mask.set(54);
	mask.set(130);
	if (commandButton->rva003BDCCA()) {
		Object *obj = ThePartitionManager->getClosestObject(&pos, REALLY_FAR, 0,
			Rva00261409Filter(team->getControllingPlayer(), true, 4)
				.link(Rva0004584D(*(BfmeFixedStorage0004543D *)g_00DFEFA4StoragePrototype,
					*(BfmeFixedStorage0004543D *)&mask).link(&Rva002611BFFilter(srcObj))));
		if (!obj)
			return;
		theGroup->groupDoCommandButtonAtPosition(commandButton, obj->getPosition(), CMD_FROM_SCRIPT);
	} else {
		Object *obj = ThePartitionManager->getClosestObject(&pos, REALLY_FAR, 0,
			Rva00261409Filter(team->getControllingPlayer(), true, 4)
				.link(Rva0004584D(*(BfmeFixedStorage0004543D *)&Rva00045411BitSet(0, kindofBit), *(BfmeFixedStorage0004543D *)g_00DFEFA4StoragePrototype).link(Rva002614BCFilter(srcObj, commandButton, true, CMD_FROM_SCRIPT)
					.link(Rva0004584D(*(BfmeFixedStorage0004543D *)g_00DFEFA4StoragePrototype,
						*(BfmeFixedStorage0004543D *)&mask).link(&Rva002611BFFilter(srcObj))))));
		if (!obj)
			return;
		theGroup->groupDoCommandButtonAtObject(commandButton, obj, CMD_FROM_SCRIPT);
	}
}

void ScriptActions::doTeamUseCommandButtonOnNearestBuilding(const AsciiString &teamName, const AsciiString &commandAbility)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (!team)
		return;

	AIGroup *theGroup = TheAI->createGroup();
	team->getTeamAsAIGroup(theGroup);

	const CommandButton *commandButton = TheControlBar->findCommandButton(commandAbility);
	if (!commandButton)
		return;

	Object *srcObj;
	if (commandButton->getSpecialPowerTemplate())
		srcObj = theGroup->getSpecialPowerSourceObject(commandButton->getSpecialPowerTemplate()->getID());
	else
		srcObj = theGroup->getCommandButtonSourceObject(commandButton->getCommandType());
	if (!srcObj)
		return;
	if (!commandButton->isReady(srcObj))
		return;

	Coord3D pos;
	theGroup->getCenter(&pos);

	Rva003C10D8Mask mask;
	mask.set(89);
	mask.set(54);
	mask.set(130);
	if (commandButton->rva003BDCCA()) {
		Object *obj = ThePartitionManager->getClosestObject(&pos, REALLY_FAR, 0,
			Rva00261409Filter(team->getControllingPlayer(), true, 4)
				.link(Rva0004584D(*(BfmeFixedStorage0004543D *)g_00DFEFA4StoragePrototype,
					*(BfmeFixedStorage0004543D *)&mask).link(&Rva002611BFFilter(srcObj))));
		if (!obj)
			return;
		theGroup->groupDoCommandButtonAtPosition(commandButton, obj->getPosition(), CMD_FROM_SCRIPT);
	} else {
		Object *obj = ThePartitionManager->getClosestObject(&pos, REALLY_FAR, 0,
			Rva00261409Filter(team->getControllingPlayer(), true, 4)
				.link(Rva0004584D(*(BfmeFixedStorage0004543D *)&Rva00045411BitSet(0, 7), *(BfmeFixedStorage0004543D *)g_00DFEFA4StoragePrototype).link(Rva002614BCFilter(srcObj, commandButton, true, CMD_FROM_SCRIPT)
					.link(Rva0004584D(*(BfmeFixedStorage0004543D *)g_00DFEFA4StoragePrototype,
						*(BfmeFixedStorage0004543D *)&mask).link(&Rva002611BFFilter(srcObj))))));
		if (!obj)
			return;
		theGroup->groupDoCommandButtonAtObject(commandButton, obj, CMD_FROM_SCRIPT);
	}
}

void ScriptActions::doTeamUseCommandButtonOnNearestBuildingClass(const AsciiString &teamName, const AsciiString &commandAbility, int kindofBit)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (!team)
		return;

	AIGroup *theGroup = TheAI->createGroup();
	team->getTeamAsAIGroup(theGroup);

	const CommandButton *commandButton = TheControlBar->findCommandButton(commandAbility);
	if (!commandButton)
		return;

	Object *srcObj;
	if (commandButton->getSpecialPowerTemplate())
		srcObj = theGroup->getSpecialPowerSourceObject(commandButton->getSpecialPowerTemplate()->getID());
	else
		srcObj = theGroup->getCommandButtonSourceObject(commandButton->getCommandType());
	if (!srcObj)
		return;
	if (!commandButton->isReady(srcObj))
		return;

	Coord3D pos;
	theGroup->getCenter(&pos);

	Rva003C10D8Mask mask;
	mask.set(89);
	mask.set(54);
	mask.set(130);
	if (commandButton->rva003BDCCA()) {
		Object *obj = ThePartitionManager->getClosestObject(&pos, REALLY_FAR, 0,
			Rva00261409Filter(team->getControllingPlayer(), true, 4)
				.link(Rva0004584D(*(BfmeFixedStorage0004543D *)&Rva00045411BitSet(0, 7),
				*(BfmeFixedStorage0004543D *)&mask)
				.link(Rva0004584D(*(BfmeFixedStorage0004543D *)&Rva00045411BitSet(0, kindofBit),
				*(BfmeFixedStorage0004543D *)g_00DFEFA4StoragePrototype)
				.link(&Rva002611BFFilter(srcObj)))));
		if (!obj)
			return;
		theGroup->groupDoCommandButtonAtPosition(commandButton, obj->getPosition(), CMD_FROM_SCRIPT);
	} else {
		Object *obj = ThePartitionManager->getClosestObject(&pos, REALLY_FAR, 0,
			Rva00261409Filter(team->getControllingPlayer(), true, 4)
				.link(Rva0004584D(*(BfmeFixedStorage0004543D *)&Rva00045411BitSet(0, 7),
				*(BfmeFixedStorage0004543D *)&mask)
				.link(Rva0004584D(*(BfmeFixedStorage0004543D *)&Rva00045411BitSet(0, kindofBit),
				*(BfmeFixedStorage0004543D *)g_00DFEFA4StoragePrototype)
				.link(Rva002614BCFilter(srcObj, commandButton, true, CMD_FROM_SCRIPT)
				.link(&Rva002611BFFilter(srcObj))))));
		if (!obj)
			return;
		theGroup->groupDoCommandButtonAtObject(commandButton, obj, CMD_FROM_SCRIPT);
	}
}

void ScriptActions::rva003C7018(const AsciiString &teamName, const AsciiString &commandAbility, float range, bool)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (!team)
		return;

	AIGroup *theGroup = TheAI->createGroup();
	team->getTeamAsAIGroup(theGroup);
	Player *controller = team->getControllingPlayer();
	if (!controller)
		return;

	const CommandButton *commandButton = TheControlBar->findCommandButton(commandAbility);
	if (!commandButton)
		return;

	Object *srcObj;
	if (commandButton->getSpecialPowerTemplate())
		srcObj = theGroup->getSpecialPowerSourceObject(commandButton->getSpecialPowerTemplate()->getID());
	else
		srcObj = theGroup->getCommandButtonSourceObject(commandButton->getCommandType());
	if (!srcObj)
		return;

	Coord3D pos;
	theGroup->getCenter(&pos);

	if (commandButton->rva003BDCCA()) {
		BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(&pos, range, 0,
			Rva00261409Filter(team->getControllingPlayer(), true, 4).link(&Rva002611BFFilter(srcObj)), 0);
		Object *best = hits.next();
		Object *obj;
		while ((obj = hits.next()) != 0)
			if (obj->getTemplate()->m_5DA > best->getTemplate()->m_5DA)
				best = obj;
		if (best)
			theGroup->groupDoCommandButtonAtPosition(commandButton, best->getPosition(), CMD_FROM_SCRIPT);
	} else {
		BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(&pos, range, 0,
			Rva00261409Filter(team->getControllingPlayer(), true, 4).link(
				Rva002614BCFilter(srcObj, commandButton, true, CMD_FROM_SCRIPT).link(&Rva002611BFFilter(srcObj))), 0);
		Object *best = hits.next();
		Object *obj;
		while ((obj = hits.next()) != 0)
			if (obj->getTemplate()->m_5DA > best->getTemplate()->m_5DA)
				best = obj;
		if (best)
			theGroup->groupDoCommandButtonAtObject(commandButton, best, CMD_FROM_SCRIPT);
	}
}
