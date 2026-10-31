// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX
//
// ScriptConditions::evaluateTypeSighted, retail 0x003EA3AB, 443 bytes (caller
// 0x003EAEDD in the condition dispatcher 0x003EA9AF). Zero Hour's
// evaluateTypeSighted made BFME2: for each player of the parameter's player
// mask (TheScriptEngine 0x00357B82, ThePlayerList::getEachPlayerFromMask),
// whether any object that player owns, alive, of the parsed ObjectTypes
// (0x00566E6C into an ObjectTypesTemp) lies within the named unit's vision
// range through BFME2's partition filter chain (the view
// AIStructureCreepTactic.cpp documents).
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

// vftable 0x00BFAD28, allow 0x0026137E, slot 2 0x00261368: +0x08 a
// player, +0x0C whether a hit allows.
class Rva0026137EFilter : public Rva000421C8
{
public:
	Rva0026137EFilter(Player *player, bool match) : m_player(player), m_match(match) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	Player *m_player;
	bool m_match;
};

// vftable 0x00BFAD10, allow 0x0026119D: not effectively dead.
class Rva0026119DFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};

// vftable 0x00BF8FE4, allow 0x0026109D; the out-of-line ctor 0x00261058.
class Rva00261058 : public Rva000421C8
{
public:
	Rva00261058(Object *obj, bool flag);	// 0x00261058
	virtual bool allow(Object *obj);
	Player *m_player;
	bool m_flag;
};

// vftable 0x00C0719C, allow 0x00261513: +0x08 an object, +0x0C a flag,
// +0x10 a float.
class Rva00261513Filter : public Rva000421C8
{
public:
	Rva00261513Filter(const Object *obj, bool flag, float value)
		: m_obj(obj), m_flag(flag), m_value(value) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
	bool m_flag;
	float m_value;
};

// vftable 0x00BF91BC, allow 0x002611BF.
class Rva002611BFFilter : public Rva000421C8
{
public:
	Rva002611BFFilter(const Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
};

#include "../../../../Libraries/Include/Lib/Coord3D.h"

struct BfmeWideResult
{
	Object *next() throw();	// 0x00045623
	~BfmeWideResult();	// 0x0004AA28
	void *m_value;
};

class PartitionManager
{
public:
	BfmeWideResult iterateObjectsInRange(const Coord3D *pos, float radius, int distCalc,
		Rva000421C8 *filters, int order);	// 0x00625610
};
extern PartitionManager *ThePartitionManager;

enum KindOfType
{
	KINDOF_90 = 90
};
class ThingTemplate
{
public:
	bool isKindOfInert() const { return (m_kindOf[0x113 - 0x108] & 0x02) != 0; }
	bool isEquivalentTo(const ThingTemplate *other) const;
	bool isKindOf(KindOfType t) const
	{
		return (m_kindOf[t >> 3] >> (t & 7)) & 1;
	}
	// LINK: same-body helper under a TU-unique name (identical inlined bytes); the isKindOf
	// copy loses to the kept copy. No flags touched.
	bool bfme_isKindOf_puc(KindOfType t) const
	{
		return (m_kindOf[t >> 3] >> (t & 7)) & 1;
	}
	const AsciiString &getName() const { return m_name; }
	char m_pad00[0x64];
	AsciiString m_name; // +0x64
	char m_pad68[0xA0];
	unsigned char m_kindOf[16]; // +0x108 KindOf bits; 0x02 of byte 11 is the inert flag
};

enum ObjectStatusTypes { OBJECT_STATUS_NONE = 0 };
enum SpecialPowerType { SPECIAL_INVALID = 0 };
enum NameKeyType
{
    NAMEKEY_INVALID = 0
};
enum CellShroudStatus { CELLSHROUD_CLEAR, CELLSHROUD_FOGGED, CELLSHROUD_SHROUDED, CELLSHROUD_COUNT };
class Rva00261C89;
class Parameter;
class Module;
class ContainModuleInterface;
class ScriptConditions;
class PolygonTrigger;
class BodyModuleInterface;
class AIUpdateInterface;
class ExperienceTracker;
class Object
{
private:
	friend bool __stdcall Rva003E4B83Get(Parameter *);
public:
	friend class ScriptConditions;
	const Coord3D *getPosition() const { return &m_pos; }
	Rva00261C89 *getField04() const { return (Rva00261C89 *)m_template; }
	bool testStatus(ObjectStatusTypes status) const;
	float getVisionRange() const;
	bool hasSpecialPower(SpecialPowerType type) const;
	Player *getControllingPlayer() const;
protected:
	Module *findModule(NameKeyType key) const;
public:
	// Keep the native +0x250 load inline; omit the competing legacy getter.
	__declspec(dllimport) __forceinline ContainModuleInterface *getContain() const { return m_contain; }
	unsigned int getID() const { return m_id; }
	const AsciiString *rva00290E67() const;
	bool didEnter(PolygonTrigger *trigger); // 0x0028D718
	bool didExit(PolygonTrigger *trigger); // 0x0028D757
	BodyModuleInterface *getBodyModule() const { return m_body; }
	bool rva002943B2(const Player *player);
	CellShroudStatus getShroudStatusForPlayer(int playerIndex) const;
	const ThingTemplate *getTemplate() const { return m_template; }
	void *getContainedBy() const { return m_containedBy; }
	AIUpdateInterface *getAIUpdateInterface() const { return m_ai; }
	char m_pad00[0x4];
	const ThingTemplate *m_template; // +0x04
	char m_pad08[0x30];
	Coord3D m_pos; // +0x38
	char m_pad44[0x30];
	unsigned int m_id; // +0x74
	char m_pad78[0x150];
	unsigned char m_disabledMask[4]; // +0x1C8
	char m_pad1CC[0x84];
	ContainModuleInterface *m_contain; // +0x250
private:
	BodyModuleInterface *m_body; // +0x254
	AIUpdateInterface *m_ai; // +0x258 (retail-proven by the kept ScriptActions_doTeamFaceWaypoint row)
	char m_pad25C[0x8];
public:
	ExperienceTracker *m_experienceTracker; // +0x264
	char m_pad268[0xC];
private:
	void *m_containedBy; // +0x274
	char m_pad278[0x1D4];
public:
	int m_44c; // +0x44C
};

class ObjectTypes
{
public:
	virtual ~ObjectTypes();
	bool isInSet(const AsciiString &name) const;	// 0x00376A62
};

class ObjectTypesTemp
{
public:
	ObjectTypesTemp();	// 0x003BA7FF
	~ObjectTypesTemp() { ::delete m_types; }
	ObjectTypes *m_types;
};

class Parameter
{
public:
	enum { LESS_THAN = 0, LESS_EQUAL, EQUAL, GREATER_EQUAL, GREATER, NOT_EQUAL };
private:
	friend class ScriptConditions; // Native conditions read the +0x08 word inline.
public:
	float getReal() const { return m_real; }
	const AsciiString &getString() const { return m_string; }
	void setCachedFrame(int value) { m_cachedFrame = value; }
	__declspec(dllimport) __forceinline int getInt() const { return m_int; }
	int bfme_getInt_58502() const { return m_int; }
	int bfme_int_ena() const { return m_int; }
	int bfme_int_exa() const { return m_int; }
	int bfme_int_hos() const { return m_int; }
	// LINK: same-body helper under a TU-unique name (identical inlined bytes); the getInt copy loses to the first-in-order copy. No flags touched.
	int bfme_getInt_f996b() const { return m_int; }
	char m_pad00[0x8];
	int m_int; // +0x08
	float m_real; // +0x0C
	AsciiString m_string; // +0x10
	unsigned char m_afterString[8]; // +0x14
	unsigned int m_objectId; // +0x1C
	int m_cachedFrame; // +0x20
};

void Script_objectTypesFromParam(Parameter *typeParm, ObjectTypes *types);	// 0x00566E6C

class PlayerList
{
public:
	Player *getPlayerFromMask(int mask);
	Player *getEachPlayerFromMask(int &mask);
	int rva002A7C0B(bool flag);
	Player *getNeutralPlayer() const { return m_neutralPlayer; }
	char m_pad00[0x18];
private:
	Player *m_neutralPlayer; // +0x18
};
extern PlayerList *ThePlayerList;

#include "../../../Include/GameLogic/ScriptEngine.h"
extern ScriptEngine *TheScriptEngine;

#include "../../../Include/GameLogic/ScriptConditions.h"

bool ScriptConditions::evaluateTypeSighted(const AsciiString &unitName, Parameter *typeParm, Parameter *playerParm)
{
	Object *theObj = TheScriptEngine->getUnitNamed(unitName);
	if (!theObj)
		return false;
	int mask = TheScriptEngine->rva00357B82(playerParm);
	while (mask) {
		Player *player = ThePlayerList->getEachPlayerFromMask(mask);
		ObjectTypesTemp types;
		Script_objectTypesFromParam(typeParm, types.m_types);
		BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(theObj->getPosition(),
			theObj->getVisionRange(), 0,
			Rva0026137EFilter(player, true).link(Rva0026119DFilter().link(Rva00261058(theObj, false).link(
				Rva00261513Filter(theObj, true, -1.0f).link(&Rva002611BFFilter(theObj))))), 0);
		Object *obj;
		while ((obj = hits.next()) != 0)
			if (types.m_types->isInSet(obj->getTemplate()->getName()))
				return true;
	}
	return false;
}
