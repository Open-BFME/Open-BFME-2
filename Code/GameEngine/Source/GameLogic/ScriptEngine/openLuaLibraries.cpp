// cl: /O1 /DNDEBUG /DWIN32 /MD /Ob1
//
// One unit for openLuaLibraries and its registration callers, as in retail: the
// static function takes its lua_State in esi, a convention MSVC uses only
// for callers in the same unit. /Ob1 keeps it out of line (retail calls it);
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
// esi, which is why both share this unit); each callback is pushed with
// lua_pushcclosure(state, fn, 0) -- Lua 4.0's lua_register, whose call sites
// land on the API's 5-byte thunk at 0x00747640 rather than on luaV_Cclosure
// behind it -- and bound with lua_setglobal in retail order; then the scripts file is
// loaded and the script-event XML parsed. The callbacks are named by the Lua
// global each is bound to; the address-named ones keep their existing ledger
// names. The method name keeps the retail address: the caller at 0x003387DC
// is not yet identified.
extern "C" lua_State *lua_open(int stacksize);
extern "C" void lua_pushcclosure(lua_State *state, int (*function)(lua_State *), int upvalues);
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

class LuaScriptEngine
{
public:
	void rva00338317RegisterScriptFunctions();
	void InitializeInternalEvents();
	void rva00335D5BRegisterDrawableFunctions();
	void LoadXML(const char *filename, bool reload);
	void LoadScripts(const char *filename);
	static int ObjectDescription(lua_State *state);

private:
	char m_pad00[0x0C];
	lua_State *m_luaState;
	lua_State *m_drawLuaState; // native+10, distinct from script state+C
};

void LuaScriptEngine::rva00338317RegisterScriptFunctions()
{
	if (m_luaState == 0) {
		lua_State *state = lua_open(256);
		m_luaState = state;
		openLuaLibraries(state);
		lua_pushcclosure(m_luaState, _ALERT, 0);
		lua_setglobal(m_luaState, "_ALERT");
		lua_pushcclosure(m_luaState, GetFrame, 0);
		lua_setglobal(m_luaState, "GetFrame");
		lua_pushcclosure(m_luaState, EvaluateCondition, 0);
		lua_setglobal(m_luaState, "EvaluateCondition");
		lua_pushcclosure(m_luaState, ExecuteAction, 0);
		lua_setglobal(m_luaState, "ExecuteAction");
		lua_pushcclosure(m_luaState, ObjectDescription, 0);
		lua_setglobal(m_luaState, "ObjectDescription");
		lua_pushcclosure(m_luaState, ObjectSpy, 0);
		lua_setglobal(m_luaState, "ObjectSpy");
		lua_pushcclosure(m_luaState, ObjectDispatchEvent, 0);
		lua_setglobal(m_luaState, "ObjectDispatchEvent");
		lua_pushcclosure(m_luaState, ObjectBroadcastEventToEnemies, 0);
		lua_setglobal(m_luaState, "ObjectBroadcastEventToEnemies");
		lua_pushcclosure(m_luaState, ObjectBroadcastEventToAllies, 0);
		lua_setglobal(m_luaState, "ObjectBroadcastEventToAllies");
		lua_pushcclosure(m_luaState, ObjectBroadcastEventToCivilians, 0);
		lua_setglobal(m_luaState, "ObjectBroadcastEventToCivilians");
		lua_pushcclosure(m_luaState, ObjectBroadcastEventToUnits, 0);
		lua_setglobal(m_luaState, "ObjectBroadcastEventToUnits");
		lua_pushcclosure(m_luaState, HordeBroadcastEventToMembers, 0);
		lua_setglobal(m_luaState, "HordeBroadcastEventToMembers");
		lua_pushcclosure(m_luaState, Rva00334E51, 0);
		lua_setglobal(m_luaState, "ObjectTeamName");
		lua_pushcclosure(m_luaState, Rva00334EC4, 0);
		lua_setglobal(m_luaState, "ObjectPlayerSide");
		lua_pushcclosure(m_luaState, ObjectCapturingObjectPlayerSide, 0);
		lua_setglobal(m_luaState, "ObjectCapturingObjectPlayerSide");
		lua_pushcclosure(m_luaState, Rva00334FAB, 0);
		lua_setglobal(m_luaState, "ObjectTemplateName");
		lua_pushcclosure(m_luaState, ObjectTestModelCondition, 0);
		lua_setglobal(m_luaState, "ObjectTestModelCondition");
		lua_pushcclosure(m_luaState, ObjectTestCanSufferFear, 0);
		lua_setglobal(m_luaState, "ObjectTestCanSufferFear");
		lua_pushcclosure(m_luaState, ObjectCountNearbyEnemies, 0);
		lua_setglobal(m_luaState, "ObjectCountNearbyEnemies");
		lua_pushcclosure(m_luaState, ObjectEnterFearState, 0);
		lua_setglobal(m_luaState, "ObjectEnterFearState");
		lua_pushcclosure(m_luaState, bfmeHelper6280, 0);
		lua_setglobal(m_luaState, "ObjectEnterRunAwayPanicState");
		lua_pushcclosure(m_luaState, bfmeHelper6320, 0);
		lua_setglobal(m_luaState, "ObjectEnterCowerState");
		lua_pushcclosure(m_luaState, ObjectEnterUncontrollableCowerState, 0);
		lua_setglobal(m_luaState, "ObjectEnterUncontrollableCowerState");
		lua_pushcclosure(m_luaState, ObjectEnterAlertState, 0);
		lua_setglobal(m_luaState, "ObjectEnterAlertState");
		lua_pushcclosure(m_luaState, ObjectEnterRampageState, 0);
		lua_setglobal(m_luaState, "ObjectEnterRampageState");
		lua_pushcclosure(m_luaState, ObjectPlaySound, 0);
		lua_setglobal(m_luaState, "ObjectPlaySound");
		lua_pushcclosure(m_luaState, ObjectSetChanting, 0);
		lua_setglobal(m_luaState, "ObjectSetChanting");
		lua_pushcclosure(m_luaState, ObjectSetFearFactor, 0);
		lua_setglobal(m_luaState, "ObjectSetFearFactor");
		lua_pushcclosure(m_luaState, ObjectSetEnragedState, 0);
		lua_setglobal(m_luaState, "ObjectSetEnragedState");
		lua_pushcclosure(m_luaState, ObjectDoSpecialPower, 0);
		lua_setglobal(m_luaState, "ObjectDoSpecialPower");
		lua_pushcclosure(m_luaState, ObjectCreateAndFireTempWeapon, 0);
		lua_setglobal(m_luaState, "ObjectCreateAndFireTempWeapon");
		lua_pushcclosure(m_luaState, ObjectHasUpgrade, 0);
		lua_setglobal(m_luaState, "ObjectHasUpgrade");
		lua_pushcclosure(m_luaState, ObjectGrantUpgrade, 0);
		lua_setglobal(m_luaState, "ObjectGrantUpgrade");
		lua_pushcclosure(m_luaState, ObjectRemoveUpgrade, 0);
		lua_setglobal(m_luaState, "ObjectRemoveUpgrade");
		lua_pushcclosure(m_luaState, ObjectSetDelayedDeath, 0);
		lua_setglobal(m_luaState, "ObjectSetDelayedDeath");
		lua_pushcclosure(m_luaState, Rva00334A3D, 0);
		lua_setglobal(m_luaState, "ObjectHideSubObject");
		lua_pushcclosure(m_luaState, ObjectHideSubObjectPermanently, 0);
		lua_setglobal(m_luaState, "ObjectHideSubObjectPermanently");
		lua_pushcclosure(m_luaState, ObjectSetGeometryActive, 0);
		lua_setglobal(m_luaState, "ObjectSetGeometryActive");
		lua_pushcclosure(m_luaState, ObjectChangeAllegianceFromNonPlayablePlayer, 0);
		lua_setglobal(m_luaState, "ObjectChangeAllegianceFromNonPlayablePlayer");
		lua_pushcclosure(m_luaState, GetRandomNumber, 0);
		lua_setglobal(m_luaState, "GetRandomNumber");
		lua_pushcclosure(m_luaState, Rva00334D16, 0);
		lua_setglobal(m_luaState, "ObjectForbidPlayerCommands");
		lua_setlinehook(m_luaState, (LuaHook)bfmeHandleDeactivation574);
	}
	LoadScripts("Data\\Scripts\\Scripts.lua");
	LoadXML("Data\\Scripts\\ScriptEvents.xml", false);
}

int _ALERT(lua_State*);
int GetFrame(lua_State*);
int CurDrawableModelcondition(lua_State*);
int CurDrawableObjectStatus(lua_State*);
int CurDrawableShowSubObject(lua_State*);
int CurDrawableHideSubObject(lua_State*);
int CurDrawableShowSubObjectPermanently(lua_State*);
int CurDrawableHideSubObjectPermanently(lua_State*);
int bfmeGoEFFa(void*);
int bfmeGoEFFb(void*);
int CurDrawablePrevAnimationState(lua_State*);
int CurDrawablePrevAnimation(lua_State*);
int CurDrawableGetCurrentTargetDistance(lua_State*);
int CurDrawableGetCurrentTargetHeight(lua_State*);
int CurDrawableGetCurrentTargetBearing(lua_State*);
int CurDrawablePrevAnimFraction(lua_State*);
int CurDrawableSetTransitionAnimState(lua_State*);
int CurDrawableAllowToContinue(lua_State*);
int CurDrawablePlaySound(lua_State*);
int CurDrawableIsCurrentTargetKindof(lua_State*);
int GetClientRandomNumberReal(lua_State*);

// Target335D5B..335FE1 is complete646B, nativeRET0. Its paired script
// registration at338317 uses state+C; this accesses the distinct state+10,
// initializes the owned332B7A internal-event table and binds21 callbacks
// whose bodies are independently owned. The callback names/order and Lua
// strings are target facts; the old PAX callback spellings are retained
// through cdecl pointer views, without a second name or new pin.
// The Lua initialization/registration pattern follows the existing
// BF1-guided sibling above; original member name remains unknown.
// Both callers must share this visible static helper for the nativeESI ABI.
void LuaScriptEngine::rva00335D5BRegisterDrawableFunctions()
{
 InitializeInternalEvents();
 if(m_drawLuaState==0) {
  lua_State* state=lua_open(256);
  m_drawLuaState=state;
  openLuaLibraries(state);
  lua_pushcclosure(m_drawLuaState,_ALERT,0);
  lua_setglobal(m_drawLuaState,"_ALERT");
  lua_pushcclosure(m_drawLuaState,GetFrame,0);
  lua_setglobal(m_drawLuaState,"GetFrame");
  lua_pushcclosure(m_drawLuaState,CurDrawableModelcondition,0);
  lua_setglobal(m_drawLuaState,"CurDrawableModelcondition");
  lua_pushcclosure(m_drawLuaState,CurDrawableObjectStatus,0);
  lua_setglobal(m_drawLuaState,"CurDrawableObjectStatus");
  lua_pushcclosure(m_drawLuaState,CurDrawableShowSubObject,0);
  lua_setglobal(m_drawLuaState,"CurDrawableShowSubObject");
  lua_pushcclosure(m_drawLuaState,CurDrawableHideSubObject,0);
  lua_setglobal(m_drawLuaState,"CurDrawableHideSubObject");
  lua_pushcclosure(m_drawLuaState,CurDrawableShowSubObjectPermanently,0);
  lua_setglobal(m_drawLuaState,"CurDrawableShowSubObjectPermanently");
  lua_pushcclosure(m_drawLuaState,CurDrawableHideSubObjectPermanently,0);
  lua_setglobal(m_drawLuaState,"CurDrawableHideSubObjectPermanently");
  lua_pushcclosure(m_drawLuaState,reinterpret_cast<int (*)(lua_State*)>(bfmeGoEFFa),0);
  lua_setglobal(m_drawLuaState,"CurDrawableHideModule");
  lua_pushcclosure(m_drawLuaState,reinterpret_cast<int (*)(lua_State*)>(bfmeGoEFFb),0);
  lua_setglobal(m_drawLuaState,"CurDrawableShowModule");
  lua_pushcclosure(m_drawLuaState,CurDrawablePrevAnimationState,0);
  lua_setglobal(m_drawLuaState,"CurDrawablePrevAnimationState");
  lua_pushcclosure(m_drawLuaState,CurDrawablePrevAnimation,0);
  lua_setglobal(m_drawLuaState,"CurDrawablePrevAnimation");
  lua_pushcclosure(m_drawLuaState,CurDrawableGetCurrentTargetDistance,0);
  lua_setglobal(m_drawLuaState,"CurDrawableGetCurrentTargetDistance");
  lua_pushcclosure(m_drawLuaState,CurDrawableGetCurrentTargetHeight,0);
  lua_setglobal(m_drawLuaState,"CurDrawableGetCurrentTargetHeight");
  lua_pushcclosure(m_drawLuaState,CurDrawableGetCurrentTargetBearing,0);
  lua_setglobal(m_drawLuaState,"CurDrawableGetCurrentTargetBearing");
  lua_pushcclosure(m_drawLuaState,CurDrawablePrevAnimFraction,0);
  lua_setglobal(m_drawLuaState,"CurDrawablePrevAnimFraction");
  lua_pushcclosure(m_drawLuaState,CurDrawableSetTransitionAnimState,0);
  lua_setglobal(m_drawLuaState,"CurDrawableSetTransitionAnimState");
  lua_pushcclosure(m_drawLuaState,CurDrawableAllowToContinue,0);
  lua_setglobal(m_drawLuaState,"CurDrawableAllowToContinue");
  lua_pushcclosure(m_drawLuaState,CurDrawablePlaySound,0);
  lua_setglobal(m_drawLuaState,"CurDrawablePlaySound");
  lua_pushcclosure(m_drawLuaState,CurDrawableIsCurrentTargetKindof,0);
  lua_setglobal(m_drawLuaState,"CurDrawableIsCurrentTargetKindof");
  lua_pushcclosure(m_drawLuaState,GetClientRandomNumberReal,0);
  lua_setglobal(m_drawLuaState,"GetClientRandomNumberReal");
  lua_setlinehook(m_drawLuaState,(LuaHook)bfmeHandleDeactivation574);
 }
}
