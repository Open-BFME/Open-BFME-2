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

#include "../../../Include/GameLogic/PartitionFilter.h"

// A KindOfMaskType as the mask filters copy it (0x0004543D).
#include "../../../Include/Common/BfmeFixedStorage0004543D.h"

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
#include "../../../Include/GameLogic/Rva00261409Filter.h"

// vftable 0x00BF91BC, allow 0x002611BF.
#include "../../../Include/GameLogic/Rva002611BFFilter.h"

class CommandButton;

// A KindOfMaskType view: 224 bits, zeroed then set bit by bit.
struct Rva003C10D8Mask
{
	Rva003C10D8Mask() { memset(this, 0, sizeof(*this)); }
	void set(int bit) { m_bits[bit >> 5] |= 1u << (bit & 31); }
	unsigned int m_bits[7];
};

#include "../../../Include/GameLogic/Module/Rva00045411BitSet.h"
template <int N> class BitFlags;
extern BitFlags<116> KINDOFMASK_NONE;

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

#include "../../../../Libraries/Include/Lib/Coord3D.h"

enum CommandSourceType
{
	CMD_FROM_SCRIPT = 1
};

enum GUICommandType
{
	GUI_COMMAND_NONE = 0
};

#include "../../../Include/Common/ThingTemplate.h"

// ContainModuleInterface view for allow 0x0026144C: isGarrisonable is
// vtable slot 4 (the +0x10 call); the preceding slots are never called here.
#define CONTAIN_GAP(n) virtual void gap##n();
#include "../../../Include/GameLogic/Module/ContainModule.h"

class Object
{
public:
	const Coord3D *getPosition() const { return &m_pos; }
	const ThingTemplate *getTemplate() const { return m_template; }
	char m_pad000[0x04];
	const ThingTemplate *m_template;	// +0x04
	char m_pad008[0x38 - 0x08];
	Coord3D m_pos;			// +0x38
	char m_pad044[0x250 - 0x44];
	ContainModuleInterface *m_contain;	// +0x250
};

// Retail 0x0026144C (41B, vftable 0x00C1FE04 slot 1): Zero Hour's
// PartitionFilterGarrisonable::allow. Without a contain module the flag
// decides; otherwise the garrisonable query must equal the flag.
bool Rva0026144CFilter::allow(Object *obj)
{
	ContainModuleInterface *cmi = obj->m_contain;
	if (!cmi)
		return !m_match;
	return cmi->isGarrisonable() == m_match;
}

#include "../../Common/PartitionRangeQueryCallView.h"

#include "../../../Include/Common/Overridable.h"
#include "../../../Include/Common/SpecialPower.h"
#include "../../../Include/GameClient/CommandButton.h"
#include "ScriptActionsCommandButtonOptions.h"

#include "../../../Include/GameClient/ControlBar.h"
extern ControlBar *TheControlBar;

#include "../../../Include/GameLogic/AIGroup.h"

#include "../../../Include/GameLogic/AI.h"
extern AI *TheAI;

#include "../../../Include/Common/TeamBFME2.h"

#include "../../../Include/GameLogic/ScriptEngine.h"
extern ScriptEngine *TheScriptEngine;

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
	void doSkirmishCommandButtonOnMostValuable(const AsciiString &teamName, const AsciiString &commandAbility, float range, bool flag);
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
	if (needsTargetPosition(commandButton)) {
		Object *obj = ThePartitionManager->getClosestObject(&pos, 100000 * 10.0f, 0,
			Rva00261409Filter(team->getControllingPlayer(), true, 4)
				.link(Rva0004584D(*(BfmeFixedStorage0004543D *)&KINDOFMASK_NONE,
					*(BfmeFixedStorage0004543D *)&mask).link(&Rva002611BFFilter(srcObj))));
		if (!obj)
			return;
		theGroup->groupDoCommandButtonAtPosition(commandButton, obj->getPosition(), CMD_FROM_SCRIPT);
	} else {
		Object *obj = ThePartitionManager->getClosestObject(&pos, 100000 * 10.0f, 0,
			Rva00261409Filter(team->getControllingPlayer(), true, 4)
				.link(Rva002614BCFilter(srcObj, commandButton, true, CMD_FROM_SCRIPT)
					.link(Rva0004584D(*(BfmeFixedStorage0004543D *)&KINDOFMASK_NONE,
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
	if (needsTargetPosition(commandButton)) {
		Object *obj = ThePartitionManager->getClosestObject(&pos, 100000 * 10.0f, 0,
			Rva00261409Filter(team->getControllingPlayer(), true, 4)
				.link(Rva0004584D(*(BfmeFixedStorage0004543D *)&KINDOFMASK_NONE,
					*(BfmeFixedStorage0004543D *)&mask).link(&Rva002611BFFilter(srcObj))));
		if (!obj)
			return;
		theGroup->groupDoCommandButtonAtPosition(commandButton, obj->getPosition(), CMD_FROM_SCRIPT);
	} else {
		Object *obj = ThePartitionManager->getClosestObject(&pos, 100000 * 10.0f, 0,
			Rva00261409Filter(team->getControllingPlayer(), true, 4)
				.link(Rva0004584D(*(BfmeFixedStorage0004543D *)&Rva00045411BitSet(0, 7), *(BfmeFixedStorage0004543D *)&KINDOFMASK_NONE).link(Rva0026144CFilter(true).link(Rva002614BCFilter(srcObj, commandButton, true, CMD_FROM_SCRIPT)
					.link(Rva0004584D(*(BfmeFixedStorage0004543D *)&KINDOFMASK_NONE,
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
	if (needsTargetPosition(commandButton)) {
		Object *obj = ThePartitionManager->getClosestObject(&pos, 100000 * 10.0f, 0,
			Rva00261409Filter(team->getControllingPlayer(), true, 4)
				.link(Rva0004584D(*(BfmeFixedStorage0004543D *)&KINDOFMASK_NONE,
					*(BfmeFixedStorage0004543D *)&mask).link(&Rva002611BFFilter(srcObj))));
		if (!obj)
			return;
		theGroup->groupDoCommandButtonAtPosition(commandButton, obj->getPosition(), CMD_FROM_SCRIPT);
	} else {
		Object *obj = ThePartitionManager->getClosestObject(&pos, 100000 * 10.0f, 0,
			Rva00261409Filter(team->getControllingPlayer(), true, 4)
				.link(Rva0004584D(*(BfmeFixedStorage0004543D *)&Rva00045411BitSet(0, kindofBit), *(BfmeFixedStorage0004543D *)&KINDOFMASK_NONE).link(Rva002614BCFilter(srcObj, commandButton, true, CMD_FROM_SCRIPT)
					.link(Rva0004584D(*(BfmeFixedStorage0004543D *)&KINDOFMASK_NONE,
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
	if (needsTargetPosition(commandButton)) {
		Object *obj = ThePartitionManager->getClosestObject(&pos, 100000 * 10.0f, 0,
			Rva00261409Filter(team->getControllingPlayer(), true, 4)
				.link(Rva0004584D(*(BfmeFixedStorage0004543D *)&KINDOFMASK_NONE,
					*(BfmeFixedStorage0004543D *)&mask).link(&Rva002611BFFilter(srcObj))));
		if (!obj)
			return;
		theGroup->groupDoCommandButtonAtPosition(commandButton, obj->getPosition(), CMD_FROM_SCRIPT);
	} else {
		Object *obj = ThePartitionManager->getClosestObject(&pos, 100000 * 10.0f, 0,
			Rva00261409Filter(team->getControllingPlayer(), true, 4)
				.link(Rva0004584D(*(BfmeFixedStorage0004543D *)&Rva00045411BitSet(0, 7), *(BfmeFixedStorage0004543D *)&KINDOFMASK_NONE).link(Rva002614BCFilter(srcObj, commandButton, true, CMD_FROM_SCRIPT)
					.link(Rva0004584D(*(BfmeFixedStorage0004543D *)&KINDOFMASK_NONE,
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
	if (needsTargetPosition(commandButton)) {
		Object *obj = ThePartitionManager->getClosestObject(&pos, 100000 * 10.0f, 0,
			Rva00261409Filter(team->getControllingPlayer(), true, 4)
				.link(Rva0004584D(*(BfmeFixedStorage0004543D *)&Rva00045411BitSet(0, 7),
				*(BfmeFixedStorage0004543D *)&mask)
				.link(Rva0004584D(*(BfmeFixedStorage0004543D *)&Rva00045411BitSet(0, kindofBit),
				*(BfmeFixedStorage0004543D *)&KINDOFMASK_NONE)
				.link(&Rva002611BFFilter(srcObj)))));
		if (!obj)
			return;
		theGroup->groupDoCommandButtonAtPosition(commandButton, obj->getPosition(), CMD_FROM_SCRIPT);
	} else {
		Object *obj = ThePartitionManager->getClosestObject(&pos, 100000 * 10.0f, 0,
			Rva00261409Filter(team->getControllingPlayer(), true, 4)
				.link(Rva0004584D(*(BfmeFixedStorage0004543D *)&Rva00045411BitSet(0, 7),
				*(BfmeFixedStorage0004543D *)&mask)
				.link(Rva0004584D(*(BfmeFixedStorage0004543D *)&Rva00045411BitSet(0, kindofBit),
				*(BfmeFixedStorage0004543D *)&KINDOFMASK_NONE)
				.link(Rva002614BCFilter(srcObj, commandButton, true, CMD_FROM_SCRIPT)
				.link(&Rva002611BFFilter(srcObj))))));
		if (!obj)
			return;
		theGroup->groupDoCommandButtonAtObject(commandButton, obj, CMD_FROM_SCRIPT);
	}
}

void ScriptActions::doSkirmishCommandButtonOnMostValuable(const AsciiString &teamName, const AsciiString &commandAbility, float range, bool)
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

	if (needsTargetPosition(commandButton)) {
		BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(&pos, range, 0,
			Rva00261409Filter(team->getControllingPlayer(), true, 4).link(&Rva002611BFFilter(srcObj)), 0);
		Object *best = hits.next();
		Object *obj;
		while ((obj = hits.next()) != 0)
			if (obj->getTemplate()->m_buildCost > best->getTemplate()->m_buildCost)
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
			if (obj->getTemplate()->m_buildCost > best->getTemplate()->m_buildCost)
				best = obj;
		if (best)
			theGroup->groupDoCommandButtonAtObject(commandButton, best, CMD_FROM_SCRIPT);
	}
}
