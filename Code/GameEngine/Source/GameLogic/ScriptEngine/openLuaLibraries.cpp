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
int Rva00334E51(lua_State *state);
int ObjectPlayerSide(lua_State *state);
int ObjectCapturingObjectPlayerSide(lua_State *state);
int ObjectTemplateName(lua_State *state);
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

#include "../../../Include/GameLogic/LuaScriptEngine.h"

void LuaScriptEngine::rva00338317RegisterScriptFunctions()
{
	if (field0C == 0) {
		lua_State *state = lua_open(256);
		field0C = state;
		openLuaLibraries(state);
		lua_pushcclosure(field0C, _ALERT, 0);
		lua_setglobal(field0C, "_ALERT");
		lua_pushcclosure(field0C, GetFrame, 0);
		lua_setglobal(field0C, "GetFrame");
		lua_pushcclosure(field0C, EvaluateCondition, 0);
		lua_setglobal(field0C, "EvaluateCondition");
		lua_pushcclosure(field0C, ExecuteAction, 0);
		lua_setglobal(field0C, "ExecuteAction");
		lua_pushcclosure(field0C, ObjectDescription, 0);
		lua_setglobal(field0C, "ObjectDescription");
		lua_pushcclosure(field0C, ObjectSpy, 0);
		lua_setglobal(field0C, "ObjectSpy");
		lua_pushcclosure(field0C, ObjectDispatchEvent, 0);
		lua_setglobal(field0C, "ObjectDispatchEvent");
		lua_pushcclosure(field0C, ObjectBroadcastEventToEnemies, 0);
		lua_setglobal(field0C, "ObjectBroadcastEventToEnemies");
		lua_pushcclosure(field0C, ObjectBroadcastEventToAllies, 0);
		lua_setglobal(field0C, "ObjectBroadcastEventToAllies");
		lua_pushcclosure(field0C, ObjectBroadcastEventToCivilians, 0);
		lua_setglobal(field0C, "ObjectBroadcastEventToCivilians");
		lua_pushcclosure(field0C, ObjectBroadcastEventToUnits, 0);
		lua_setglobal(field0C, "ObjectBroadcastEventToUnits");
		lua_pushcclosure(field0C, HordeBroadcastEventToMembers, 0);
		lua_setglobal(field0C, "HordeBroadcastEventToMembers");
		lua_pushcclosure(field0C, Rva00334E51, 0);
		lua_setglobal(field0C, "ObjectTeamName");
		lua_pushcclosure(field0C, ObjectPlayerSide, 0);
		lua_setglobal(field0C, "ObjectPlayerSide");
		lua_pushcclosure(field0C, ObjectCapturingObjectPlayerSide, 0);
		lua_setglobal(field0C, "ObjectCapturingObjectPlayerSide");
		lua_pushcclosure(field0C, ObjectTemplateName, 0);
		lua_setglobal(field0C, "ObjectTemplateName");
		lua_pushcclosure(field0C, ObjectTestModelCondition, 0);
		lua_setglobal(field0C, "ObjectTestModelCondition");
		lua_pushcclosure(field0C, ObjectTestCanSufferFear, 0);
		lua_setglobal(field0C, "ObjectTestCanSufferFear");
		lua_pushcclosure(field0C, ObjectCountNearbyEnemies, 0);
		lua_setglobal(field0C, "ObjectCountNearbyEnemies");
		lua_pushcclosure(field0C, ObjectEnterFearState, 0);
		lua_setglobal(field0C, "ObjectEnterFearState");
		lua_pushcclosure(field0C, bfmeHelper6280, 0);
		lua_setglobal(field0C, "ObjectEnterRunAwayPanicState");
		lua_pushcclosure(field0C, bfmeHelper6320, 0);
		lua_setglobal(field0C, "ObjectEnterCowerState");
		lua_pushcclosure(field0C, ObjectEnterUncontrollableCowerState, 0);
		lua_setglobal(field0C, "ObjectEnterUncontrollableCowerState");
		lua_pushcclosure(field0C, ObjectEnterAlertState, 0);
		lua_setglobal(field0C, "ObjectEnterAlertState");
		lua_pushcclosure(field0C, ObjectEnterRampageState, 0);
		lua_setglobal(field0C, "ObjectEnterRampageState");
		lua_pushcclosure(field0C, ObjectPlaySound, 0);
		lua_setglobal(field0C, "ObjectPlaySound");
		lua_pushcclosure(field0C, ObjectSetChanting, 0);
		lua_setglobal(field0C, "ObjectSetChanting");
		lua_pushcclosure(field0C, ObjectSetFearFactor, 0);
		lua_setglobal(field0C, "ObjectSetFearFactor");
		lua_pushcclosure(field0C, ObjectSetEnragedState, 0);
		lua_setglobal(field0C, "ObjectSetEnragedState");
		lua_pushcclosure(field0C, ObjectDoSpecialPower, 0);
		lua_setglobal(field0C, "ObjectDoSpecialPower");
		lua_pushcclosure(field0C, ObjectCreateAndFireTempWeapon, 0);
		lua_setglobal(field0C, "ObjectCreateAndFireTempWeapon");
		lua_pushcclosure(field0C, ObjectHasUpgrade, 0);
		lua_setglobal(field0C, "ObjectHasUpgrade");
		lua_pushcclosure(field0C, ObjectGrantUpgrade, 0);
		lua_setglobal(field0C, "ObjectGrantUpgrade");
		lua_pushcclosure(field0C, ObjectRemoveUpgrade, 0);
		lua_setglobal(field0C, "ObjectRemoveUpgrade");
		lua_pushcclosure(field0C, ObjectSetDelayedDeath, 0);
		lua_setglobal(field0C, "ObjectSetDelayedDeath");
		lua_pushcclosure(field0C, Rva00334A3D, 0);
		lua_setglobal(field0C, "ObjectHideSubObject");
		lua_pushcclosure(field0C, ObjectHideSubObjectPermanently, 0);
		lua_setglobal(field0C, "ObjectHideSubObjectPermanently");
		lua_pushcclosure(field0C, ObjectSetGeometryActive, 0);
		lua_setglobal(field0C, "ObjectSetGeometryActive");
		lua_pushcclosure(field0C, ObjectChangeAllegianceFromNonPlayablePlayer, 0);
		lua_setglobal(field0C, "ObjectChangeAllegianceFromNonPlayablePlayer");
		lua_pushcclosure(field0C, GetRandomNumber, 0);
		lua_setglobal(field0C, "GetRandomNumber");
		lua_pushcclosure(field0C, Rva00334D16, 0);
		lua_setglobal(field0C, "ObjectForbidPlayerCommands");
		lua_setlinehook(field0C, (LuaHook)bfmeHandleDeactivation574);
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
int CurDrawableHideModule(void*);
int CurDrawableShowModule(void*);
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
void LuaScriptEngine::init()
{
 InitializeInternalEvents();
 if(field10==0) {
  lua_State* state=lua_open(256);
  field10=state;
  openLuaLibraries(state);
  lua_pushcclosure(field10,_ALERT,0);
  lua_setglobal(field10,"_ALERT");
  lua_pushcclosure(field10,GetFrame,0);
  lua_setglobal(field10,"GetFrame");
  lua_pushcclosure(field10,CurDrawableModelcondition,0);
  lua_setglobal(field10,"CurDrawableModelcondition");
  lua_pushcclosure(field10,CurDrawableObjectStatus,0);
  lua_setglobal(field10,"CurDrawableObjectStatus");
  lua_pushcclosure(field10,CurDrawableShowSubObject,0);
  lua_setglobal(field10,"CurDrawableShowSubObject");
  lua_pushcclosure(field10,CurDrawableHideSubObject,0);
  lua_setglobal(field10,"CurDrawableHideSubObject");
  lua_pushcclosure(field10,CurDrawableShowSubObjectPermanently,0);
  lua_setglobal(field10,"CurDrawableShowSubObjectPermanently");
  lua_pushcclosure(field10,CurDrawableHideSubObjectPermanently,0);
  lua_setglobal(field10,"CurDrawableHideSubObjectPermanently");
  lua_pushcclosure(field10,reinterpret_cast<int (*)(lua_State*)>(CurDrawableHideModule),0);
  lua_setglobal(field10,"CurDrawableHideModule");
  lua_pushcclosure(field10,reinterpret_cast<int (*)(lua_State*)>(CurDrawableShowModule),0);
  lua_setglobal(field10,"CurDrawableShowModule");
  lua_pushcclosure(field10,CurDrawablePrevAnimationState,0);
  lua_setglobal(field10,"CurDrawablePrevAnimationState");
  lua_pushcclosure(field10,CurDrawablePrevAnimation,0);
  lua_setglobal(field10,"CurDrawablePrevAnimation");
  lua_pushcclosure(field10,CurDrawableGetCurrentTargetDistance,0);
  lua_setglobal(field10,"CurDrawableGetCurrentTargetDistance");
  lua_pushcclosure(field10,CurDrawableGetCurrentTargetHeight,0);
  lua_setglobal(field10,"CurDrawableGetCurrentTargetHeight");
  lua_pushcclosure(field10,CurDrawableGetCurrentTargetBearing,0);
  lua_setglobal(field10,"CurDrawableGetCurrentTargetBearing");
  lua_pushcclosure(field10,CurDrawablePrevAnimFraction,0);
  lua_setglobal(field10,"CurDrawablePrevAnimFraction");
  lua_pushcclosure(field10,CurDrawableSetTransitionAnimState,0);
  lua_setglobal(field10,"CurDrawableSetTransitionAnimState");
  lua_pushcclosure(field10,CurDrawableAllowToContinue,0);
  lua_setglobal(field10,"CurDrawableAllowToContinue");
  lua_pushcclosure(field10,CurDrawablePlaySound,0);
  lua_setglobal(field10,"CurDrawablePlaySound");
  lua_pushcclosure(field10,CurDrawableIsCurrentTargetKindof,0);
  lua_setglobal(field10,"CurDrawableIsCurrentTargetKindof");
  lua_pushcclosure(field10,GetClientRandomNumberReal,0);
  lua_setglobal(field10,"GetClientRandomNumberReal");
  lua_setlinehook(field10,(LuaHook)bfmeHandleDeactivation574);
 }
}
