// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?ObjectModifyUpgrade@LuaScriptEngine@@SAHPAUlua_State@@_N@Z, retail 0x003354D6 220B.
// Gap between CreateAndFire 0x0033541C and HasUpgrade 0x003355B2, same flags.
// Grants/removes player or object upgrades by bool arg.
// Evidence: rowed lua_gettop 0x00746F30, rowed Rva00990030Lookup 0x00747190,
// rowed lua_type 0x007470A0, rowed findObjectByID 0x00049DC5,
// rowed lua_tostring 0x007473B0, rowed StringBase ctor 0x00037BA0,
// rowed findUpgrade 0x0026F26D, rowed releaseBuffer 0x00036410,
// rowed getControllingPlayer 0x0028AFA9, rowed Player addUpgrade 0x002AE329,
// rowed Player removeUpgrade 0x002ADAC3, rowed Object rva00293077 0x00293077,
// rowed Object removeUpgrade 0x00290D42.
#include "ascii_string.h"

struct lua_State;
extern "C" int lua_gettop(lua_State *s);
extern "C" int lua_type(lua_State *s, int i);
extern "C" const char *lua_tostring(lua_State *s, int i);

struct Rva00990030Range;
unsigned Rva00990030Lookup(Rva00990030Range *r, int i);

#include "../../Common/GameLogicObjectLookupView.h"
class Object;
class Player;
class Upgrade;
class UpgradeTemplate;
enum UpgradeStatusType { UPGRADE_STATUS_02 = 2 };
typedef int Int;

extern GameLogic *TheGameLogic;

class Object
{
public:
	Player *getControllingPlayer() const;
	void rva00293077(const void *a);
	void removeUpgrade(const UpgradeTemplate *u);
};

class Player
{
public:
	Upgrade *addUpgrade(const UpgradeTemplate *t, UpgradeStatusType s, Int x);
	void removeUpgrade(const UpgradeTemplate *t, Int x);
};

class UpgradeTemplate
{
public:
	int m_00;
	int m_type;
};

class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &n) const;
};
extern UpgradeCenter *TheUpgradeCenter;

// Static callback view only; this helper reads no LuaScriptEngine object.
// WB C06AD0 ObjectModifyUpgrade has the same two stack arguments, complete
// grant/remove control flow and retail call targets; native 3354D6..3355B2.
class LuaScriptEngine
{
public:
	static int ObjectModifyUpgrade(lua_State *luaState, bool grant);
};

int LuaScriptEngine::ObjectModifyUpgrade(lua_State *luaState, bool grant)
{
	if (lua_gettop(luaState) < 2)
		return 0;
	unsigned id = Rva00990030Lookup((Rva00990030Range *)luaState, 1);
	if (id == 0 && lua_type(luaState, 1) != 1)
		return 0;
	Object *obj = TheGameLogic->findObjectByID((ObjectID)id);
	if (obj == 0)
		return 0;
	const char *upName = lua_tostring(luaState, 2);
	const UpgradeTemplate *tpl;
	{
		AsciiString tmp(upName);
		tpl = TheUpgradeCenter->findUpgrade(tmp);
	}
	if (tpl == 0)
		return 0;
	if (tpl->m_type == 0) {
		Player *player = obj->getControllingPlayer();
		if (grant != 0) {
			player->addUpgrade(tpl, (UpgradeStatusType)2, 0);
		} else {
			player->removeUpgrade(tpl, 0);
		}
	} else {
		if (grant != 0) {
			obj->rva00293077(tpl);
		} else {
			obj->removeUpgrade(tpl);
		}
	}
	return 1;
}

// ?ObjectGrantUpgrade@@YAHPAUlua_State@@@Z, retail 0x00335692 14B: the Lua
// callback registration 0x003386BF names ObjectGrantUpgrade (pushcclosure
// then setglobal); it forwards to the shared worker above with grant=true.
int ObjectGrantUpgrade(lua_State *luaState)
{
	return LuaScriptEngine::ObjectModifyUpgrade(luaState, true);
}

// ?ObjectRemoveUpgrade@@YAHPAUlua_State@@@Z, retail 0x003356A0 14B: the Lua
// callback registration 0x003386DA names ObjectRemoveUpgrade; same worker
// with grant=false.
int ObjectRemoveUpgrade(lua_State *luaState)
{
	return LuaScriptEngine::ObjectModifyUpgrade(luaState, false);
}
