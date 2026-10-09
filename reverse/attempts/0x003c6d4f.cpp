// ?Rva003C6D4FDo@@YGXPAVParameter@@00@Z
// partial score=0.99 date=2026-10-10
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHs /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
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
//   0x003C4EC3 (479B) ScriptActions::doCreateObject
//   0x003C50A2 (658B) ScriptActions::createUnitOnTeamAt
//   0x003C4A70 (189B) ScriptActions::doDisplayNotificationBox
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
//
// doCreateObject. Target facts: the unnamed-unit test compares against
// AsciiString::TheEmptyString (0x009E0878); the existing object comes from
// the by-value lookup 0x00358752, and its liveness test reads bit 0 of
// Object +0x438 (WB +0x445); the team lookup passes true; a missing team
// posts the two debug messages and returns, with no team creation; the
// template lookup is 0x002D06CA on TheThingFactory and newObject gets a
// zeroed 16-byte mask and false; the name lands at Object +0x88 through
// StringBase::set; the renamed path calls 0x00357960 and the fresh one
// addObjectToCache with an empty name; the body ends with the 5-byte
// Object forwarder 0x0028FC18 where BFME1 has its blast-crater block.
// Donor facts: BFME1 doCreateObject gives the statement order, the messages
// and transferObjectName for 0x00357960.
//
// createUnitOnTeamAt shares that skeleton (without the unnamed-unit test
// ahead of the lookup) and adds a fallback BFME1 lacks: a name that is not a
// waypoint (TerrainLogic slot 0x88) is tried as a template, and the unit goes
// to the object of that template closest (within 1e6, ThePartitionManager
// 0x00625360 with the template filter, vftable 0x00C1FDEC) to the team's
// position 0x0039E5B9. Neither found posts the waypoint warning. The
// destination is the waypoint's +0x0C location or the object's +0x38
// position; WB, like retail, leaves it unset when neither holds, and retail
// keeps that unset local in the dead waypoint argument slot.
//
// doDisplayNotificationBox (BFME2 only; BFME1's ScriptActions has no such
// action). Target facts: an unknown type name returns at once; the type's
// record comes back by value from 0x00221ABB and is destroyed by 0x002217B1;
// a non-empty object-type name (the out-of-line StringBase test 0x00001E2F)
// that names a template sets the record's image to the template's button
// image; the label is fetched through TheGameText slot 0x38 into the dead
// name argument slot; the record, the text and seconds * 1000 go to the
// 0x005CC208 forwarder on TheInGameUI's +0x10 notification box (0x000CF155).
// WB supplies the names: FindInGameNotificationType and
// InGameNotificationBox::Open.

#include "ascii_string.h"
#include "unicode_string.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../Common/PartitionRangeQueryCallView.h"
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

class Image;

class ThingTemplate
{
public:
	__forceinline bool isKindOf(int t) const { return (m_kindOf[t >> 3] & (1 << (t & 7))) != 0; }
	const Image *getButtonImage(); // resolves the image name on first use

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
enum NameKeyType { NAMEKEY_INVALID = 0 };
enum SpecialPowerType { SPECIAL_INVALID = 0 };
class Module;

class Thing
{
public:
	virtual ~Thing();
	void setOrientation(float angle);
	void setPosition(const Coord3D *pos);
};

class SpecialPowerModuleInterface
{
public:
	virtual void s00();
	virtual bool isReady();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void doSpecialPowerAtObject(Object *target, int value);
};

class Object : public Thing
{
public:
	virtual ~Object();
	const ThingTemplate *getTemplate() const { return m_template; }
	__forceinline bool isKindOf(int t) const { return getTemplate()->isKindOf(t); }
	ContainModuleInterface *getContain() const { return m_contain; }
	AIUpdateInterface *getAIUpdateInterface() const { return m_ai; }
	Player *getControllingPlayer() const;
	bool testStatus(ObjectStatusTypes bit) const;
	void rva0028FC18();
	SpecialPowerModuleInterface *findSpecialPowerModuleInterface(SpecialPowerType type) const;	// 0x00290E22
	Module *findModule(NameKeyType key) const;	// 0x0028B6D6

private:
	const ThingTemplate *m_template;
	unsigned char m_pad08[0x38 - 0x08];
	Coord3D m_pos;
	unsigned char m_pad44[0x74 - 0x44];
	ObjectID m_id;
	unsigned char m_pad78[0x88 - 0x78];
	AsciiString m_name;
	unsigned char m_pad8C[0x250 - 0x8C];
	ContainModuleInterface *m_contain;
	unsigned char m_pad254[4];
	AIUpdateInterface *m_ai;
	unsigned char m_pad25C[0x274 - 0x25C];
	Object *m_containedBy;
	unsigned char m_pad278[0x438 - 0x278];
	unsigned char m_privateStatus;

public:
	ObjectID getID() const { return m_id; }
	const Coord3D *getPosition() const { return &m_pos; }
	Object *getContainedBy() const { return m_containedBy; }
	void setName(const AsciiString &name) { m_name = name; }
	bool isEffectivelyDead() const { return (m_privateStatus & 1) != 0; }
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
	void rva0039E5B9(Coord3D *pos);
	Coord3D rva0039DA2A() const;	// 0x0039DA2A: the team's position
};

class Parameter
{
public:
	unsigned char m_beforeInt[8];
	int m_int;
	float m_real;
	AsciiString m_string;	// +0x10
};

class Rva002046C0Owner
{
public:
	AsciiString resolveName(const AsciiString &s);
};

class ScriptEngine
{
public:
	Team *getTeamNamed(AsciiString name, bool);
	Object *getUnitNamed(const AsciiString &name);
	Object *getUnitNamed(Parameter *parameter);
	void AppendDebugMessage(const AsciiString &msg, bool flag);
	bool didUnitExist(const AsciiString &name);
	void rva00357960(const AsciiString &name, Object *obj); // ZH transferObjectName
	void addObjectToCache(Object *obj, const AsciiString &name);
};
extern ScriptEngine *TheScriptEngine;

struct CreateMask
{
	unsigned char m_data[0x10];
};

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
	Object *newObject(const ThingTemplate *tmpl, Team *team, const CreateMask *mask, bool flag);
};
extern ThingFactory *TheThingFactory;

class Waypoint
{
public:
	const Coord3D *getLocation() const { return &m_location; }

private:
	unsigned char m_pad[0x0C];
	Coord3D m_location;
};

class TerrainLogic
{
public:
#define TERRAIN_SLOT(n) virtual void slot##n();
	TERRAIN_SLOT(0) TERRAIN_SLOT(1) TERRAIN_SLOT(2) TERRAIN_SLOT(3) TERRAIN_SLOT(4)
	TERRAIN_SLOT(5) TERRAIN_SLOT(6) TERRAIN_SLOT(7) TERRAIN_SLOT(8) TERRAIN_SLOT(9)
	TERRAIN_SLOT(10) TERRAIN_SLOT(11) TERRAIN_SLOT(12) TERRAIN_SLOT(13) TERRAIN_SLOT(14)
	TERRAIN_SLOT(15) TERRAIN_SLOT(16) TERRAIN_SLOT(17) TERRAIN_SLOT(18) TERRAIN_SLOT(19)
	TERRAIN_SLOT(20) TERRAIN_SLOT(21) TERRAIN_SLOT(22) TERRAIN_SLOT(23) TERRAIN_SLOT(24)
	TERRAIN_SLOT(25) TERRAIN_SLOT(26) TERRAIN_SLOT(27) TERRAIN_SLOT(28) TERRAIN_SLOT(29)
	TERRAIN_SLOT(30) TERRAIN_SLOT(31) TERRAIN_SLOT(32) TERRAIN_SLOT(33)
#undef TERRAIN_SLOT
	virtual Waypoint *getWaypointByName(const AsciiString &name); // slot 0x88
};
extern TerrainLogic *TheTerrainLogic;

// The partition filter chain: a vptr, the +0x04 link to the next filter, then
// each filter's members (see ScriptActions_closestOfObjectTypes.cpp).
class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual bool allow(Object *obj) = 0;
	Rva000421C8 *link(Rva000421C8 *next);	// 0x00625790
	Rva000421C8 *m_next;
};

// vftable 0x00C1FDEC, allow 0x00261750 (Zero Hour's PartitionFilterThing).
class Rva00261750Filter : public Rva000421C8
{
public:
	Rva00261750Filter(const ThingTemplate *tmpl, bool match) : m_template(tmpl), m_match(match) {}
	virtual bool allow(Object *obj);
	const ThingTemplate *m_template;
	bool m_match;
};

extern PartitionManager *ThePartitionManager;

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

// An InGameNotificationType's notification record, 0x14 bytes: the text at
// +0x00 and the image at +0x08 (copy constructor 0x002217EA, destructor
// 0x002217B1). The image setter 0x0010670B is folded with
// GameMessage::friend_setPrev, so it keeps an address-derived spelling.
class Rva002217EA
{
public:
	~Rva002217EA();
	void rva0010670B(const Image *image);

private:
	unsigned char m_data[0x14];
};

class InGameNotificationType
{
public:
	Rva002217EA rva00221ABB() const; // WB 0x00B8D300, unnamed: the type's record
};
InGameNotificationType *FindInGameNotificationType(const AsciiString &name);

class GameTextInterface
{
public:
#define GAMETEXT_SLOT(n) virtual void slot##n();
	GAMETEXT_SLOT(0) GAMETEXT_SLOT(1) GAMETEXT_SLOT(2) GAMETEXT_SLOT(3) GAMETEXT_SLOT(4)
	GAMETEXT_SLOT(5) GAMETEXT_SLOT(6) GAMETEXT_SLOT(7) GAMETEXT_SLOT(8) GAMETEXT_SLOT(9)
	GAMETEXT_SLOT(10) GAMETEXT_SLOT(11) GAMETEXT_SLOT(12) GAMETEXT_SLOT(13)
#undef GAMETEXT_SLOT
	virtual UnicodeString fetch(const AsciiString &label, bool *exists = 0); // slot 0x38
};
extern GameTextInterface *TheGameText;

// WB's InGameNotificationBox::Open (0x01092540) asserts the timeout and hands
// all three arguments to its own vtable slot 2; retail's copy is the tail jump
// 0x005CC208, folded with the vcall thunk ??_9@$B7AE, so it keeps an
// address-derived spelling.
class InGameNotificationBox
{
public:
	void rva005CC208(const UnicodeString &text, const Rva002217EA &data, int timeoutMS);
};

class Rva005CB260;

class InGameUI
{
public:
	Rva005CB260 *rva000CF155(); // the +0x10 notification box, null-checked
	void addNamedTimer(const AsciiString &timerName, const UnicodeString &text, bool isCountdown);
};
extern InGameUI *TheInGameUI;

class ScriptActions
{
protected:
	void doDisplayNotificationBox(const AsciiString &name, const AsciiString &textLabel,
		int seconds, const AsciiString &objectTypeName);
	ContainModuleInterface *rva003C538F(ObjectID *&it, const _STL::vector<ObjectID> &ids,
		Object *unit, bool flag);
	void rva003C6EFC(const AsciiString &teamName, const AsciiString &containerTeamName,
		bool instant);
	void putUnitInContain(Object *unit, ContainModuleInterface *contain, bool flag);
	void doTeamGarrisonSpecificBuilding(const AsciiString &teamName,
		const AsciiString &buildingName, bool instant);
	void doUnitGarrisonSpecificBuilding(const AsciiString &unitName,
		const AsciiString &buildingName, bool instant);
	void doCreateObject(const AsciiString &objectName, const AsciiString &thingName,
		const AsciiString &teamName, Coord3D *pos, float angle);
	void createUnitOnTeamAt(const AsciiString &unitName, const AsciiString &objType,
		const AsciiString &teamName, const AsciiString &waypoint);
};

struct ContainTransfer
{
	ContainModuleInterface *dest;
	ContainedObjectSource *source;
};

// WB 0x01006F10 (unnamed), retail 0x003C4B97.
void ScriptActions::doDisplayNotificationBox(const AsciiString &name, const AsciiString &textLabel,
	int seconds, const AsciiString &objectTypeName)
{
	InGameNotificationType *type = FindInGameNotificationType(name);
	if (!type)
		return;
	Rva002217EA data = type->rva00221ABB();
	if (!((const StringBase<char> *)&objectTypeName)->isEmpty()) {
		const ThingTemplate *thingTemplate = TheThingFactory->findTemplate(objectTypeName);
		if (thingTemplate)
			data.rva0010670B(const_cast<ThingTemplate *>(thingTemplate)->getButtonImage());
	}
	UnicodeString text = TheGameText->fetch(textLabel);
	((InGameNotificationBox *)TheInGameUI->rva000CF155())->rva005CC208(text, data, seconds * 1000);
}

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

void ScriptActions::doCreateObject(const AsciiString &objectName, const AsciiString &thingName,
	const AsciiString &teamName, Coord3D *pos, float angle)
{
	Object *pOldObj = 0;
	if (objectName != AsciiString::TheEmptyString) {
		pOldObj = ((Rva00358752Opaque *)TheScriptEngine)->lookupUnitByValue(objectName);
		if (pOldObj && !pOldObj->isEffectivelyDead()) {
			AsciiString str = "WARNING - Object with name ";
			str.concat(objectName);
			str.concat(" already exists. Failed Create.");
			TheScriptEngine->AppendDebugMessage(str, false);
			return;
		}
	}
	Team *theTeam = TheScriptEngine->getTeamNamed(teamName, true);
	if (!theTeam) {
		TheScriptEngine->AppendDebugMessage("***WARNING - Team not found:***", false);
		TheScriptEngine->AppendDebugMessage(teamName, true);
		return;
	}
	const ThingTemplate *thingTemplate = TheThingFactory->findTemplate(thingName);
	if (thingTemplate) {
		CreateMask mask;
		memset(&mask, 0, sizeof(mask));
		Object *obj = TheThingFactory->newObject(thingTemplate, theTeam, &mask, false);
		if (obj) {
			if (objectName != AsciiString::TheEmptyString) {
				obj->setName(objectName);
				if (pOldObj || TheScriptEngine->didUnitExist(objectName))
					TheScriptEngine->rva00357960(objectName, obj);
				else
					TheScriptEngine->addObjectToCache(obj, "");
			}
			obj->setOrientation(angle);
			obj->setPosition(pos);
			obj->rva0028FC18();
		}
	}
}

void ScriptActions::createUnitOnTeamAt(const AsciiString &unitName, const AsciiString &objType,
	const AsciiString &teamName, const AsciiString &waypoint)
{
	Object *pOldObj = ((Rva00358752Opaque *)TheScriptEngine)->lookupUnitByValue(unitName);
	if (pOldObj && !pOldObj->isEffectivelyDead()) {
		AsciiString str = "WARNING - Object with name ";
		str.concat(unitName);
		str.concat(" already exists. Failed Create.");
		TheScriptEngine->AppendDebugMessage(str, false);
		return;
	}
	Team *theTeam = TheScriptEngine->getTeamNamed(teamName, true);
	if (!theTeam) {
		TheScriptEngine->AppendDebugMessage("***WARNING - Team not found:***", false);
		TheScriptEngine->AppendDebugMessage(teamName, true);
		return;
	}
	Waypoint *way = TheTerrainLogic->getWaypointByName(waypoint);
	Object *foundObject = 0;
	if (!way) {
		const ThingTemplate *tmpl = TheThingFactory->findTemplate(waypoint);
		if (tmpl) {
			Coord3D pos;
			theTeam->rva0039E5B9(&pos);
			foundObject = ThePartitionManager->getClosestObject(&pos, 100000 * 10.0f, 0,
				&Rva00261750Filter(tmpl, true));
		}
	}
	if (!way && !foundObject) {
		TheScriptEngine->AppendDebugMessage("***WARNING - Waypoint/Object type not found:***", false);
		TheScriptEngine->AppendDebugMessage(waypoint, true);
		return;
	}
	const ThingTemplate *thingTemplate = TheThingFactory->findTemplate(objType);
	if (thingTemplate) {
		CreateMask mask;
		memset(&mask, 0, sizeof(mask));
		Object *obj = TheThingFactory->newObject(thingTemplate, theTeam, &mask, false);
		if (obj) {
			if (unitName != AsciiString::TheEmptyString) {
				obj->setName(unitName);
				if (pOldObj || TheScriptEngine->didUnitExist(unitName))
					TheScriptEngine->rva00357960(unitName, obj);
				else
					TheScriptEngine->addObjectToCache(obj, "");
			}
			const Coord3D *destination;
			if (way)
				destination = way->getLocation();
			else if (foundObject)
				destination = foundObject->getPosition();
			obj->setPosition(destination);
			obj->rva0028FC18();
		}
	}
}

// ?Rva003C5405Do@@YGXVAsciiString@@ABV1@@Z @0x003C5405 152B evidence: timerName via resolveName 0x002046C0 plus '/' 0x2f plus concat; label via TheGameText slot 0x38; named timer via addNamedTimer 0x002A5A50; caller 0x003CC5FF; prev 0x003C538F in this file
void __stdcall Rva003C5405Do(AsciiString timerName, const AsciiString &label)
{
	AsciiString tmp = ((Rva002046C0Owner *)TheScriptEngine)->resolveName(timerName);
	tmp += '/';
	tmp += timerName;
	TheInGameUI->addNamedTimer(tmp, TheGameText->fetch(label), false);
}

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

// A KindOfMaskType as the mask filters copy it (0x0004543D).
class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other) throw();
private:
	unsigned char m_bytes[28];
};

struct Rva00045411BitSet
{
	Rva00045411BitSet(int unused, int bit);	// 0x00045411
	unsigned int m_bits[7];
};
extern unsigned char g_00DFEFA4StoragePrototype[28];

// vftable 0x00BC2908, allow 0x002610DE: accept what has every kind of the
// first mask and none of the second (ZH's PartitionFilterAcceptByKindOf).
class Rva0004584D : public Rva000421C8
{
public:
	Rva0004584D(const BfmeFixedStorage0004543D &a, const BfmeFixedStorage0004543D &b);
	virtual bool allow(Object *obj);
	BfmeFixedStorage0004543D m_08;
	BfmeFixedStorage0004543D m_24;
};

// SiegeDockingBehavior: the +0x20 interface's slot 3 answers whether the
// object with the given ID may dock (retail 0x003C6A0E).
class SiegeDockInterface
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual bool canDock(ObjectID id);
};

class SiegeDockingModule
{
public:
	unsigned char m_pad[0x20];
	SiegeDockInterface m_dock;
};

// ?Rva003C6A0EDo@@YGXPAVParameter@@00@Z @0x003C6A0E 365B evidence: unit by Parameter (0x003588E7) of kind 93 with a ready special power 0x2d; waypoint (TerrainLogic slot 0x88) location and the radius parameter; objects in range passing the kind-60 filter; first with a SiegeDockingBehavior whose dock interface accepts the unit gets the special power at it (slot 11, 2); caller 0x003CE4A0
void __stdcall Rva003C6A0EDo(Parameter *unitParm, Parameter *wayParm, Parameter *radiusParm)
{
	Object *unit = TheScriptEngine->getUnitNamed(unitParm);
	if (!unit || !unit->isKindOf(0x5D))
		return;
	SpecialPowerModuleInterface *sp = unit->findSpecialPowerModuleInterface((SpecialPowerType)0x2D);
	if (!sp || !sp->isReady())
		return;
	Waypoint *way = TheTerrainLogic->getWaypointByName(wayParm->m_string);
	if (!way)
		return;
	Coord3D pos;
	pos.x = way->getLocation()->x;
	pos.y = way->getLocation()->y;
	pos.z = way->getLocation()->z;
	float radius = radiusParm->m_real;
	BfmeWideResult iter = ThePartitionManager->iterateObjectsInRange(&pos, radius, 0,
		&Rva0004584D(*(BfmeFixedStorage0004543D *)&Rva00045411BitSet(0, 0x3C),
			*(BfmeFixedStorage0004543D *)g_00DFEFA4StoragePrototype), 1);
	for (Object *obj = iter.next(); obj; obj = iter.next()) {
		static NameKeyType siegeKey = TheNameKeyGenerator->nameToKey("SiegeDockingBehavior");
		SiegeDockingModule *module = (SiegeDockingModule *)obj->findModule(siegeKey);
		if (module && module->m_dock.canDock(unit->getID())) {
			sp->doSpecialPowerAtObject(obj, 2);
			break;
		}
	}
}

// vftable 0x00BFAD10, allow 0x0026119D: not effectively dead.
class Rva0026119DFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};

// ?Rva003C6B7BDo@@YGXPAVParameter@@00@Z @0x003C6B7B 468B evidence: team by name (getTeamNamed 0x003584E9) and its first member; waypoint location and radius as 0x003C6A0E; query filter kind 60 linked to the not-dead filter 0x00BFAD10; each object with a SiegeDockingBehavior takes the team members, in turn, that are kind 93 with a ready special power 0x2d and not status 0x40, until one is refused by the dock interface; caller 0x003CE4D0
void __stdcall Rva003C6B7BDo(Parameter *teamParm, Parameter *wayParm, Parameter *radiusParm)
{
	Team *team = TheScriptEngine->getTeamNamed(teamParm->m_string, false);
	if (!team)
		return;
	DLINK_ITERATOR<Object> diter = team->iterate_TeamMemberList();
	if (diter.done())
		return;
	Waypoint *way = TheTerrainLogic->getWaypointByName(wayParm->m_string);
	if (!way)
		return;
	Coord3D pos;
	pos.x = way->getLocation()->x;
	pos.y = way->getLocation()->y;
	pos.z = way->getLocation()->z;
	float radius = radiusParm->m_real;
	BfmeWideResult iter = ThePartitionManager->iterateObjectsInRange(&pos, radius, 0,
		Rva0004584D(*(BfmeFixedStorage0004543D *)&Rva00045411BitSet(0, 0x3C),
			*(BfmeFixedStorage0004543D *)g_00DFEFA4StoragePrototype).link(&Rva0026119DFilter()), 1);
	for (Object *obj = iter.next(); obj; obj = iter.next()) {
		static NameKeyType siegeKey = TheNameKeyGenerator->nameToKey("SiegeDockingBehavior");
		SiegeDockingModule *module = (SiegeDockingModule *)obj->findModule(siegeKey);
		if (!module)
			continue;
		Object *member = diter.cur();
		if (!diter.done()) {
			do {
				if (diter.cur()->isKindOf(0x5D)) {
					SpecialPowerModuleInterface *sp = diter.cur()->findSpecialPowerModuleInterface((SpecialPowerType)0x2D);
					if (sp && sp->isReady() && !diter.cur()->testStatus((ObjectStatusTypes)0x40)) {
						if (!module->m_dock.canDock(diter.cur()->getID()))
							break;
						sp->doSpecialPowerAtObject(obj, 2);
					}
				}
				diter.advance();
			} while (!diter.done());
		}
	}
}

// ?Rva003C6D4FDo@@YGXPAVParameter@@00@Z @0x003C6D4F 429B evidence: as 0x003C6B7B, but the objects come from the area around a second team's position (0x0039DA2A) and the query has only the kind-60 filter; caller 0x003CE500
void __stdcall Rva003C6D4FDo(Parameter *teamParm, Parameter *posTeamParm, Parameter *radiusParm)
{
	Team *team = TheScriptEngine->getTeamNamed(teamParm->m_string, false);
	if (!team)
		return;
	DLINK_ITERATOR<Object> diter = team->iterate_TeamMemberList();
	if (diter.done())
		return;
	Team *posTeam = TheScriptEngine->getTeamNamed(posTeamParm->m_string, false);
	if (!posTeam)
		return;
	Coord3D pos = posTeam->rva0039DA2A();
	float radius = radiusParm->m_real;
	BfmeWideResult iter = ThePartitionManager->iterateObjectsInRange(&pos, radius, 0,
		&Rva0004584D(*(BfmeFixedStorage0004543D *)&Rva00045411BitSet(0, 0x3C),
			*(BfmeFixedStorage0004543D *)g_00DFEFA4StoragePrototype), 1);
	for (Object *obj = iter.next(); obj; obj = iter.next()) {
		static NameKeyType siegeKey = TheNameKeyGenerator->nameToKey("SiegeDockingBehavior");
		SiegeDockingModule *module = (SiegeDockingModule *)obj->findModule(siegeKey);
		if (!module)
			continue;
		while (diter.cur()) {
			if (diter.cur()->isKindOf(0x5D)) {
				SpecialPowerModuleInterface *sp = diter.cur()->findSpecialPowerModuleInterface((SpecialPowerType)0x2D);
				if (sp && sp->isReady() && !diter.cur()->testStatus((ObjectStatusTypes)0x40)) {
					if (!module->m_dock.canDock(diter.cur()->getID()))
						break;
					sp->doSpecialPowerAtObject(obj, 2);
				}
			}
			diter.advance();
		}
	}
}
