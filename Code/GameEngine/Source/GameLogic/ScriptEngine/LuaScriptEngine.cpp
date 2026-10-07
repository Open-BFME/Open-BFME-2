// cl: /Ireference/shims/bfme2_ascii /O1 /MD /GX /arch:SSE
//
// Lua callbacks of BFME2's LuaScriptEngine.cpp: the file-name literal the two
// random-number bindings pass (VA 0x00C0DE00) reads
// "C:\projects\bfme2patch103\bfme2\Code\GameEngine\Source\GameLogic\
// ScriptEngine\LuaScriptEngine.cpp", and every body here is named by its
// registration: lua_pushcclosure (row @0x00747640) of the body's address
// followed by lua_setglobal (row @0x00747920) of the name string. The
// CurDrawable* names come from the drawable registration block
// (0x00335DC3..0x00335FB8), GetRandomNumber from the game registration at
// 0x00338782.
//
// Donor: Open-BFME-1 game/GameEngine/Source/GameLogic/ScriptEngine/
// LuaScriptEngine.cpp (revision 6583b3c1), which holds the BFME1 forms of
// GetClientRandomNumberReal, CurDrawableIsCurrentTargetKindof,
// CurDrawablePrevAnimationState and CurDrawablePrevAnimation. Target facts:
// the per-drawable Lua context sits at +0x9C of the Lua state global
// (+0x78 in BFME1), its drawable at +0x0C; the rest is read from the
// retail bodies, as noted per field.
#include "ascii_string.h"

struct lua_State;
extern "C" int lua_gettop(lua_State *state);
extern "C" double lua_tonumber(lua_State *state, int index);
extern "C" void lua_pushnumber(lua_State *state, double value);
extern "C" const char *lua_tostring(lua_State *state, int index);
extern "C" void lua_pushnil(lua_State *state);
extern "C" void lua_pushstring(lua_State *state, const char *value);

// lua_pushboolean, rowed under its BFME1 donor name at 0x00747540.
struct BfmeQ1039;
void bfmeGo1039E(BfmeQ1039 *q, int v);

typedef float Real;
typedef unsigned char Bool;

Real GetGameClientRandomValueReal(Real low, Real high, char *file, int line);
Real GetGameLogicRandomValueReal(Real low, Real high, char *file, int line);

template<int Bits> class BitFlags
{
public:
	static int getSingleBitFromName(const char *name);
};

// Retail returns the kind bit in al (callers test al); the row keeps the
// int spelling, so the Bool view truncates rather than converting.
class ThingTemplate
{
public:
	int rva000456AC(int bit) const;
	Bool isKindOf(int bit) const { return (Bool)rva000456AC(bit); }
};

class Object
{
public:
	__forceinline Bool testStatus(int bit) const
	{
		return (m_status[(unsigned int)bit >> 5] & (1u << (bit & 31))) != 0;
	}

	char m_pad00[0x04];
	ThingTemplate *m_template;	// +0x04
	char m_pad08[0x94 - 0x08];
	unsigned int m_status[2];	// +0x94, tested with BitFlags<101> bits
	char m_pad9C[0x398 - 0x9C];
	int m_currentTargetID;	// +0x398, passed to findObjectByID
};

enum ObjectID { INVALID_OBJECT_ID = 0 };

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};
extern GameLogic *TheGameLogic;

class Drawable
{
public:
	bool rva00278689(const AsciiString &name, bool a, bool b);
	void rva002724FD(const AsciiString &name, int show, int permanent, float c, float d);

	__forceinline Bool testModelCondition(int bit) const
	{
		return (m_conditionState[(unsigned int)bit >> 5] & (1u << (bit & 31))) != 0;
	}

	char m_pad000[0xFC];
	Object *m_object;	// +0xFC
	char m_pad100[0x258 - 0x100];
	unsigned int m_conditionState[10];	// +0x258, tested with BitFlags<304> bits
};

struct LuaDrawableLink
{
	AsciiString m_previousAnimationState;	// +0x00
	AsciiString m_transitionAnimState;	// +0x04
	AsciiString m_previousAnimation;	// +0x08
	Drawable *m_drawable;	// +0x0C
	float m_prevAnimFraction;	// +0x10
	Bool m_allowToContinue;	// +0x14
};

// TheLuaScriptEngine (VA 0x00E01DBC, the subsystem initSubsystem<LuaScriptEngine>
// fills); only the current-drawable context it exposes to the callbacks.
class LuaScriptEngine
{
public:
	char m_pad00[0x9C];
	LuaDrawableLink *m_drawable;	// +0x9C
};
// Retail VA 0x00E01DBC starts with four zero-filled bytes; the verified
// initSubsystem<LuaScriptEngine> caller registers the subsystem here.
LuaScriptEngine *TheLuaScriptEngine = 0;

// ?GetClientRandomNumberReal@@YAHPAUlua_State@@@Z
int GetClientRandomNumberReal(lua_State *state)
{
	if (lua_gettop(state) <= 1) {
		lua_pushnumber(state, 0.0);
	} else {
		Real low = (Real)lua_tonumber(state, 1);
		Real high = (Real)lua_tonumber(state, 2);
#line 1896 "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\ScriptEngine\\LuaScriptEngine.cpp"
		Real value = GetGameClientRandomValueReal(low, high, __FILE__, __LINE__);
		lua_pushnumber(state, value);
	}
	return 1;
}

// ?CurDrawableAllowToContinue@@YAHPAUlua_State@@@Z
int CurDrawableAllowToContinue(lua_State *state)
{
	LuaDrawableLink *drawable = TheLuaScriptEngine->m_drawable;
	if (drawable != 0) {
		drawable->m_allowToContinue = 1;
	}
	return 0;
}

// ?GetRandomNumber@@YAHPAUlua_State@@@Z
int GetRandomNumber(lua_State *state)
{
#line 2710
	lua_pushnumber(state, GetGameLogicRandomValueReal(0.0f, 1.0f, __FILE__, __LINE__));
	return 1;
}

// ?CurDrawableModelcondition@@YAHPAUlua_State@@@Z
int CurDrawableModelcondition(lua_State *state)
{
	LuaDrawableLink *drawable = TheLuaScriptEngine->m_drawable;
	if (drawable != 0) {
		Drawable *draw = drawable->m_drawable;
		if (draw != 0 && lua_gettop(state) > 0) {
			Bool hit = 0;
			int bit = BitFlags<304>::getSingleBitFromName(lua_tostring(state, 1));
			if (bit != -1)
				hit = draw->testModelCondition(bit);

			if (hit) {
				lua_pushnumber(state, 1.0);
				return 1;
			}
		}
	}

	lua_pushnil(state);
	return 1;
}

// ?CurDrawableObjectStatus@@YAHPAUlua_State@@@Z
int CurDrawableObjectStatus(lua_State *state)
{
	LuaDrawableLink *drawable = TheLuaScriptEngine->m_drawable;
	if (drawable != 0) {
		Drawable *draw = drawable->m_drawable;
		if (draw != 0 && lua_gettop(state) > 0) {
			Bool hit = 0;
			const char *name = lua_tostring(state, 1);
			Object *object = draw->m_object;
			int bit = BitFlags<101>::getSingleBitFromName(name);
			if (bit != -1)
				hit = object->testStatus(bit);

			if (hit) {
				lua_pushnumber(state, 1.0);
				return 1;
			}
		}
	}

	lua_pushnil(state);
	return 1;
}

// ?CurDrawableHideSubObject@@YAHPAUlua_State@@@Z
int CurDrawableHideSubObject(lua_State *state)
{
	LuaDrawableLink *drawable = TheLuaScriptEngine->m_drawable;
	Drawable *draw;
	if (drawable == 0 || (draw = drawable->m_drawable) == 0 || lua_gettop(state) <= 0)
		return 0;

	const char *name = lua_tostring(state, 1);
	if (!draw->rva00278689(AsciiString(name), false, false)) {
		draw->rva002724FD(AsciiString(name), 0, 0, 0.0f, 0.0f);
	}
	return 0;
}

// ?CurDrawableShowSubObject@@YAHPAUlua_State@@@Z
int CurDrawableShowSubObject(lua_State *state)
{
	LuaDrawableLink *drawable = TheLuaScriptEngine->m_drawable;
	Drawable *draw;
	if (drawable == 0 || (draw = drawable->m_drawable) == 0 || lua_gettop(state) <= 0)
		return 0;

	const char *name = lua_tostring(state, 1);
	if (!draw->rva00278689(AsciiString(name), true, false)) {
		draw->rva002724FD(AsciiString(name), 1, 0, 0.0f, 0.0f);
	}
	return 0;
}

// ?CurDrawableHideSubObjectPermanently@@YAHPAUlua_State@@@Z
int CurDrawableHideSubObjectPermanently(lua_State *state)
{
	LuaDrawableLink *drawable = TheLuaScriptEngine->m_drawable;
	Drawable *draw;
	if (drawable == 0 || (draw = drawable->m_drawable) == 0 || lua_gettop(state) <= 0)
		return 0;

	draw->rva002724FD(AsciiString(lua_tostring(state, 1)), 0, 1, 0.0f, 0.0f);
	return 0;
}

// ?CurDrawableShowSubObjectPermanently@@YAHPAUlua_State@@@Z
int CurDrawableShowSubObjectPermanently(lua_State *state)
{
	LuaDrawableLink *drawable = TheLuaScriptEngine->m_drawable;
	Drawable *draw;
	if (drawable == 0 || (draw = drawable->m_drawable) == 0 || lua_gettop(state) <= 0)
		return 0;

	draw->rva002724FD(AsciiString(lua_tostring(state, 1)), 1, 1, 0.0f, 0.0f);
	return 0;
}

// ?CurDrawablePrevAnimationState@@YAHPAUlua_State@@@Z
int CurDrawablePrevAnimationState(lua_State *state)
{
	AsciiString previousState;
	LuaDrawableLink *drawable = TheLuaScriptEngine->m_drawable;
	if (drawable != 0) {
		previousState = drawable->m_previousAnimationState;
	}

	if (!previousState.isEmpty()) {
		lua_pushstring(state, previousState.str());
	} else {
		lua_pushnil(state);
	}
	return 1;
}

// ?CurDrawablePrevAnimation@@YAHPAUlua_State@@@Z
int CurDrawablePrevAnimation(lua_State *state)
{
	AsciiString previousAnimation;
	LuaDrawableLink *drawable = TheLuaScriptEngine->m_drawable;
	if (drawable != 0) {
		previousAnimation = drawable->m_previousAnimation;
	}

	if (!previousAnimation.isEmpty()) {
		lua_pushstring(state, previousAnimation.str());
	} else {
		lua_pushnil(state);
	}
	return 1;
}

// ?CurDrawableIsCurrentTargetKindof@@YAHPAUlua_State@@@Z
int CurDrawableIsCurrentTargetKindof(lua_State *state)
{
	LuaDrawableLink *drawable = TheLuaScriptEngine->m_drawable;
	if (drawable != 0 && drawable->m_drawable != 0 && drawable->m_drawable->m_object != 0) {
		Object *target = TheGameLogic->findObjectByID((ObjectID)drawable->m_drawable->m_object->m_currentTargetID);
		if (target != 0 && lua_gettop(state) > 0) {
			int kind = BitFlags<218>::getSingleBitFromName(lua_tostring(state, 1));
			if (target->m_template->isKindOf(kind)) {
				bfmeGo1039E((BfmeQ1039 *)state, 1);
				return 1;
			}
		}
	} else {
		lua_pushnil(state);
	}

	bfmeGo1039E((BfmeQ1039 *)state, 0);
	return 1;
}
