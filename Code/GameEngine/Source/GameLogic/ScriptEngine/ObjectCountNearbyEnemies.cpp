// cl: /MD /GX
//
// The Lua callback ObjectCountNearbyEnemies (0x003362FE): the registration at
// 0x00338531 pushes it with lua_pushcclosure and lua_setglobal names it next.
// Ported from Open-BFME-1 GameEngine/Source/GameLogic/ScriptEngine/
// ObjectCountNearbyEnemies.cpp (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76):
// resolve the object argument, then push how many objects within the second
// argument's range pass the relationship-1, alive and not-this-object filters
// (BFME2's partition filter chain, the view AIStructureCreepTactic.cpp
// documents), or 0 when the object is gone. Retail drops the hit list's
// unwind state once the filters die, so nothing after the query may throw:
// lua_pushnumber is declared throw() here.

struct Rva00990030Range;
unsigned Rva00990030Lookup(Rva00990030Range *range, int index);	// 0x00747190

struct lua_State;
extern "C" int lua_type(lua_State *state, int index);
extern "C" double lua_tonumber(lua_State *state, int index);
extern "C" void lua_pushnil(lua_State *state);
extern "C" void lua_pushnumber(lua_State *state, double n) throw();

class Object;

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

// vftable 0x00BFAD10, allow 0x0026119D: not effectively dead.
class Rva0026119DFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};

// vftable 0x00BF91BC, allow 0x002611BF.
class Rva002611BFFilter : public Rva000421C8
{
public:
	Rva002611BFFilter(const Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
};

// vftable 0x00BFBC90, allow 0x00260EB1, getPlayerMask 0x00260E6A: the object,
// relationship flags and whether a hit allows.
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

// Native lookup 0x00049DC5 takes the same 32-bit ObjectID enum as its
// verified provider; only the declaration changes, not the ID representation.
enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);	// 0x00049DC5
};
extern GameLogic *TheGameLogic;

// The hit list: an object and its distance per entry.
struct Rva002E8130Entry
{
	Object *m_object;
	unsigned m_distanceBits;
};

struct Rva009F39F0Payload
{
	int size() const { return m_end - m_begin; }
	Rva002E8130Entry *m_begin;
	Rva002E8130Entry *m_end;
};

struct BfmeWideResult
{
	~BfmeWideResult();	// 0x0004AA28
	Rva009F39F0Payload *m_value;
};

class PartitionManager
{
public:
	BfmeWideResult iterateObjectsInRange(const Coord3D *pos, float radius, int distCalc,
		Rva000421C8 *filters, int order);	// 0x00625610
};
extern PartitionManager *ThePartitionManager;

int ObjectCountNearbyEnemies(lua_State *state)
{
	unsigned objectID = Rva00990030Lookup((Rva00990030Range *)state, 1);
	if (!objectID && lua_type(state, 1) != 1) {
		lua_pushnil(state);
		return 0;
	}
	int radius = (int)lua_tonumber(state, 2);
	Object *object = TheGameLogic->findObjectByID((ObjectID)objectID);
	if (object) {
		BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(object->getPosition(),
			(float)radius, 0,
			Rva00260EB1Filter(object, 1, false).link(Rva0026119DFilter().link(&Rva002611BFFilter(object))), 1);
		lua_pushnumber(state, (double)hits.m_value->size());
		return 1;
	}
	lua_pushnumber(state, 0.0);
	return 1;
}
