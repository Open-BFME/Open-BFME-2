// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// BFME2's garrison script actions and their shared contain helpers, from
// WorldBuilder's ScriptActions.cpp (debug build, names and statement order):
//
//   0x003C4B97 (112B) unnamed static helper: move every object a source
//              container lists into the destination container. Retail passes
//              its one argument (a two-pointer record) in EDI, the register
//              convention cl 7.1 gives a TU-local static whose callers are
//              all in the same unit, so all three callers live here.
//   0x003C5334 (91B)  ScriptActions::putUnitInContain
//   0x003C65F7 (250B) ScriptActions::doTeamGarrisonSpecificBuilding
//   0x003C8E89 (253B) ScriptActions::doUnitGarrisonSpecificBuilding
//   0x003C538F (118B) unnamed WB member (0x01007020): from a rotating
//              position in a list of object ids, the next container that
//              will take the unit
//   0x003C6EFC (284B) unnamed WB member (0x01007100), dispatched right after
//              TEAM_GARRISON_SPECIFIC_BUILDING with the flag fixed to true:
//              put every free member of one team into the containers of
//              another team's members, round robin
//
// Target facts: Object +0x04 template (kind-of bits at template +0x108),
// +0x250 contain module, +0x258 AI update (WorldBuilder's debug Object is
// 8 bytes longer ahead of these: +0x258/+0x260). Contain vtable slots
// 0x98 (valid-for, three arguments), 0x9C (add), 0x7C (inner container
// accessor) and 0x144 (entering-player mask) are read from retail; WB's
// debug vtable has the first two four bytes lower. Donor facts: BFME1's
// doTeam/doUnitGarrisonSpecificBuilding (no third argument there) give the
// player-mask test and the group-enter / aiEnter paths. Kind-of bits 0x76
// and 0x6D, status 0x26 and the inner container slots 0xA8 / 0x10C carry no
// established names.

#include "ascii_string.h"
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

#include <vector>

class Object;
class Team;
class Player;
enum CommandSourceType { CMD_FROM_SCRIPT = 1 };

class ContainedObjectSource
{
public:
#define SRC_SLOT(n) virtual void slot##n();
	SRC_SLOT(0) SRC_SLOT(1) SRC_SLOT(2) SRC_SLOT(3) SRC_SLOT(4) SRC_SLOT(5)
	SRC_SLOT(6) SRC_SLOT(7) SRC_SLOT(8) SRC_SLOT(9) SRC_SLOT(10) SRC_SLOT(11)
	SRC_SLOT(12) SRC_SLOT(13) SRC_SLOT(14) SRC_SLOT(15) SRC_SLOT(16) SRC_SLOT(17)
	SRC_SLOT(18) SRC_SLOT(19) SRC_SLOT(20) SRC_SLOT(21) SRC_SLOT(22) SRC_SLOT(23)
	SRC_SLOT(24) SRC_SLOT(25) SRC_SLOT(26) SRC_SLOT(27) SRC_SLOT(28) SRC_SLOT(29)
	SRC_SLOT(30) SRC_SLOT(31) SRC_SLOT(32) SRC_SLOT(33) SRC_SLOT(34) SRC_SLOT(35)
	SRC_SLOT(36) SRC_SLOT(37) SRC_SLOT(38) SRC_SLOT(39) SRC_SLOT(40) SRC_SLOT(41)
#undef SRC_SLOT
	virtual void removeObject(const Object *obj); // slot 0xA8
#define SRC_SLOT(n) virtual void slot##n();
	SRC_SLOT(43) SRC_SLOT(44) SRC_SLOT(45) SRC_SLOT(46) SRC_SLOT(47) SRC_SLOT(48)
	SRC_SLOT(49) SRC_SLOT(50) SRC_SLOT(51) SRC_SLOT(52) SRC_SLOT(53) SRC_SLOT(54)
	SRC_SLOT(55) SRC_SLOT(56) SRC_SLOT(57) SRC_SLOT(58) SRC_SLOT(59) SRC_SLOT(60)
	SRC_SLOT(61) SRC_SLOT(62) SRC_SLOT(63) SRC_SLOT(64) SRC_SLOT(65) SRC_SLOT(66)
#undef SRC_SLOT
	virtual void getObjects(_STL::list<const Object *> &objects); // slot 0x10C
};

class ContainModuleInterface
{
public:
#define CONTAIN_SLOT(n) virtual void slot##n();
	CONTAIN_SLOT(0) CONTAIN_SLOT(1) CONTAIN_SLOT(2) CONTAIN_SLOT(3)
	CONTAIN_SLOT(4) CONTAIN_SLOT(5) CONTAIN_SLOT(6) CONTAIN_SLOT(7)
	CONTAIN_SLOT(8) CONTAIN_SLOT(9) CONTAIN_SLOT(10) CONTAIN_SLOT(11)
	CONTAIN_SLOT(12) CONTAIN_SLOT(13) CONTAIN_SLOT(14) CONTAIN_SLOT(15)
	CONTAIN_SLOT(16) CONTAIN_SLOT(17) CONTAIN_SLOT(18) CONTAIN_SLOT(19)
	CONTAIN_SLOT(20) CONTAIN_SLOT(21) CONTAIN_SLOT(22) CONTAIN_SLOT(23)
	CONTAIN_SLOT(24) CONTAIN_SLOT(25) CONTAIN_SLOT(26) CONTAIN_SLOT(27)
	CONTAIN_SLOT(28) CONTAIN_SLOT(29) CONTAIN_SLOT(30)
#undef CONTAIN_SLOT
	virtual ContainedObjectSource *getContainedObjectSource(); // slot 0x7C
#define CONTAIN_SLOT(n) virtual void slot##n();
	CONTAIN_SLOT(32) CONTAIN_SLOT(33) CONTAIN_SLOT(34) CONTAIN_SLOT(35)
	CONTAIN_SLOT(36) CONTAIN_SLOT(37)
#undef CONTAIN_SLOT
	virtual bool isValidContainerFor(const Object *obj, bool checkCapacity, bool flag); // slot 0x98
	virtual void addToContain(Object *obj); // slot 0x9C
#define CONTAIN_SLOT(n) virtual void slot##n();
	CONTAIN_SLOT(40) CONTAIN_SLOT(41) CONTAIN_SLOT(42) CONTAIN_SLOT(43)
	CONTAIN_SLOT(44) CONTAIN_SLOT(45) CONTAIN_SLOT(46) CONTAIN_SLOT(47)
	CONTAIN_SLOT(48) CONTAIN_SLOT(49) CONTAIN_SLOT(50) CONTAIN_SLOT(51)
	CONTAIN_SLOT(52) CONTAIN_SLOT(53) CONTAIN_SLOT(54) CONTAIN_SLOT(55)
	CONTAIN_SLOT(56) CONTAIN_SLOT(57) CONTAIN_SLOT(58) CONTAIN_SLOT(59)
	CONTAIN_SLOT(60) CONTAIN_SLOT(61) CONTAIN_SLOT(62) CONTAIN_SLOT(63)
	CONTAIN_SLOT(64) CONTAIN_SLOT(65) CONTAIN_SLOT(66) CONTAIN_SLOT(67)
	CONTAIN_SLOT(68) CONTAIN_SLOT(69) CONTAIN_SLOT(70) CONTAIN_SLOT(71)
	CONTAIN_SLOT(72) CONTAIN_SLOT(73) CONTAIN_SLOT(74) CONTAIN_SLOT(75)
	CONTAIN_SLOT(76) CONTAIN_SLOT(77) CONTAIN_SLOT(78) CONTAIN_SLOT(79)
	CONTAIN_SLOT(80)
#undef CONTAIN_SLOT
	virtual int getPlayerWhoEntered(); // slot 0x144
};

class ThingTemplate
{
public:
	__forceinline bool isKindOf(int t) const { return (m_kindOf[t >> 3] & (1 << (t & 7))) != 0; }

private:
	unsigned char m_pad[0x108];
	unsigned char m_kindOf[0x20];
};

class AICommandInterface
{
public:
	void rva0026C347(Object *obj, CommandSourceType cmdSource);
};

class AIUpdateInterface
{
public:
	unsigned char m_pad[0x20];
	AICommandInterface m_command;
};

class Player
{
public:
	int getPlayerMask() const { return 1 << m_playerIndex; }

private:
	unsigned char m_pad[0x54];
	int m_playerIndex;
};

enum ObjectStatusTypes { OBJECT_STATUS_NONE = 0 };
enum ObjectID { INVALID_ID = 0 };

class Object
{
public:
	virtual ~Object();
	const ThingTemplate *getTemplate() const { return m_template; }
	__forceinline bool isKindOf(int t) const { return getTemplate()->isKindOf(t); }
	ContainModuleInterface *getContain() const { return m_contain; }
	AIUpdateInterface *getAIUpdateInterface() const { return m_ai; }
	Player *getControllingPlayer() const;
	bool testStatus(ObjectStatusTypes bit) const;

private:
	const ThingTemplate *m_template;
	unsigned char m_pad08[0x74 - 0x08];
	ObjectID m_id;
	unsigned char m_pad78[0x250 - 0x78];
	ContainModuleInterface *m_contain;
	unsigned char m_pad254[4];
	AIUpdateInterface *m_ai;
	unsigned char m_pad25C[0x274 - 0x25C];
	Object *m_containedBy;

public:
	ObjectID getID() const { return m_id; }
	Object *getContainedBy() const { return m_containedBy; }
};

template<class OBJCLASS>
class DLINK_ITERATOR
{
public:
	void advance();
	bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }

private:
	OBJCLASS *m_cur;
	unsigned char m_targetAbiState[20];
};

class AIGroup
{
public:
	void groupEnter(Object *obj, CommandSourceType cmdSource);
};

class AI
{
public:
	AIGroup *createGroup();
};
extern AI *TheAI;

class Team
{
public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
	Player *getControllingPlayer() const;
	void getTeamAsAIGroup(AIGroup *group);
};

class ScriptEngine
{
public:
	Team *getTeamNamed(AsciiString name, bool);
	Object *getUnitNamed(const AsciiString &name);
};
extern ScriptEngine *TheScriptEngine;

class Rva00358752Opaque
{
public:
	Object *lookupUnitByValue(AsciiString name);
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};
extern GameLogic *TheGameLogic;

class ScriptActions
{
protected:
	ContainModuleInterface *rva003C538F(ObjectID *&it, const _STL::vector<ObjectID> &ids,
		Object *unit, bool flag);
	void rva003C6EFC(const AsciiString &teamName, const AsciiString &containerTeamName,
		bool instant);
	void putUnitInContain(Object *unit, ContainModuleInterface *contain, bool flag);
	void doTeamGarrisonSpecificBuilding(const AsciiString &teamName,
		const AsciiString &buildingName, bool instant);
	void doUnitGarrisonSpecificBuilding(const AsciiString &unitName,
		const AsciiString &buildingName, bool instant);
};

struct ContainTransfer
{
	ContainModuleInterface *dest;
	ContainedObjectSource *source;
};

// WB 0x01006F10 (unnamed), retail 0x003C4B97.
static void transferContainedObjects(ContainTransfer *transfer)
{
	_STL::list<const Object *> objects;
	transfer->source->getObjects(objects);
	for (_STL::list<const Object *>::iterator it = objects.begin(); it != objects.end(); ++it) {
		transfer->source->removeObject(*it);
		transfer->dest->addToContain(const_cast<Object *>(*it));
	}
}

void ScriptActions::putUnitInContain(Object *unit, ContainModuleInterface *contain, bool flag)
{
	bool isValidForEntry = contain->isValidContainerFor(unit, true, flag);
	if (!isValidForEntry)
		return;
	contain->addToContain(unit);
	if (unit->isKindOf(0x6D)) {
		ContainedObjectSource *source = unit->getContain()->getContainedObjectSource();
		if (source) {
			ContainTransfer transfer;
			transfer.dest = contain;
			transfer.source = source;
			transferContainedObjects(&transfer);
		}
	}
}

void ScriptActions::doTeamGarrisonSpecificBuilding(const AsciiString &teamName,
	const AsciiString &buildingName, bool instant)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(teamName, false);
	if (!theTeam)
		return;
	Object *theBuilding = ((Rva00358752Opaque *)TheScriptEngine)->lookupUnitByValue(buildingName);
	if (!theBuilding)
		return;
	ContainModuleInterface *contain = theBuilding->getContain();
	if (!contain)
		return;
	if (instant) {
		for (DLINK_ITERATOR<Object> iter = theTeam->iterate_TeamMemberList(); !iter.done();
			iter.advance()) {
			if (!iter.cur()->testStatus((ObjectStatusTypes)0x26))
				putUnitInContain(iter.cur(), contain, false);
		}
	} else {
		int player = contain->getPlayerWhoEntered();
		if (!(theBuilding->isKindOf(7) && player == 0) &&
			player != theTeam->getControllingPlayer()->getPlayerMask())
			return;
		AIGroup *theGroup = TheAI->createGroup();
		if (!theGroup)
			return;
		theTeam->getTeamAsAIGroup(theGroup);
		theGroup->groupEnter(theBuilding, CMD_FROM_SCRIPT);
	}
}

void ScriptActions::doUnitGarrisonSpecificBuilding(const AsciiString &unitName,
	const AsciiString &buildingName, bool instant)
{
	Object *theUnit = TheScriptEngine->getUnitNamed(unitName);
	if (!theUnit)
		return;
	AIUpdateInterface *ai = theUnit->getAIUpdateInterface();
	if (!ai)
		return;
	Object *theBuilding = ((Rva00358752Opaque *)TheScriptEngine)->lookupUnitByValue(buildingName);
	if (!theBuilding)
		return;
	ContainModuleInterface *contain = theBuilding->getContain();
	if (!contain)
		return;
	int player = contain->getPlayerWhoEntered();
	if (!(theBuilding->isKindOf(0x76) && player == 0) &&
		player != theUnit->getControllingPlayer()->getPlayerMask())
		return;
	if (!contain->isValidContainerFor(theUnit, true, !instant))
		return;
	if (instant) {
		contain->addToContain(theUnit);
		if (theUnit->isKindOf(0x6D)) {
			ContainedObjectSource *source = theUnit->getContain()->getContainedObjectSource();
			if (source) {
				ContainTransfer transfer;
				transfer.dest = contain;
				transfer.source = source;
				transferContainedObjects(&transfer);
			}
		}
	} else {
		ai->m_command.rva0026C347(theBuilding, CMD_FROM_SCRIPT);
	}
}

ContainModuleInterface *ScriptActions::rva003C538F(ObjectID *&it, const _STL::vector<ObjectID> &ids,
	Object *unit, bool flag)
{
	int count = ids.size();
	while (--count >= 0) {
		ObjectID *cur = it;
		Object *obj = TheGameLogic->findObjectByID(*cur);
		it = cur + 1;
		if (it == ids.end())
			it = (ObjectID *)ids.begin();
		if (!obj || obj->getID() == unit->getID())
			continue;
		ContainModuleInterface *contain = obj->getContain();
		if (!contain)
			continue;
		if (contain->isValidContainerFor(unit, true, flag))
			return contain;
	}
	return 0;
}

void ScriptActions::rva003C6EFC(const AsciiString &teamName, const AsciiString &containerTeamName,
	bool instant)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(teamName, false);
	if (!theTeam)
		return;
	Team *containerTeam = TheScriptEngine->getTeamNamed(containerTeamName, false);
	if (!containerTeam)
		return;
	_STL::vector<ObjectID> ids;
	{
		for (DLINK_ITERATOR<Object> iter = containerTeam->iterate_TeamMemberList(); !iter.done();
			iter.advance())
			ids.push_back(iter.cur()->getID());
	}
	ObjectID *it = ids.begin();
	for (DLINK_ITERATOR<Object> iter = theTeam->iterate_TeamMemberList(); !iter.done();
		iter.advance()) {
		Object *obj = iter.cur();
		if (obj->testStatus((ObjectStatusTypes)0x26))
			continue;
		if (obj->getContainedBy())
			continue;
		ContainModuleInterface *contain = rva003C538F(it, ids, obj, !instant);
		if (contain)
			putUnitInContain(obj, contain, !instant);
	}
}
