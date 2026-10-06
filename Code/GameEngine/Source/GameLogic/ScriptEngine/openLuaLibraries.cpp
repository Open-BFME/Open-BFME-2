// cl: /DNDEBUG /DWIN32 /MD /O1 /Ob1
//
// One unit for openLuaLibraries and its only caller, as in retail: the
// static function takes its lua_State in esi, a convention MSVC uses only
// for a caller in the same unit. /Ob1 keeps it out of line (retail calls it);
// /O1 gives the caller's zero-in-ebx pushes and memory-operand pushes. Both
// bodies byte-match under these flags. This replaces the unit's earlier
// invokeOpenLuaLibraries anchor, which existed only to emit the static body.

struct lua_State;

extern "C" void lua_baselibopen(lua_State *state);
extern "C" void lua_iolibopen(lua_State *state);
extern "C" void lua_strlibopen(lua_State *state);
extern "C" void lua_mathlibopen(lua_State *state);
extern "C" void lua_dblibopen(lua_State *state);

static void openLuaLibraries(lua_State *state)
{
	lua_baselibopen(state);
	lua_iolibopen(state);
	lua_strlibopen(state);
	lua_mathlibopen(state);
	lua_dblibopen(state);
}

// LuaScriptEngine's script-side function registration, retail 0x00338317
// (1221 bytes). Donor: Open-BFME-1 LuaScriptEngineRegisterScriptFunctions.cpp
// (0x002EC990). Target facts read from this body: the Lua state lives at +0x0C;
// lua_open(256) and the static openLuaLibraries above (its state arrives in
// esi, which is why both share this unit); each callback goes through
// luaV_Cclosure and lua_setglobal in retail order; then the scripts file is
// loaded and the script-event XML parsed. The callbacks are named by the Lua
// global each is bound to; the address-named ones keep their existing ledger
// names. The method name keeps the retail address: the caller at 0x003387DC
// is not yet identified.
extern "C" lua_State *lua_open(int stacksize);
extern "C" void luaV_Cclosure(lua_State *state, int (*function)(lua_State *), int upvalues);
extern "C" void lua_setglobal(lua_State *state, const char *name);
struct lua_Debug;
typedef void (*LuaHook)(lua_State *state, lua_Debug *ar);
extern "C" LuaHook lua_setlinehook(lua_State *state, LuaHook hook);
// The line hook at 0x00334587, rowed under its existing ledger name.
void bfmeHandleDeactivation574(void *state, void *ar);

int _ALERT(lua_State *state);
int GetFrame(lua_State *state);
int EvaluateCondition(lua_State *state);
int ExecuteAction(lua_State *state);
int Rva00334DDFObjectDescribe(lua_State *state);
int ObjectSpy(lua_State *state);
int ObjectDispatchEvent(lua_State *state);
int ObjectBroadcastEventToEnemies(lua_State *state);
int ObjectBroadcastEventToAllies(lua_State *state);
int ObjectBroadcastEventToCivilians(lua_State *state);
int ObjectBroadcastEventToUnits(lua_State *state);
int HordeBroadcastEventToMembers(lua_State *state);
int Rva00334E51(lua_State *state);
int Rva00334EC4(lua_State *state);
int ObjectCapturingObjectPlayerSide(lua_State *state);
int Rva00334FAB(lua_State *state);
int ObjectTestModelCondition(lua_State *state);
int ObjectTestCanSufferFear(lua_State *state);
int ObjectCountNearbyEnemies(lua_State *state);
int ObjectEnterFearState(lua_State *state);
int bfmeHelper6280(lua_State *state);
int bfmeHelper6320(lua_State *state);
int ObjectEnterUncontrollableCowerState(lua_State *state);
int ObjectEnterAlertState(lua_State *state);
int ObjectEnterRampageState(lua_State *state);
int ObjectPlaySound(lua_State *state);
int ObjectSetChanting(lua_State *state);
int ObjectSetFearFactor(lua_State *state);
int ObjectSetEnragedState(lua_State *state);
int ObjectDoSpecialPower(lua_State *state);
int ObjectCreateAndFireTempWeapon(lua_State *state);
int ObjectHasUpgrade(lua_State *state);
int ObjectGrantUpgrade(lua_State *state);
int ObjectRemoveUpgrade(lua_State *state);
int ObjectSetDelayedDeath(lua_State *state);
int Rva00334A3D(lua_State *state);
int ObjectHideSubObjectPermanently(lua_State *state);
int ObjectSetGeometryActive(lua_State *state);
int ObjectChangeAllegianceFromNonPlayablePlayer(lua_State *state);
int GetRandomNumber(lua_State *state);
int Rva00334D16(lua_State *state);

class Rva003340C1
{
public:
	void rva003345BE(const char *filename);
};

class LuaScriptEngine
{
public:
	void rva00338317RegisterScriptFunctions();
	void rva00338241(const char *filename, bool reload);

private:
	char m_pad00[0x0C];
	lua_State *m_luaState;
};

void LuaScriptEngine::rva00338317RegisterScriptFunctions()
{
	if (m_luaState == 0) {
		lua_State *state = lua_open(256);
		m_luaState = state;
		openLuaLibraries(state);
		luaV_Cclosure(m_luaState, _ALERT, 0);
		lua_setglobal(m_luaState, "_ALERT");
		luaV_Cclosure(m_luaState, GetFrame, 0);
		lua_setglobal(m_luaState, "GetFrame");
		luaV_Cclosure(m_luaState, EvaluateCondition, 0);
		lua_setglobal(m_luaState, "EvaluateCondition");
		luaV_Cclosure(m_luaState, ExecuteAction, 0);
		lua_setglobal(m_luaState, "ExecuteAction");
		luaV_Cclosure(m_luaState, Rva00334DDFObjectDescribe, 0);
		lua_setglobal(m_luaState, "ObjectDescription");
		luaV_Cclosure(m_luaState, ObjectSpy, 0);
		lua_setglobal(m_luaState, "ObjectSpy");
		luaV_Cclosure(m_luaState, ObjectDispatchEvent, 0);
		lua_setglobal(m_luaState, "ObjectDispatchEvent");
		luaV_Cclosure(m_luaState, ObjectBroadcastEventToEnemies, 0);
		lua_setglobal(m_luaState, "ObjectBroadcastEventToEnemies");
		luaV_Cclosure(m_luaState, ObjectBroadcastEventToAllies, 0);
		lua_setglobal(m_luaState, "ObjectBroadcastEventToAllies");
		luaV_Cclosure(m_luaState, ObjectBroadcastEventToCivilians, 0);
		lua_setglobal(m_luaState, "ObjectBroadcastEventToCivilians");
		luaV_Cclosure(m_luaState, ObjectBroadcastEventToUnits, 0);
		lua_setglobal(m_luaState, "ObjectBroadcastEventToUnits");
		luaV_Cclosure(m_luaState, HordeBroadcastEventToMembers, 0);
		lua_setglobal(m_luaState, "HordeBroadcastEventToMembers");
		luaV_Cclosure(m_luaState, Rva00334E51, 0);
		lua_setglobal(m_luaState, "ObjectTeamName");
		luaV_Cclosure(m_luaState, Rva00334EC4, 0);
		lua_setglobal(m_luaState, "ObjectPlayerSide");
		luaV_Cclosure(m_luaState, ObjectCapturingObjectPlayerSide, 0);
		lua_setglobal(m_luaState, "ObjectCapturingObjectPlayerSide");
		luaV_Cclosure(m_luaState, Rva00334FAB, 0);
		lua_setglobal(m_luaState, "ObjectTemplateName");
		luaV_Cclosure(m_luaState, ObjectTestModelCondition, 0);
		lua_setglobal(m_luaState, "ObjectTestModelCondition");
		luaV_Cclosure(m_luaState, ObjectTestCanSufferFear, 0);
		lua_setglobal(m_luaState, "ObjectTestCanSufferFear");
		luaV_Cclosure(m_luaState, ObjectCountNearbyEnemies, 0);
		lua_setglobal(m_luaState, "ObjectCountNearbyEnemies");
		luaV_Cclosure(m_luaState, ObjectEnterFearState, 0);
		lua_setglobal(m_luaState, "ObjectEnterFearState");
		luaV_Cclosure(m_luaState, bfmeHelper6280, 0);
		lua_setglobal(m_luaState, "ObjectEnterRunAwayPanicState");
		luaV_Cclosure(m_luaState, bfmeHelper6320, 0);
		lua_setglobal(m_luaState, "ObjectEnterCowerState");
		luaV_Cclosure(m_luaState, ObjectEnterUncontrollableCowerState, 0);
		lua_setglobal(m_luaState, "ObjectEnterUncontrollableCowerState");
		luaV_Cclosure(m_luaState, ObjectEnterAlertState, 0);
		lua_setglobal(m_luaState, "ObjectEnterAlertState");
		luaV_Cclosure(m_luaState, ObjectEnterRampageState, 0);
		lua_setglobal(m_luaState, "ObjectEnterRampageState");
		luaV_Cclosure(m_luaState, ObjectPlaySound, 0);
		lua_setglobal(m_luaState, "ObjectPlaySound");
		luaV_Cclosure(m_luaState, ObjectSetChanting, 0);
		lua_setglobal(m_luaState, "ObjectSetChanting");
		luaV_Cclosure(m_luaState, ObjectSetFearFactor, 0);
		lua_setglobal(m_luaState, "ObjectSetFearFactor");
		luaV_Cclosure(m_luaState, ObjectSetEnragedState, 0);
		lua_setglobal(m_luaState, "ObjectSetEnragedState");
		luaV_Cclosure(m_luaState, ObjectDoSpecialPower, 0);
		lua_setglobal(m_luaState, "ObjectDoSpecialPower");
		luaV_Cclosure(m_luaState, ObjectCreateAndFireTempWeapon, 0);
		lua_setglobal(m_luaState, "ObjectCreateAndFireTempWeapon");
		luaV_Cclosure(m_luaState, ObjectHasUpgrade, 0);
		lua_setglobal(m_luaState, "ObjectHasUpgrade");
		luaV_Cclosure(m_luaState, ObjectGrantUpgrade, 0);
		lua_setglobal(m_luaState, "ObjectGrantUpgrade");
		luaV_Cclosure(m_luaState, ObjectRemoveUpgrade, 0);
		lua_setglobal(m_luaState, "ObjectRemoveUpgrade");
		luaV_Cclosure(m_luaState, ObjectSetDelayedDeath, 0);
		lua_setglobal(m_luaState, "ObjectSetDelayedDeath");
		luaV_Cclosure(m_luaState, Rva00334A3D, 0);
		lua_setglobal(m_luaState, "ObjectHideSubObject");
		luaV_Cclosure(m_luaState, ObjectHideSubObjectPermanently, 0);
		lua_setglobal(m_luaState, "ObjectHideSubObjectPermanently");
		luaV_Cclosure(m_luaState, ObjectSetGeometryActive, 0);
		lua_setglobal(m_luaState, "ObjectSetGeometryActive");
		luaV_Cclosure(m_luaState, ObjectChangeAllegianceFromNonPlayablePlayer, 0);
		lua_setglobal(m_luaState, "ObjectChangeAllegianceFromNonPlayablePlayer");
		luaV_Cclosure(m_luaState, GetRandomNumber, 0);
		lua_setglobal(m_luaState, "GetRandomNumber");
		luaV_Cclosure(m_luaState, Rva00334D16, 0);
		lua_setglobal(m_luaState, "ObjectForbidPlayerCommands");
		lua_setlinehook(m_luaState, (LuaHook)bfmeHandleDeactivation574);
	}
	((Rva003340C1 *)this)->rva003345BE("Data\\Scripts\\Scripts.lua");
	rva00338241("Data\\Scripts\\ScriptEvents.xml", false);
}
