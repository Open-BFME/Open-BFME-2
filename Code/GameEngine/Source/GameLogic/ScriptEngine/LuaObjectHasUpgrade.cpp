// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?ObjectHasUpgrade@@YAHPAUlua_State@@@Z, retail 0x003355B2 224B.
// Lua binding: true (1.0) when the object has the named upgrade.
// Evidence: pinned name, rowed lua_gettop 0x00746F30, rowed Rva00990030Lookup
// 0x00747190, rowed lua_type 0x007470A0, rowed findObjectByID 0x00049DC5,
// rowed lua_tostring 0x007473B0, rowed StringBase ctor 0x00037BA0,
// rowed findUpgrade 0x0026F26D, rowed releaseBuffer 0x00036410,
// rowed getControllingPlayer 0x0028AFA9, rowed Player rva 0x002AB87D,
// rowed lua_pushnumber 0x00747570, globals TheGameLogic TheUpgradeCenter,
// neighbours LuaObjectModelConditionEnragedDelayedDeath and LuaPlaySounds.
#include "ascii_string.h"

struct lua_State;
extern "C" int lua_gettop(lua_State *s);
extern "C" int lua_type(lua_State *s, int i);
extern "C" const char *lua_tostring(lua_State *s, int i);
extern "C" void lua_pushnumber(lua_State *s, double v);

struct Rva00990030Range;
unsigned Rva00990030Lookup(Rva00990030Range *r, int i);

enum ObjectID { INVALID_OBJECT_ID = 0 };
class Object;
class Player;
class UpgradeTemplate;
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};
extern GameLogic *TheGameLogic;

class Object
{
public:
	Player *getControllingPlayer() const;
};

class Player
{
public:
	bool rva002AB87D(const UpgradeTemplate *t) const;
};

class UpgradeTemplate
{
public:
	int m_00;
	int m_04;
};

class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &n) const;
};
extern "C" UpgradeCenter *TheUpgradeCenter;

int ObjectHasUpgrade(lua_State *L)
{
	double result;
	if (lua_gettop(L) < 2)
		return 0;
	unsigned id = Rva00990030Lookup((Rva00990030Range *)L, 1);
	if (id == 0 && lua_type(L, 1) != 1)
		return 0;
	GameLogic *gl = TheGameLogic;
	result = 0.0;
	Object *obj = gl->findObjectByID((ObjectID)id);
	if (obj != 0) {
		const char *upName = lua_tostring(L, 2);
		const UpgradeTemplate *tpl;
		{
			AsciiString tmp(upName);
			tpl = TheUpgradeCenter->findUpgrade(tmp);
		}
		if (tpl != 0) {
			if (tpl->m_04 == 0) {
				if (obj->getControllingPlayer()->rva002AB87D(tpl))
					result = 1.0;
			}
			lua_pushnumber(L, result);
			return 1;
		}
	}
	return 0;
}
