// cl: /Ireference/shims/bfme2_ascii /MD /GX
//
// The ObjectBroadcastEventTo* Lua callbacks. The registration at 0x003383F1
// pushes each with lua_pushcclosure and the lua_setglobal after it names it:
//
//   0x00336434  ObjectBroadcastEventToEnemies    relationship 1 and the player
//                                                filter; draws the radius when
//                                                TheGlobalData +0xE9C is set
//   0x0033663C  ObjectBroadcastEventToAllies     relationship 4
//   0x003367A9  ObjectBroadcastEventToCivilians  relationship 2 and the player
//                                                filter
//   0x0033694D  ObjectBroadcastEventToUnits      the player filter
//
// Each resolves the object (argument 1) and the event named by argument 2,
// then sends that event to every object within argument 3's radius that
// passes its filters (BFME2's partition filter chain, the view
// AIStructureCreepTactic.cpp documents), with the delayed-event arguments
// the object's ID (type 3) and argument 4's text (type 4). Shape after
// Open-BFME-1's ObjectBroadcastEventTo*.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76).
#include "ascii_string.h"

struct Rva00990030Range;
unsigned Rva00990030Lookup(Rva00990030Range *range, int index);	// 0x00747190

struct lua_State;
extern "C" int lua_type(lua_State *state, int index);
extern "C" double lua_tonumber(lua_State *state, int index);
extern "C" const char *lua_tostring(lua_State *state, int index);

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

class Rva00260EB1Filter : public Rva000421C8
{
public:
	Rva00260EB1Filter(const Object *obj, int flags, bool match)
		: m_obj(obj), m_flags(flags), m_match(match) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	const Object *m_obj;
	int m_flags;
	bool m_match;
};

class Rva00261058 : public Rva000421C8
{
public:
	Rva00261058(Object *obj, bool flag);	// 0x00261058
	virtual bool allow(Object *obj);
	Player *m_player;
	bool m_flag;
};

#pragma comment(linker, "/alternatename:?getPlayerMask@Rva000421C8@@UAEHXZ=?Get_File_Handle@FileClass@@UAEPAXXZ")

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object
{
public:
	const Coord3D *getPosition() const { return &m_pos; }
	char m_pad000[0x38];
	Coord3D m_pos;		// +0x38
};

// Zero Hour's GameCommon.h spells the id an enum; retail's 0x00049DC5 row takes it.
enum ObjectID { INVALID_ID = 0, FORCE_OBJECTID_TO_LONG_SIZE = 0x7ffffff };
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);	// 0x00049DC5
};
extern GameLogic *TheGameLogic;

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

class TerrainLogic
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual float getGroundHeight(float x, float y, Coord3D *normal = 0) const;
};
extern TerrainLogic *TheTerrainLogic;

class View
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void rvaSlot12(const Coord3D *pos, float radius, int color);
};
extern View *TheTacticalView;

class GlobalData
{
public:
	char m_pad000[0xE9C];
	bool m_E9C;		// +0xE9C
};
extern class GlobalData *TheWritableGlobalData;

typedef unsigned NameKeyType;

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);	// 0x00148E1A
};
extern NameKeyGenerator *TheNameKeyGenerator;

// One delayed Lua event argument (0x18 bytes): +0x0C an object ID (type 3),
// +0x10 a string (type 4), +0x14 the type.
struct BfmeDispatchDelayedLuaEvent
{
	void *m_vtable;
	float m_number;
	unsigned char m_boolean;
	unsigned m_objectID;
	AsciiString m_string;
	unsigned m_type;
};

struct BfmeDelayedLuaEventList
{
	BfmeDelayedLuaEventList();	// 0x000B6D8B
	~BfmeDelayedLuaEventList();	// 0x000B6DD2
	void *m_vtable;
	BfmeDispatchDelayedLuaEvent m_events[3];
};

// The global at 0x00E01DBC.
struct LuaDrawableState
{
	void *rva00333918(NameKeyType key);	// 0x00333918: the event named by key
	void rva00334634(void *event, Object *obj, BfmeDelayedLuaEventList *args);	// 0x00334634
};
class LuaScriptEngine;
extern LuaScriptEngine *TheLuaScriptEngine;

int ObjectBroadcastEventToEnemies(lua_State *state)
{
	unsigned objectID = Rva00990030Lookup((Rva00990030Range *)state, 1);
	if (!objectID && lua_type(state, 1) != 1)
		return 0;
	Object *object = TheGameLogic->findObjectByID((ObjectID)objectID);
	if (!object)
		return 0;

	BfmeDelayedLuaEventList eventList;
	const char *eventName = lua_tostring(state, 2);
	if (!eventName)
		return 0;
	void *event = reinterpret_cast<LuaDrawableState *>(TheLuaScriptEngine)->rva00333918(TheNameKeyGenerator->nameToKey(eventName));
	if (!event)
		return 0;

	float radius = (float)lua_tonumber(state, 3);
	const char *text = lua_tostring(state, 4);
	eventList.m_events[0].m_objectID = objectID;
	eventList.m_events[0].m_type = 3;
	if (text) {
		AsciiString value(text);
		eventList.m_events[1].m_string = value;
		eventList.m_events[1].m_type = 4;
	}

	Rva00260EB1Filter enemies(object, 1, false);
	Rva00261058 player(object, false);
	enemies.link(&player);

	if (TheWritableGlobalData->m_E9C) {
		Coord3D pos;
		pos.x = object->getPosition()->x;
		pos.y = object->getPosition()->y;
		pos.z = object->getPosition()->z;
		pos.z = TheTerrainLogic->getGroundHeight(pos.x, pos.y);
		TheTacticalView->rvaSlot12(&pos, radius, 0xFFFFFF00);
	}

	BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(object->getPosition(), radius, 1,
		&enemies, 1);
	Object *other;
	while ((other = hits.next()) != 0)
		reinterpret_cast<LuaDrawableState *>(TheLuaScriptEngine)->rva00334634(event, other, &eventList);
	return 0;
}

int ObjectBroadcastEventToAllies(lua_State *state)
{
	unsigned objectID = Rva00990030Lookup((Rva00990030Range *)state, 1);
	if (!objectID && lua_type(state, 1) != 1)
		return 0;
	Object *object = TheGameLogic->findObjectByID((ObjectID)objectID);
	if (!object)
		return 0;

	BfmeDelayedLuaEventList eventList;
	const char *eventName = lua_tostring(state, 2);
	if (!eventName)
		return 0;
	void *event = reinterpret_cast<LuaDrawableState *>(TheLuaScriptEngine)->rva00333918(TheNameKeyGenerator->nameToKey(eventName));
	if (!event)
		return 0;

	float radius = (float)lua_tonumber(state, 3);
	const char *text = lua_tostring(state, 4);
	eventList.m_events[0].m_objectID = objectID;
	eventList.m_events[0].m_type = 3;
	if (text) {
		AsciiString value(text);
		eventList.m_events[1].m_string = value;
		eventList.m_events[1].m_type = 4;
	}

	Rva00260EB1Filter allies(object, 4, false);
	BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(object->getPosition(), radius, 1,
		&allies, 1);
	Object *other;
	while ((other = hits.next()) != 0)
		reinterpret_cast<LuaDrawableState *>(TheLuaScriptEngine)->rva00334634(event, other, &eventList);
	return 0;
}

int ObjectBroadcastEventToCivilians(lua_State *state)
{
	unsigned objectID = Rva00990030Lookup((Rva00990030Range *)state, 1);
	if (!objectID && lua_type(state, 1) != 1)
		return 0;
	Object *object = TheGameLogic->findObjectByID((ObjectID)objectID);
	if (!object)
		return 0;

	BfmeDelayedLuaEventList eventList;
	const char *eventName = lua_tostring(state, 2);
	if (!eventName)
		return 0;
	void *event = reinterpret_cast<LuaDrawableState *>(TheLuaScriptEngine)->rva00333918(TheNameKeyGenerator->nameToKey(eventName));
	if (!event)
		return 0;

	float radius = (float)lua_tonumber(state, 3);
	const char *text = lua_tostring(state, 4);
	eventList.m_events[0].m_objectID = objectID;
	eventList.m_events[0].m_type = 3;
	if (text) {
		AsciiString value(text);
		eventList.m_events[1].m_string = value;
		eventList.m_events[1].m_type = 4;
	}

	Rva00260EB1Filter civilians(object, 2, false);
	Rva00261058 player(object, false);
	civilians.link(&player);
	BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(object->getPosition(), radius, 1,
		&civilians, 1);
	Object *other;
	while ((other = hits.next()) != 0)
		reinterpret_cast<LuaDrawableState *>(TheLuaScriptEngine)->rva00334634(event, other, &eventList);
	return 0;
}

int ObjectBroadcastEventToUnits(lua_State *state)
{
	unsigned objectID = Rva00990030Lookup((Rva00990030Range *)state, 1);
	if (!objectID && lua_type(state, 1) != 1)
		return 0;
	Object *object = TheGameLogic->findObjectByID((ObjectID)objectID);
	if (!object)
		return 0;

	BfmeDelayedLuaEventList eventList;
	const char *eventName = lua_tostring(state, 2);
	if (!eventName)
		return 0;
	void *event = reinterpret_cast<LuaDrawableState *>(TheLuaScriptEngine)->rva00333918(TheNameKeyGenerator->nameToKey(eventName));
	if (!event)
		return 0;

	float radius = (float)lua_tonumber(state, 3);
	const char *text = lua_tostring(state, 4);
	eventList.m_events[0].m_objectID = objectID;
	eventList.m_events[0].m_type = 3;
	if (text) {
		AsciiString value(text);
		eventList.m_events[1].m_string = value;
		eventList.m_events[1].m_type = 4;
	}

	Rva00261058 player(object, false);
	BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(object->getPosition(), radius, 1,
		&player, 1);
	Object *other;
	while ((other = hits.next()) != 0)
		reinterpret_cast<LuaDrawableState *>(TheLuaScriptEngine)->rva00334634(event, other, &eventList);
	return 0;
}
